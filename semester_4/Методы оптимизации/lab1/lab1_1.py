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
max_iters = 50             
eps = 1e-4                 
trajectory = [(x, y)]
plots = []

i = 0
while i < max_iters:
    step_length = 1 / (2 * (i + 1) ** 0.5)
    if step_length < eps:
        print(f"Достигнута заданная точность на шаге {i}")
        break

    angle = 2 * np.pi * np.random.rand(1)
    dx = np.cos(angle)[0] * step_length
    dy = np.sin(angle)[0] * step_length

    trajectory.append((x + dx, y + dy))
    plots.append(plot_trajectory(f, trajectory, limit_point=(0, 0)))

    if f(x, y) > f(x + dx, y + dy):
        x = x + dx
        y = y + dy
    else:
        trajectory.pop() 

    i += 1

animate_list(plots, play=True, interval=300)