import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return 2 - 0.3 * np.exp(x) + np.cos(x)**2

def f_prime(x):
    return -0.3 * np.exp(x) - np.sin(2*x)

def f_double_prime(x):
    return -0.3 * np.exp(x) - 2 * np.cos(2*x)

x_vals = np.linspace(0, 3, 1000)
y_vals = f(x_vals)
plt.plot(x_vals, y_vals)
plt.axhline(0, color='black', linestyle='--')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('График f(x) = 2 - 0.3*exp(x) + cos^2(x)')
plt.grid(True)
plt.show()

step = 0.01
x = 1.9
while x < 2.1:
    if f(x) * f(x+step) < 0:
        a, b = x, x+step
        break
    x += step
else:
    a, b = 1.95, 2.0

print(f"Интервал локализации: [{a:.4f}, {b:.4f}]")
print(f"f({a:.4f}) = {f(a):.6f}, f({b:.4f}) = {f(b):.6f}")

if f(a) * f(b) < 0:
    print("Условие (2) выполнено: f(a)*f(b) < 0")
else:
    print("Условие (2) не выполнено!")

x_test = np.linspace(a, b, 10)
sign_fprime = np.sign(f_prime(x_test))
sign_fdoubleprime = np.sign(f_double_prime(x_test))

if np.all(sign_fprime == sign_fprime[0]) and np.all(sign_fdoubleprime == sign_fdoubleprime[0]):
    print("Условие (3) выполнено: производные сохраняют знак и не обращаются в ноль")
    print(f"Знак f'(x) на интервале: {'отрицательный' if sign_fprime[0] < 0 else 'положительный'}")
    print(f"Знак f''(x) на интервале: {'отрицательный' if sign_fdoubleprime[0] < 0 else 'положительный'}")
else:
    print("Условие (3) не выполнено: производные меняют знак или равны нулю")

x0 = (a + b) / 2
print(f"Начальное приближение x0 = {x0:.6f}")

if f(x0) * f_double_prime(x0) > 0:
    print("Условие (4) выполнено: f(x0)*f''(x0) > 0")
else:
    print("Условие (4) не выполнено!")

eps = 0.01
x_prev = x0
max_iter = 100
print("\nИтерации метода Ньютона:")
for i in range(max_iter):
    f_val = f(x_prev)
    f_der = f_prime(x_prev)
    if abs(f_der) < 1e-12:
        print("Производная слишком мала, метод не сходится")
        break
    x_next = x_prev - f_val / f_der
    diff = abs(x_next - x_prev)
    print(f"Итерация {i+1}: x = {x_next:.6f}, |xk+1 - xk| = {diff:.6f}")
    if diff < eps:
        print(f"\nДостигнута требуемая точность ε = {eps}.")
        print(f"Приближённое значение корня: x = {x_next:.6f}")
        break
    x_prev = x_next
else:
    print("Достигнуто максимальное число итераций")
