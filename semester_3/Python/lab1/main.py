from random import randint


def main() -> None:
    N = int(input("Введите число элементов:"))
    X = [randint(-100, 100) for i in range(N)]
    max_id = X.index(max(X))
    counter = 0
    for i in range(len(X)-max_id+1):
        if X[i] < 0:
            counter += 1
    print(f"Кол-во отрицательных элементов идущих после максимального = {counter}")
    print("12345"[1:-1])

if __name__ == "__main__":
    main()