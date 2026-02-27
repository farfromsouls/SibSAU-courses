import math
import matplotlib.pyplot as plt 


def H2(p):
    Hx = []
    for i in p:
        H = (-i) * math.log(i, 2) - (1-i)*math.log((1-i), 2)
        Hx.append(H)
        print(i, H)
    return Hx

def main():
    p = [i/100 for i in range(1, 100)]
    H = H2(p)

    print("Максимальное значение энтропии: ", max(H))

    plt.plot(p, H)
    plt.show()

if __name__ == "__main__":
    main()