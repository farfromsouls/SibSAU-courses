import math
from scipy.optimize import minimize

# зададим исходные данные в километрах
h1 = 0.10  # 100 метров
h2 = 0.10  # 100 метров
l = 1  # 1000 метров

v1 = 40  # 40 км/ч
v2 = 30  # 30 км/ч

c1 = 0.115  # л/км
c2 = 0.15  # л/км

t_max = 0.028  # максимальное время в часах
penalty_coef = 1000  # коэффициент штрафа

# описываем функцию для расчета времени движения
def time_func(x):
    # Расстояние по первому участку: от (0,0) до (x, h1)
    dist1 = math.sqrt(h1**2 + x**2)
    # Расстояние по второму участку: от (x, h1) до (l, h1+h2)
    dist2 = math.sqrt((l - x)**2 + h2**2)
    
    # Время = расстояние / скорость
    time = dist1 / v1 + dist2 / v2
    return time

# описываем функцию для расчета расхода топлива
def fuel_func(x):
    # Расстояние по первому участку
    dist1 = math.sqrt(h1**2 + x**2)
    # Расстояние по второму участку
    dist2 = math.sqrt((l - x)**2 + h2**2)
    
    # Расход топлива = расстояние * расход на км
    fuel = dist1 * c1 + dist2 * c2
    return fuel

# описываем функцию со штрафом, которую будем минимизировать
def func_to_minimize(x):
    # Преобразуем x в число, если это массив
    if hasattr(x, '__len__'):
        x_val = x[0]
    else:
        x_val = x
    
    # Рассчитываем базовый расход топлива
    fuel = fuel_func(x_val)
    
    # Рассчитываем время движения
    time = time_func(x_val)
    
    # Добавляем штраф, если время превышает допустимое
    if time > t_max:
        # Квадратичный штраф за превышение времени
        penalty = penalty_coef * (time - t_max)**2
    else:
        penalty = 0
    
    return fuel + penalty

# Зададим начальное значение x
x0 = 0

# Добавляем границы для x (0 <= x <= l)
bounds = [(0, l)]

# Минимизируем функцию со штрафом
result = minimize(func_to_minimize, x0, bounds=bounds)

print("Результат оптимизации со штрафной функцией:")
print(result)
print(f"\nОптимальное значение x: {result.x[0]:.4f} км")
print(f"Расход топлива: {fuel_func(result.x[0]):.4f} л")
print(f"Время движения: {time_func(result.x[0]):.4f} ч")
print(f"Ограничение по времени: {time_func(result.x[0]):.4f} <= {t_max} - {time_func(result.x[0]) <= t_max}")