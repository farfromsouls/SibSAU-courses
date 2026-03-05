from IPython.display import HTML
# подключаем модули Jupyter Notebook для взаимодействия с пользователем
from ipywidgets import interact, interactive, fixed, interact_manual
import ipywidgets as widgets
from IPython.display import display

# пдключаем модули для расчетов и рисования графиков
import numpy as np
import matplotlib.pyplot as plt


# Служебная функция
# Возврашает элемент массива, переданного ей в качестве первого параметра с указанным номером
def step_slice(lst, step):
    return lst[step]


# Функция анимации. Именно она будет рисовать последовательность шагов
def animate_list(lst, play=False, interval=200):
    slider = widgets.IntSlider(min=0, max=len(lst) - 1, step=1, value=0)
    if play:
        play_widjet = widgets.Play(interval=interval)
        widgets.jslink((play_widjet, 'value'), (slider, 'value'))
        display(play_widjet)
    return interact(step_slice, lst=fixed(lst), step=slider)


# Отрисовка траектории и линий уровня функции
def plot_trajectory(func, traj, limit_point=None):
    # Добавим график, в ктором будем рисовать
    fig = plt.figure(figsize=(7, 7))
    ax = fig.add_axes([0, 0, 1, 1])    
    
    # Если задаа финальная точка, обозначим ее зеленым кружком
    if limit_point:
        ax.plot([limit_point[0]], [limit_point[1]], 'o', color='green')

    delta = 0.025
    x = np.arange(-2, 2, delta)  # диапазон значений по x
    y = np.arange(-2, 2, delta)  # и по y соответственно
    X, Y = np.meshgrid(x, y)  # пространственная сетка по указанным диапазонам значений
    
    # вычисление значений функции во всех узлах сетки, необходимо для рисования изолиний на графике
    Z = np.zeros_like(X)
    for i in range(X.shape[0]):
        for j in range(X.shape[1]):
            Z[i][j] = func(X[i][j], Y[i][j])
    # создание контуров изолиний по заданным значениям функции
    CS = ax.contour(X, Y, Z, [0.5, 1.5, 3], colors=['blue', 'purple', 'red'])  # значения функции, для которых будут нарисованы изолинии, и соответствующие им цвета
    ax.plot([u[0] for u in traj], [u[1] for u in traj], color='black')  # рисование всех линий траектории
    ax.plot([u[0] for u in traj], [u[1] for u in traj], 'o', color='black')  # и соответствующих им точек
    
    plt.close(fig)
    return fig

display(HTML('<link rel="stylesheet" href="//stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css"/>'))
# Функция, которую минимизируем, минимум в точке (0, 0)
def f(x, y):
    return 1.3 * (x - y) ** 2 + 0.7 * (x + y) ** 2

x, y = (1.0, 1.0)
num_iters = 50
trajectory = [(x, y)]
plots = []

for i in range(num_iters):
    step_length = 1 / (2 * (i + 1) ** 0.5)   # убывающий шаг

    # Чередуем координаты: чётный i – движение по x, нечётный – по y
    if i % 2 == 0:
        candidates = [(x + step_length, y), (x - step_length, y)]
    else:
        candidates = [(x, y + step_length), (x, y - step_length)]

    # Выбираем лучшее направление (минимальное значение f)
    best_x, best_y = min(candidates, key=lambda p: f(p[0], p[1]))

    # Добавляем пробную точку в траекторию и строим график
    trajectory.append((best_x, best_y))
    plots.append(plot_trajectory(f, trajectory, limit_point=(0, 0)))

    # Если пробная точка лучше текущей – перемещаемся, иначе откатываем траекторию
    if f(best_x, best_y) < f(x, y):
        x, y = best_x, best_y
    else:
        trajectory.pop()

animate_list(plots, play=True, interval=300);