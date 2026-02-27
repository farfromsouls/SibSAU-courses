import math
import matplotlib.pyplot as plt 


def H(X):
    H = 0
    for p in X:
        if p > 0: 
            H -= p * math.log(p, 2)
    return H

def main():
    x = {}
    n = 0
    text = open("lab1/text.txt", "r", encoding="utf-8").read()

    for i in text:
        symbol = i.lower()

        if symbol in "абвгдеёжзийклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyz ":
            if symbol not in x:
                x[symbol] = 1
            else:
                x[symbol] += 1
            n += 1

    X = [i/n for i in x.values()]
    entr = H(X)

    print("Энтропия: ", entr)

if __name__ == "__main__":
    main()