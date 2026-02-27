#include <iostream>
#include <string>

using namespace std;


class SocialMediaProfile {
private:
    string username, name, surname;
    int followers, follows;
    int date[3];

public:
// без параметров
    SocialMediaProfile() { 
        username  = "";
        name      = "";
        surname   = "";
        followers = follows = date[0] = date[1] = date[2] = 0;
    };

// с параметрами
    SocialMediaProfile(string _un, string _n, string _sn, int _f1, int _f2, int _d[3]) { 
        username   = _un;
        name       = _n;
        surname    = _sn;
        followers  = _f1;
        follows    = _f2;
        memcpy(date, _d, 3 * sizeof(int));
    };

// копирование
    SocialMediaProfile(const SocialMediaProfile &t) {
        username   = t.username;
        name       = t.name;
        surname    = t.surname;
        followers  = t.followers;
        follows    = t.follows;
        memcpy(date, t.date, 3 * sizeof(int)); 
    };

// ostream вывод данных
    ostream & print(ostream &out) const {
        out <<"Юзер: "         << username 
            <<"\nИмя: "        << name
            <<"\nФамилия: "    << surname
            <<"\nПодписчики: " << followers
            <<"\nПодписки: "   << follows
            <<"\nДата рег.: "  
            <<date[0]<<"."<<date[1]<<"."<<date[2] << endl;
        return out;
    };

// istream ввод данных
    istream & scan(istream &in) {
        if (&in == &cin) {
            cout << "Введите имя пользователя: ";
            in >> username;
            cout << "Введите имя и фамилию: ";
            in >> name >> surname;

        } else {
            in >> username >> name >> surname >> followers
               >> follows >> date[0], date[1], date[2];
        }
        return in;
    };

// геттеры
    const int* getDate() { return date; };
    const int getFollowers() { return followers; };
    const string getUsername() { return username; };

// сеттер устанавливает дату
    void setDate(int day, int month, int year) {
        date[0] = day;
        date[1] = month;
        date[2] = year;
    };

// перегрузка операторов ввода вывода
    friend ostream & operator <<(ostream &stream, const SocialMediaProfile &obj) {
        return obj.print(stream);
    };

    friend istream & operator >>(istream &stream, SocialMediaProfile &obj) {
        return obj.scan(stream);
    };

// чтение из файла
    static SocialMediaProfile* readFromFile(istream &stream) {
        int count = 0;
        SocialMediaProfile temp;
        while (stream >> temp) {
            //for (int i = 0; i < 7; i++) stream >> temp;
            count++;
        }
        stream.clear();
        stream.seekg(0);
        SocialMediaProfile* profiles = new SocialMediaProfile[count];

        for (int i = 0; i < count; i++) {
            stream >> profiles[i];
        }
        
        return profiles;
    }

// запись в файл
    static void writeToFile(ostream &stream, SocialMediaProfile* profiles, int count) {
        for (int i = 0; i < count; i++) {
            stream << profiles[i];
        }
    }
};