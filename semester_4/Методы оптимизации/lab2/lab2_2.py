import math  # 
from scipy.optimize import minimize  # берем готовую библиотечную функцию minimize

# задаим исходные данные в километрах

h1 = 0.10  # 100 метров
h2 = 0.10  # 100 метров
l = 1  # 1000 метров

v1 = 40  # 40 км/ч
v2 = 30  # 30 км/ч

c1 = 0.115  # л/км
c2 = 0.15  # л/км

a1 = 0.5  # вес первого критерия, т.е. времени движения
a2 = 0.5  # вес второго критерия, т.е. расхода топлива

# описываем функцию, которую хотим минимизировать

def func_to_minimize(x):
    dist1 = math.sqrt(h1 * h1 + x * x)
    dist2 = math.sqrt(h2 * h2 + (l - x) * (l - x))
    
    time1 = dist1 / v1
    time2 = dist2 / v2
    total_time = time1 + time2 
    
    fuel1 = dist1 * c1
    fuel2 = dist2 * c2
    total_fuel = fuel1 + fuel2
    
    return a1 * total_time + a2 * total_fuel
    
x = 0

# а теперь минимизируем нашу функцию
result = minimize(func_to_minimize, x)
print(result)  # выведем наш результа на экран