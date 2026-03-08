import math
import random

h1 = 0.10
h2 = 0.10
l = 1.0
v1 = 40.0
v2 = 30.0
c1 = 0.115
c2 = 0.15
a1 = 0.5
a2 = 0.5

def func_to_minimize(x):
    if x < 0 or x > l:
        return float('inf')
    
    dist1 = math.sqrt(h1 * h1 + x * x)
    dist2 = math.sqrt(h2 * h2 + (l - x) * (l - x))
    
    time1 = dist1 / v1
    time2 = dist2 / v2
    total_time = time1 + time2
    
    fuel1 = dist1 * c1
    fuel2 = dist2 * c2
    total_fuel = fuel1 + fuel2
    
    return a1 * total_time + a2 * total_fuel

def h_probability_function(delta_e: float, temperature: float) -> float:
    if temperature <= 0:
        return 0.0
    return math.exp(-delta_e / temperature)

def linear_decrease_temperature(current_temperature: float) -> float:
    """Простое линейное уменьшение температуры."""
    return current_temperature - 1

def generate_new_x(x: float) -> float:
    step_size = 0.1
    new_x = x + random.uniform(-step_size, step_size)
    return new_x

def annealing(x_start: float,
              initial_temperature: float,
              decrease_temperature: callable,
              p: float,
              f: callable,
              generate_new_x: callable,
              h: callable,
              max_iterations: int = 1000) -> (float, float):
    
    x = x_start
    temperature = initial_temperature
    iteration = 0
    
    while temperature > 0 and iteration < max_iterations:
        target_function_value = f(x)
        
        for _ in range(100):  
            x_n = generate_new_x(x)
            new_target_function_value = f(x_n)
            if math.isinf(new_target_function_value):
                continue
            
            delta = new_target_function_value - target_function_value
            new_probability = h(delta, temperature)
            
            if new_probability > p:
                x = x_n
                break  
            
        temperature = decrease_temperature(temperature)
        iteration += 1
        
    return x, f(x)

start_x = 0.5
threshold_p = 0.3
initial_temp = 0.01

print(f"Поиск минимума методом имитации отжига")
print(f"Начальная температура: {initial_temp}")
print("-" * 30)

num_runs = 5
for run in range(num_runs):
    final_x, final_f = annealing(start_x,
                                 initial_temp,
                                 linear_decrease_temperature,
                                 threshold_p,
                                 func_to_minimize,
                                 generate_new_x,
                                 h_probability_function,
                                 max_iterations=500) 
    print(f"Run {run+1}: x* = {final_x:.4f}, f(x*) = {final_f:.6f}")

print("-" * 30)

from scipy.optimize import minimize_scalar
result_scipy = minimize_scalar(func_to_minimize, bounds=(0, l), method='bounded')
print(f"Для справки (minimize_scalar): x* = {result_scipy.x:.4f}, f(x*) = {result_scipy.fun:.6f}")