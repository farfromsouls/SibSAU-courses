#include <iostream>
#include <string>
#include <fstream>
#include "SocialMediaProfile.cpp"
#include <locale.h>

using namespace std;

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");

    string username = "юзернейм";
    string name = "имя";
    string surname = "фамилия";
    int date[3] = {31, 12, 1999};

    // конструкторы
    SocialMediaProfile p1;                                            // по умолчанию
    SocialMediaProfile p2(username, name, surname, 12, 21, date);     // с параметрами
    SocialMediaProfile p3(p2);                                        // копирование

    // istream ostream
    p1.scan(cin);
    p1.print(cout);

    // сеттер и геттер
    p1.setDate(5, 2, 2015);
    const int* gottenDate = p1.getDate();
    cout << "дата поставленная через сеттер и полученная через геттер: "
         << gottenDate[0] << "." << gottenDate[1] << "." << gottenDate[2] << endl;

    // выборка кол-во подписчиков >= n
    int n;
    cout << "Минимум подписчиков для выборки профилей: ";
    cin >> n;
    SocialMediaProfile profiles[] = {p1, p2};
    for (int i = 0; i != 2; i++) {
        if (profiles[i].getFollowers() >= n) {
            cout << profiles[i].getUsername() << ", ";
        };
    };

    // перегрузки операций >> <<
    cout << "\nПерегрузка операции вывода\n" << p1;
    cout << "\nПерегрузка операции ввода\n" ;
    cin >> p1;

    // чтение файла
    ifstream file("input.txt");
    SocialMediaProfile* input_profiles = SocialMediaProfile::readFromFile(file);
    file.close();

    // запись в файл
    ofstream outputFile("output.txt");
    SocialMediaProfile::writeToFile(outputFile, input_profiles, 1); 
    outputFile.close();

    return 0;
}
