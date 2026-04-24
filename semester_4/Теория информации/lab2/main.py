import math
import random

# ------------------------------------------------------------
# Часть 1: ваш исходный код (без изменений)
# ------------------------------------------------------------

ru = "абвгдежзийклмнопрстуфхцчшщьыъэюя"

with open("text.txt", "r", encoding="utf-8") as f:
    
    # очистка текста
    text = f.read().split()
    words = ["".join([i.lower() for i in word if i.lower() in ru]) for word in text]
    combinations = []
    
    # сбор комбинаций пар символов
    for word in words:
        if len(word) >= 2:
            for i in range(len(word) // 2):
                combinations.append(word[i*2] + word[i*2 + 1])
    
    # подсчет комбинаций пар символов
    result = {}
    for combination in combinations:
        if combination not in result:
            result[combination] = 1
        else:
            result[combination] += 1

print("  " + "  ".join([i for i in ru]))
for a1 in ru:
    line = a1 + " "
    for a2 in ru:
        if a1+a2 in result:
            amount = str(result[a1+a2])
            if len(amount) == 2:
                line += amount + " "
            else:
                line += amount + "  "
        else:
            line += "0  "
    print(line)

print("Исследование канала связи (10x10)")

# случайная матрица совместных вероятностей 10x10
random.seed(42)  # для воспроизводимости
N = 10
P = [[random.random() for _ in range(N)] for _ in range(N)]
total = sum(sum(row) for row in P)
for i in range(N):
    for j in range(N):
        P[i][j] /= total   # теперь сумма всех p_ij = 1

# В соответствии с примечанием:
# строки P – это y (приёмник), столбцы – x (источник).
# Тогда:
p_x = [sum(P[y][x] for y in range(N)) for x in range(N)]   # сумма по столбцам
p_y = [sum(P[y][x] for x in range(N)) for y in range(N)]   # сумма по строкам

# Канальная матрица со стороны источника: P(Y|X)
# p_y_given_x[y][x] = P[y][x] / p_x[x]
p_y_given_x = [[P[y][x] / p_x[x] if p_x[x] > 0 else 0.0 for x in range(N)] for y in range(N)]

# Канальная матрица со стороны приёмника: P(X|Y)
# p_x_given_y[y][x] = P[y][x] / p_y[y]  (если p_y[y] > 0)
p_x_given_y = [[P[y][x] / p_y[y] if p_y[y] > 0 else 0.0 for x in range(N)] for y in range(N)]

# 2. Потери информации H(Y|x_i)
H_Y_xi = []
for x in range(N):
    h = 0.0
    for y in range(N):
        prob = p_y_given_x[y][x] 
        if prob > 0:
            h -= prob * math.log2(prob)
    H_Y_xi.append(h)

print("\nПотери информации H(Y|x_i) для каждого переданного сигнала x_i:")
for x, h in enumerate(H_Y_xi):
    print(f"  x_{x}: {h:.4f} бит")

# Полная условная энтропия H(Y|X)
H_Y_X = 0.0
for x in range(N):
    H_Y_X += p_x[x] * H_Y_xi[x]

print(f"\nПотери информации при передаче всех сигналов H(Y|X) = {H_Y_X:.4f} бит")

# 3. Потери информации H(X|y_j)
H_X_yj = []
for y in range(N):
    h = 0.0
    for x in range(N):
        prob = p_x_given_y[y][x]
        if prob > 0:
            h -= prob * math.log2(prob)
    H_X_yj.append(h)

print("\nПотери информации H(X|y_j) для каждого принятого сигнала y_j:")
for y, h in enumerate(H_X_yj):
    print(f"  y_{y}: {h:.4f} бит")

# Полная условная энтропия H(X|Y)
H_X_Y = 0.0
for y in range(N):
    H_X_Y += p_y[y] * H_X_yj[y]

print(f"\nПотери информации при приёме всех сигналов H(X|Y) = {H_X_Y:.4f} бит")

print("Энтропия двухбуквенных сочетаний текста")

# Алфавит – 32 буквы из ru (без 'ё')
alphabet = list(ru)
L = len(alphabet)  # 32
# Соответствие буква -> индекс
char_to_idx = {ch: i for i, ch in enumerate(alphabet)}

# Матрица совместных частот (X – первая буква, Y – вторая)
# размер L x L, сначала заполним нулями
freq = [[0]*L for _ in range(L)]
total_pairs = 0

for pair, count in result.items():
    if len(pair) == 2:
        x_char = pair[0]
        y_char = pair[1]
        if x_char in char_to_idx and y_char in char_to_idx:
            xi = char_to_idx[x_char]
            yi = char_to_idx[y_char]
            freq[xi][yi] += count
            total_pairs += count

# Преобразуем в вероятности
if total_pairs > 0:
    prob_xy = [[f / total_pairs for f in row] for row in freq]
else:
    prob_xy = [[0.0]*L for _ in range(L)]

# Расчёт H(X,Y)
H_XY = 0.0
for row in prob_xy:
    for p in row:
        if p > 0:
            H_XY -= p * math.log2(p)

# Маргинальное распределение X
p_x_text = [sum(prob_xy[xi][yi] for yi in range(L)) for xi in range(L)]

# Энтропия H(X)
H_X_text = 0.0
for p in p_x_text:
    if p > 0:
        H_X_text -= p * math.log2(p)

# Условная энтропия H(Y|X) = H(X,Y) - H(X)
H_Y_given_X_text = H_XY - H_X_text

print(f"\nОбщее число двухбуквенных сочетаний: {total_pairs}")
print(f"Энтропия объединения H(X,Y) = {H_XY:.4f} бит")
print(f"Энтропия источника H(X)    = {H_X_text:.4f} бит")
print(f"Условная энтропия H(Y|X)   = {H_Y_given_X_text:.4f} бит")