import subprocess
import matplotlib.pyplot as plt
import time
import os

plt.rcParams['font.family'] = 'DejaVu Sans'
plt.rcParams['axes.unicode_minus'] = False

def run_single_test(method, array_type, size, timeout=30):
    exe_path = "main.exe"
    if not os.path.exists(exe_path):
        raise FileNotFoundError(f"{exe_path} не найден")

    out_filename = f"temp_{method}_{array_type}_{size}.txt"
    if os.path.exists(out_filename):
        os.remove(out_filename)

    input_data = f"2\n{array_type}\n{size} {size+1} 1\n{method}\n{out_filename[:-4]}\n"

    proc = subprocess.Popen(
        exe_path,
        stdin=subprocess.PIPE,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
        text=True
    )

    try:
        proc.stdin.write(input_data)
        proc.stdin.close()
    except Exception as e:
        print(f"    Ошибка записи в stdin: {e}")

    # Ждём, пока файл не станет непустым
    start_wait = time.time()
    while (time.time() - start_wait) < timeout:
        if os.path.exists(out_filename) and os.path.getsize(out_filename) > 0:
            break
        time.sleep(0.1)
    else:
        # Таймаут — файл пуст или не создан
        if proc.poll() is None:
            proc.terminate()
            try:
                proc.wait(timeout=1)
            except subprocess.TimeoutExpired:
                proc.kill()
        raise TimeoutError(f"Файл {out_filename} не создан или пуст за {timeout} секунд")

    # Даём процессу ещё немного времени на завершение записи (опционально)
    time.sleep(0.2)

    # Принудительно завершаем процесс
    if proc.poll() is None:
        proc.terminate()
        try:
            proc.wait(timeout=1)
        except subprocess.TimeoutExpired:
            proc.kill()

    # Читаем время из файла
    time_ms = None
    with open(out_filename, 'r', encoding='utf-8') as f:
        for line in f:
            if line.startswith(f"N={size}"):
                parts = line.split('time=')
                if len(parts) == 2:
                    time_us = int(parts[1].strip())
                    time_ms = time_us / 1000.0
                    break

    os.remove(out_filename)

    if time_ms is None:
        raise ValueError(f"В файле {out_filename} нет строки с N={size}")

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
        time.sleep(0.5)   # пауза между запусками
    return results


def plot_time_vs_size():
    """Сравнение методов (случайные данные)."""
    plt.figure(figsize=(12, 8))
    sizes = list(range(1000, 10001, 1000))

    methods = {
        1: "Прямое слияние",
        2: "Естественное слияние"
    }
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
    plt.title('Сравнение быстродействия алгоритмов внешней сортировки\n(случайные данные)', fontsize=14)
    plt.grid(True, alpha=0.3)
    if any(data for _, data in methods.items()):
        plt.legend()
    plt.text(0.02, 0.98,
             'Вывод: Естественное слияние обычно быстрее прямого,\n'
             'особенно на частично упорядоченных данных.\n'
             'На полностью случайных данных разница может быть невелика.',
             transform=plt.gca().transAxes, verticalalignment='top',
             bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5), fontsize=10)
    plt.tight_layout()
    plt.savefig('merge_time_comparison.png', dpi=300)
    plt.show()


def plot_behavior_for_method(method_num, method_name):
    """Влияние типа данных на один метод."""
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
    plt.title(f'Влияние исходной упорядоченности\nАлгоритм: {method_name}', fontsize=14)
    plt.grid(True, alpha=0.3)
    if any(True for _ in array_types):
        plt.legend()
    if method_num == 1:
        note = ('Вывод для прямого слияния:\n'
                '• Не зависит от исходного порядка – всегда разбивает на серии фиксированной длины\n'
                '• Время практически одинаково для любых типов данных\n'
                '• Естественность поведения отсутствует')
    else:
        note = ('Вывод для естественного слияния:\n'
                '• На упорядоченных данных работает значительно быстрее (длинные серии)\n'
                '• На обратно упорядоченных – медленнее (короткие серии)\n'
                '• Обладает высокой степенью естественности')

    plt.text(0.02, 0.98, note, transform=plt.gca().transAxes, verticalalignment='top',
             bbox=dict(boxstyle='round', facecolor='lightblue', alpha=0.7),
             fontsize=9, family='monospace')
    plt.tight_layout()
    plt.savefig(f'merge_behavior_{method_num}.png', dpi=300)
    plt.show()


def main():
    print("=" * 60)
    print("Сбор данных и построение графиков (внешняя сортировка слиянием)")
    print("=" * 60)

    if not os.path.exists("main.exe"):
        print("ОШИБКА: main.exe не найден!")
        return

    # График 1: сравнение методов (случайные данные)
    plot_time_vs_size()

    # График 2: поведение прямого слияния
    plot_behavior_for_method(1, "Прямое слияние")

    # График 3: поведение естественного слияния
    plot_behavior_for_method(2, "Естественное слияние")

    print("\nГрафики сохранены:")
    print("  - merge_time_comparison.png")
    print("  - merge_behavior_1.png")
    print("  - merge_behavior_2.png")


if __name__ == "__main__":
    main()