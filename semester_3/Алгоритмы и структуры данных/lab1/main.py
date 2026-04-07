import subprocess
import matplotlib.pyplot as plt
import time
import os
import signal

plt.rcParams['font.family'] = 'DejaVu Sans'
plt.rcParams['axes.unicode_minus'] = False

def run_single_test(method, array_type, size, timeout=10):
    """Запускает main.exe для одного теста и возвращает время в мс."""
    exe_path = "main.exe"
    if not os.path.exists(exe_path):
        raise FileNotFoundError(f"{exe_path} не найден")

    output_filename = f"temp_{method}_{array_type}_{size}.txt"
    if os.path.exists(output_filename):
        os.remove(output_filename)

    # Передаём диапазон так, чтобы C++ выполнил цикл ровно один раз
    input_data = f"2\n{array_type}\n{size} {size+1} 1\n{method}\ntemp_{method}_{array_type}_{size}\n"

    # Запускаем процесс
    proc = subprocess.Popen(
        exe_path,
        stdin=subprocess.PIPE,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
        text=True
    )

    try:
        # Отправляем данные и закрываем stdin (чтобы процесс не ждал дальше)
        proc.stdin.write(input_data)
        proc.stdin.close()
    except Exception:
        pass

    # Ждём появления файла (не более timeout секунд)
    start_wait = time.time()
    while not os.path.exists(output_filename) and (time.time() - start_wait) < timeout:
        time.sleep(0.1)

    # Принудительно завершаем процесс (он всё равно не завершится сам)
    if proc.poll() is None:
        proc.terminate()
        try:
            proc.wait(timeout=1)
        except subprocess.TimeoutExpired:
            proc.kill()

    # Если файл не появился – ошибка
    if not os.path.exists(output_filename):
        raise TimeoutError(f"Файл {output_filename} не создан за {timeout} секунд")

    # Читаем время из файла
    time_ms = None
    with open(output_filename, 'r', encoding='utf-8') as f:
        for line in f:
            if line.startswith(f"N={size}"):
                time_str = line.split('time=')[1].strip()
                time_us = int(time_str)
                time_ms = time_us / 1000.0
                break

    os.remove(output_filename)

    if time_ms is None:
        raise ValueError(f"В файле {output_filename} нет строки с N={size}")

    return time_ms


def collect_data(method, array_type, sizes):
    """Собирает данные для списка размеров."""
    results = []
    for size in sizes:
        print(f"  Тест: метод={method}, тип={array_type}, размер={size}")
        try:
            t = run_single_test(method, array_type, size)
            results.append((size, t))
            print(f"    Время: {t:.3f} мс")
        except Exception as e:
            print(f"    Ошибка: {e}")
        time.sleep(0.3)  # пауза между тестами
    return results


def plot_time_vs_size():
    """Сравнение алгоритмов на случайных данных."""
    plt.figure(figsize=(12, 8))
    sizes = list(range(1000, 10001, 1000))

    methods = {1: "Сортировка вставками", 2: "Сортировка Шелла"}
    colors = ['blue', 'red']
    markers = ['o', 's']

    for method_num, method_name in methods.items():
        print(f"\nСбор данных для {method_name} (случайные значения)")
        data = collect_data(method_num, 1, sizes)
        if data:
            x, y = zip(*data)
            plt.plot(x, y, marker=markers[method_num-1], color=colors[method_num-1],
                     linewidth=2, markersize=6, label=method_name)

    plt.xlabel('Количество элементов', fontsize=12)
    plt.ylabel('Время (мс)', fontsize=12)
    plt.title('Сравнение быстродействия алгоритмов (случайные значения)', fontsize=14)
    plt.grid(True, alpha=0.3)
    plt.legend()
    plt.text(0.02, 0.98,
             'Вывод: Сортировка Шелла значительно быстрее сортировки вставками\n'
             'для массивов размером > 2000 элементов',
             transform=plt.gca().transAxes, verticalalignment='top',
             bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5), fontsize=10)
    plt.tight_layout()
    plt.savefig('time_comparison.png', dpi=300)
    plt.show()


def plot_behavior_for_method(method_num, method_name):
    """Поведение одного алгоритма на разных типах массивов."""
    plt.figure(figsize=(12, 8))
    sizes = list(range(1000, 10001, 1000))

    array_types = {
        1: "Случайные значения",
        2: "Упорядоченные значения",
        3: "Обратный порядок"
    }
    colors = ['green', 'orange', 'purple']
    markers = ['^', 'D', '*']
    linestyles = ['-', '--', ':']

    print(f"\nСбор данных для {method_name}")
    for at_num, at_name in array_types.items():
        print(f"  Тип массива: {at_name}")
        data = collect_data(method_num, at_num, sizes)
        if data:
            x, y = zip(*data)
            plt.plot(x, y, marker=markers[at_num-1], color=colors[at_num-1],
                     linestyle=linestyles[at_num-1], linewidth=2, markersize=6,
                     label=at_name)

    plt.xlabel('Количество элементов', fontsize=12)
    plt.ylabel('Время (мс)', fontsize=12)
    plt.title(f'Влияние исходной упорядоченности массива\nАлгоритм: {method_name}', fontsize=14)
    plt.grid(True, alpha=0.3)
    plt.legend()

    if method_num == 1:
        note = ('Вывод для сортировки вставками:\n'
                '• На упорядоченных данных – почти линейное время\n'
                '• На обратно упорядоченных – максимальное время\n'
                '• Высокая естественность поведения')
    else:
        note = ('Вывод для сортировки Шелла:\n'
                '• Менее чувствительна к исходному порядку\n'
                '• На упорядоченных данных работает немного быстрее\n'
                '• Средняя степень естественности')

    plt.text(0.02, 0.98, note, transform=plt.gca().transAxes, verticalalignment='top',
             bbox=dict(boxstyle='round', facecolor='lightblue', alpha=0.7),
             fontsize=9, family='monospace')
    plt.tight_layout()
    plt.savefig(f'behavior_{method_num}.png', dpi=300)
    plt.show()


def main():
    print("=" * 60)
    print("Сбор данных и построение графиков")
    print("=" * 60)

    if not os.path.exists("main.exe"):
        print("ОШИБКА: main.exe не найден!")
        return

    plot_time_vs_size()
    plot_behavior_for_method(1, "Сортировка вставками")
    plot_behavior_for_method(2, "Сортировка Шелла")

    print("\nГрафики сохранены:")
    print("  - time_comparison.png")
    print("  - behavior_1.png")
    print("  - behavior_2.png")


if __name__ == "__main__":
    main()