import math


def n(p):
    return (-p) * math.log(p, 2)

def main():
    for i in range(1, 100):
        p = i/100
        print(p, n(p))

if __name__ == "__main__":
    main()