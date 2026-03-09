import math

# Определение функции
def f(x):
    return math.atan(3 + 2 * x * x)

# Параметры
n = 10
h = 1.0 / n

# 1. Узлы и значения функции
t = [i * h for i in range(n + 1)]          # t_j = (j-1)h, j=1..11
f_vals = [f(x) for x in t]

# Вычисление разделенных разностей
dd = [f_vals]                                # dd[0] – значения функции
for k in range(1, n + 1):
    prev = dd[k - 1]
    new = []
    for i in range(len(prev) - 1):
        # для равноотстоящих узлов знаменатель = k*h
        diff = (prev[i + 1] - prev[i]) / (k * h)
        new.append(diff)
    dd.append(new)

# Коэффициенты интерполяционного многочлена Ньютона (привязаны к узлу t[0])
coeffs = [dd[0][0]] + [dd[k][0] for k in range(1, n + 1)]

# Функция для вычисления многочлена Ньютона в точке x (схема Горнера)
def newton_poly(x, nodes, coeffs):
    m = len(coeffs) - 1          # степень многочлена
    p = coeffs[m]
    for i in range(m - 1, -1, -1):
        p = coeffs[i] + (x - nodes[i]) * p
    return p

# 2. Точки с полуцелыми индексами
t_half = [(j - 0.5) * h for j in range(1, n + 1)]   # j=1..10 → 0.05, 0.15, ..., 0.95

# Вычисление погрешностей
results = []
for x in t_half:
    exact = f(x)
    interp = newton_poly(x, t, coeffs)
    err = abs(exact - interp)
    results.append((x, exact, interp, err))

errors = [r[3] for r in results]
eps_max = max(errors)
eps_rms = math.sqrt(sum(e**2 for e in errors) / n)

# 3. Вывод результатов
print("Разделенные разности:")
print("f(t_j):", " ".join(f"{v:.6f}" for v in f_vals))
for k in range(1, n + 1):
    print(f"Разности {k}-го порядка:", " ".join(f"{v:.6f}" for v in dd[k]))

print("\nКоэффициенты Ньютона (f1, f[t1,t2], ..., f[t1..t11]):")
print(" ".join(f"{c:.6f}" for c in coeffs))

print("\nИнтерполяция в точках с полуцелыми индексами:")
print(" j    t_{j-1/2}    f(t)           N(t)           |f-N|")
for i, (x, exact, interp, err) in enumerate(results, start=1):
    print(f"{i:2}    {x:.2f}       {exact:.8f}   {interp:.8f}   {err:.2e}")

print(f"\nМаксимальная погрешность: {eps_max:.2e}")
print(f"Среднеквадратичная погрешность: {eps_rms:.2e}")