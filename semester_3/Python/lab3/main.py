def typechange(path: str, el_type: type) -> list:
    with open(path, "r", encoding="utf-8") as f:
        data = f.read()
        array = [el_type(i) for i in data.split()]
        return array

def min_counter(array: list) -> int:
    minimum = min(array)
    return array.count(minimum)

def result(path: str, mins: int) -> None:
    with open(path, "w", encoding="utf-8") as f:
        f.write(str(mins))

def main() -> None:
    result("./lab3/output.txt", min_counter(typechange("./lab3/input.txt", int)))

if __name__ == "__main__":
    main()