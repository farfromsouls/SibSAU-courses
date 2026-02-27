#include <iostream>
using namespace std;

struct Laptop {
    string company;
    double weight;
    int cost;
};

void inputLaptop(Laptop& laptop) {
    cout << "company name: ";
    cin >> laptop.company;
    cout << "weight (kg): ";
    cin >> laptop.weight;
    cout << "price: ";
    cin >> laptop.cost;
}

void printLaptop(const Laptop& laptop) {
    cout << "company: " << laptop.company << endl;
    cout << "weight: " << laptop.weight << " kg" << endl;
    cout << "price: " << laptop.cost << " rub\n" << endl;
}

void fillLaptops(Laptop laptops[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << "laptop #" << i + 1 << ":" << endl;
        inputLaptop(laptops[i]);
    }
}

void printLaptops(const Laptop laptops[], int size) {
    cout << "\n\nLaptop list:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "\nLaptop #" << i + 1 << ":" << endl;
        printLaptop(laptops[i]);
    }
}

void viborka(const Laptop laptops[], int weight, int cost,  int size) {

    for (int i = 0; i < size; ++i) {
        if (laptops[i].weight <= weight && laptops[i].cost <= cost){
            printLaptop(laptops[i]);
        }
    }
}

int main() {
    int N;
    cout << "Enter number of laptops: ";
    cin >> N;
    
    Laptop* laptops = new Laptop[N];
    fillLaptops(laptops, N);
    printLaptops(laptops, N);
    int weight;
    int cost;
    cout << "Enter condition weight: ";
    cin >> weight;
    cout << "Enter condition cost: ";
    cin >> cost;
    viborka(laptops, weight, cost, N);
    
    delete[] laptops;
    return 0;
}