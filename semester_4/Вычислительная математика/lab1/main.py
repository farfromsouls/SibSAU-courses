def triangle_matrix(matrix):
    for k in range(3):            
        for i in range(k+1, 4):     
            m = matrix[i][k] / matrix[k][k] 
            for j in range(k, 5): 
                matrix[i][j] -= m * matrix[k][j]

def U(t_matrix):
    u4 = t_matrix[3][4]/t_matrix[3][3]
    u3 = (t_matrix[2][4]-t_matrix[2][3]*u4)/t_matrix[2][2]
    u2 = (t_matrix[1][4]-t_matrix[1][3]*u4-t_matrix[1][2]*u3)/t_matrix[1][1]
    u1 = (t_matrix[0][4]-t_matrix[0][3]*u4-t_matrix[0][2]*u3-t_matrix[0][1]*u2)/t_matrix[0][0]
    return [u1, u2, u3, u4]

def mat_vec_mult(A, v):
    n = len(A)
    res = [0.0] * n
    for i in range(n):
        s = 0.0
        for j in range(n):
            s += A[i][j] * v[j]
        res[i] = s
    return res

def vec_sub(a, b):
    return [a[i] - b[i] for i in range(len(a))]

def vec_add(a, b):
    return [a[i] + b[i] for i in range(len(a))]

def vec_mul_scalar(v, s):
    return [x * s for x in v]

def norm1(v):
    return sum(abs(x) for x in v)

def build_B_c(A, f):
    n = len(A)
    B = [[0.0]*n for _ in range(n)]
    c = [0.0]*n
    for i in range(n):
        diag = A[i][i]
        c[i] = f[i] / diag
        for j in range(n):
            if i != j:
                B[i][j] = -A[i][j] / diag
    return B, c

def norm_matrix_cols(B):
    n = len(B)
    max_sum = 0.0
    for j in range(n):
        s = sum(abs(B[i][j]) for i in range(n))
        if s > max_sum:
            max_sum = s
    return max_sum

def simple_iteration(A, f, x0, eps):
    B, c = build_B_c(A, f)
    q = norm_matrix_cols(B)
    print(f"Норма матрицы перехода q = {q:.6f}")
    if q >= 1:
        print("Внимание: q >= 1, метод может не сходиться!")
    stop_tol = ((1 - q) / q) * eps if q != 0 else 0
    print(f"Порог остановки: {stop_tol:.6f}")
    
    x_prev = x0[:]
    iterations = 0
    while True:
        x_next = [0.0]*len(A)
        for i in range(len(A)):
            s = c[i]
            for j in range(len(A)):
                s += B[i][j] * x_prev[j]
            x_next[i] = s
        diff_norm = norm1(vec_sub(x_next, x_prev))
        iterations += 1
        print(f"Итерация {iterations}: x = {[round(x,6) for x in x_next]}, ||uk+1 - uk|| = {diff_norm:.6f}")
        if diff_norm <= stop_tol:
            break
        x_prev = x_next
    return x_next, iterations, diff_norm

def main():
    matrix = [[4.503, 0.219, 0.527, 0.396, 0.553],
              [0.259, 5.121, 0.423, 0.206, 0.358],
              [0.413, 0.531, 4.317, 0.264, 0.565],
              [0.327, 0.412, 0.203, 4.851, 0.436]]

    A = [[matrix[i][j] for j in range(4)] for i in range(4)]
    f = [matrix[i][4] for i in range(4)]

    M = [row[:] for row in matrix] 
    triangle_matrix(M)              
    u_gauss = U(M)                         
    print("Решение методом Гаусса u =", [round(x,6) for x in u_gauss])

    Au = mat_vec_mult(A, u_gauss)

    print("A*u =", [round(x,6) for x in Au])
    print("f =", [round(x,6) for x in f])
    print("Невязка:", [round(Au[i]-f[i],6) for i in range(4)])
    print("-"*50)

    eps = 0.001
    x0 = [0.0, 0.0, 0.0, 0.0]
    u_iter, iter_count, last_diff = simple_iteration(A, f, x0, eps)
    print(f"\nПростая итерация за {iter_count} итераций: u = {[round(x,6) for x in u_iter]}")
    print(f"Норма разности на последней итерации: {last_diff:.6f} (требовалось <= {((1-norm_matrix_cols(build_B_c(A,f)[0]))/norm_matrix_cols(build_B_c(A,f)[0]))*eps:.6f})")

    Au_iter = mat_vec_mult(A, u_iter)
    print("A*u =", [round(x,6) for x in Au_iter])
    print("Невязка итерационного решения:", [round(Au_iter[i]-f[i],6) for i in range(4)])

if __name__ == "__main__":
    main()