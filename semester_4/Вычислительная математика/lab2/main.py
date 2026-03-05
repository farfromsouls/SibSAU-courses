import matplotlib.pyplot as plt

def gauss(A, b):
        n = len(A)
        M = [A[i][:] + [b[i]] for i in range(n)]

        for k in range(n):
            max_row = max(range(k, n), key=lambda i: abs(M[i][k]))
            M[k], M[max_row] = M[max_row], M[k]
            for i in range(k + 1, n):
                factor = M[i][k] / M[k][k]
                for j in range(k, n + 1):
                    M[i][j] -= factor * M[k][j]

        x = [0.0] * n
        for i in range(n - 1, -1, -1):
            s = M[i][n]
            for j in range(i + 1, n):
                s -= M[i][j] * x[j]
            x[i] = s / M[i][i]
        return x

def main():
    x = [0.218, 0.559, 0.900, 1.242, 1.583, 1.924, 2.266, 2.607, 2.948]
    f = [-0.169, -1.599, -1.064, -0.124, 0.302, -0.045, -0.780, -0.859, 1.405]
    n = len(x)
    p = 4
    m = p + 1  

    A = [[0.0] * m for _ in range(m)]
    b = [0.0] * m
    for i in range(n):
        xi = x[i]
        fi = f[i]
        powers = [1.0]
        for j in range(1, 2 * p + 1):
            powers.append(powers[-1] * xi)
        for j in range(m):
            for k in range(m):
                A[j][k] += powers[j + k]
            b[j] += fi * powers[j]

    u = gauss(A, b)
    for j, coef in enumerate(u):
        print(f"u{j} = {coef:.6f}")

    r = []
    print("\nНевязки:")
    for i in range(n):
        val = sum(u[j] * (x[i] ** j) for j in range(m))
        rk = val - f[i]
        r.append(rk)
        print(f"r_{i+1} = {rk:.6f}")

    x_min, x_max = min(x), max(x)
    x_plot = [x_min + (x_max - x_min) * t / 200 for t in range(201)]
    y_plot = [sum(u[j] * (xp ** j) for j in range(m)) for xp in x_plot]

    plt.figure(figsize=(8, 5))
    plt.plot(x_plot, y_plot, label='полином', linewidth=2)
    plt.scatter(x, f, color='red', label='табличные значения', zorder=5)
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    main()