#include <iostream>
#include <windows.h>
#include <locale.h>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

long global_comparisons = 0;
long global_swaps = 0;

void reset_counts() {
    global_comparisons = 0;
    global_swaps = 0;
}

// генерация файла
void generate_file(const string& filename, int size, int type, int x1 = 0, int x2 = 1000000) {
    ofstream fout(filename);
    if (type == 1) { // случайные
        for (int i = 0; i < size; i++) {
            int val = rand() % (x2 - x1 + 1) + x1;
            fout << val << " ";
        }
    } else if (type == 2) { // упорядоченные
        for (int i = 0; i < size; i++) {
            fout << i << " ";
        }
    } else if (type == 3) { // обратный порядок
        for (int i = size; i > 0; i--) {
            fout << i << " ";
        }
    }
    fout.close();
}

// скопировать файл
void copy_file(const string& src, const string& dst) {
    ifstream fin(src);
    ofstream fout(dst);
    int x;
    while (fin >> x) {
        fout << x << " ";
    }
    fin.close();
    fout.close();
}

// проверка на отсортированность
bool is_sorted(const string& filename) {
    ifstream fin(filename);
    int prev, cur;
    if (!(fin >> prev)) return true;
    while (fin >> cur) {
        global_comparisons++;
        if (prev > cur) {
            fin.close();
            return false;
        }
        prev = cur;
    }
    fin.close();
    return true;
}

// ------------------------------------------------------------
// прямое слияние
void straight_merge_sort(const string& input_file, const string& output_file) {
    reset_counts();
    
    string f1 = "temp1.txt", f2 = "temp2.txt", f3 = "temp3.txt", f4 = "temp4.txt";
    copy_file(input_file, f1);
    
    int series_len = 1;
    bool done = false;
    
    while (!done) {
        // разбиваем f1 на f2 и f3 по series_len
        ifstream fin(f1);
        ofstream fout2(f2), fout3(f3);
        int count = 0;
        int val;
        bool to_f2 = true;
        while (fin >> val) {
            if (to_f2)
                fout2 << val << " ";
            else
                fout3 << val << " ";
            count++;
            if (count == series_len) {
                count = 0;
                to_f2 = !to_f2;
            }
        }
        fin.close();
        fout2.close();
        fout3.close();
        
        // сливаем f2 и f3 в f4
        ifstream fin2(f2), fin3(f3);
        ofstream fout4(f4);
        
        int val2, val3;
        bool have2 = false, have3 = false;
        if (fin2 >> val2) have2 = true;
        if (fin3 >> val3) have3 = true;
        
        while (have2 || have3) {
            int taken2 = 0, taken3 = 0;
            while (taken2 < series_len && have2 && taken3 < series_len && have3) {
                global_comparisons++;
                if (val2 <= val3) {
                    fout4 << val2 << " ";
                    global_swaps++;
                    if (fin2 >> val2) taken2++;
                    else { have2 = false; break; }
                } else {
                    fout4 << val3 << " ";
                    global_swaps++;
                    if (fin3 >> val3) taken3++;
                    else { have3 = false; break; }
                }
            }
            while (taken2 < series_len && have2) {
                fout4 << val2 << " ";
                global_swaps++;
                if (fin2 >> val2) taken2++;
                else { have2 = false; break; }
            }
            while (taken3 < series_len && have3) {
                fout4 << val3 << " ";
                global_swaps++;
                if (fin3 >> val3) taken3++;
                else { have3 = false; break; }
            }
        }
        fin2.close();
        fin3.close();
        fout4.close();
        
        // проверка: если в f1 была одна серия - закончили
        ifstream check(f1);
        int cnt = 0, prev, cur;
        if (check >> prev) {
            cnt++;
            while (check >> cur) {
                if (prev > cur) cnt++;
                prev = cur;
            }
        }
        check.close();
        
        if (cnt == 1) {
            done = true;
            copy_file(f4, output_file);
        } else {
            copy_file(f4, f1);
            series_len *= 2;
        }
    }
    
    remove("temp1.txt");
    remove("temp2.txt");
    remove("temp3.txt");
    remove("temp4.txt");
}

// ------------------------------------------------------------
// естественное слияние
void natural_merge_sort(const string& input_file, const string& output_file) {
    reset_counts();
    
    string f1 = "temp1.txt", f2 = "temp2.txt", f3 = "temp3.txt";
    copy_file(input_file, f1);
    
    while (true) {
        // Разделение на серии
        ifstream in(f1);
        ofstream out2(f2), out3(f3);
        int prev, cur;
        bool to2 = true;
        if (in >> prev) out2 << prev << " ";
        while (in >> cur) {
            global_comparisons++;
            if (cur < prev) to2 = !to2;
            if (to2) out2 << cur << " ";
            else out3 << cur << " ";
            prev = cur;
        }
        in.close(); out2.close(); out3.close();
        
        // Слияние серий
        ifstream in2(f2), in3(f3);
        ofstream out1(f1);
        int a, b;
        bool has2 = (in2 >> a) ? true : false;
        bool has3 = (in3 >> b) ? true : false;
        
        while (has2 || has3) {
            int last = 0;
            bool first = true;
            bool end2 = false, end3 = false;
            
            while (!end2 && !end3 && has2 && has3) {
                if (a <= b) {
                    out1 << a << " ";
                    global_swaps++;
                    last = a;
                    if (!(in2 >> a)) { has2 = false; end2 = true; }
                    else if (!first && a < last) end2 = true;
                } else {
                    out1 << b << " ";
                    global_swaps++;
                    last = b;
                    if (!(in3 >> b)) { has3 = false; end3 = true; }
                    else if (!first && b < last) end3 = true;
                }
                first = false;
            }
            while (!end2 && has2) {
                out1 << a << " ";
                global_swaps++;
                last = a;
                if (!(in2 >> a)) { has2 = false; end2 = true; }
                else if (!first && a < last) end2 = true;
                first = false;
            }
            while (!end3 && has3) {
                out1 << b << " ";
                global_swaps++;
                last = b;
                if (!(in3 >> b)) { has3 = false; end3 = true; }
                else if (!first && b < last) end3 = true;
                first = false;
            }
        }
        in2.close(); in3.close(); out1.close();
        
        if (is_sorted(f1)) {
            copy_file(f1, output_file);
            break;
        }
    }
    
    remove("temp1.txt");
    remove("temp2.txt");
    remove("temp3.txt");
}

// ------------------------------------------------------------
int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    srand(time(NULL));
    
    while (true) {
        int a;
        cout << "Выберите режим: (1) сортировка файла (2) сбор статистики: ";
        cin >> a;
        
        if (a == 1) {
            int len, x1, x2, method;
            string filename;
            cout << "размер: ";
            cin >> len;
            cout << "диапазон (min max): ";
            cin >> x1 >> x2;
            cout << "метод (1-прямое слияние, 2-естественное слияние): ";
            cin >> method;
            cout << "имя файла: ";
            cin >> filename;
            
            generate_file(filename + "_unsorted.txt", len, 1, x1, x2);
            
            if (method == 1)
                straight_merge_sort(filename + "_unsorted.txt", filename + "_sorted.txt");
            else
                natural_merge_sort(filename + "_unsorted.txt", filename + "_sorted.txt");
            
            cout << "сравнения: " << global_comparisons << ", перестановки: " << global_swaps << endl;
            
        } else if (a == 2) {
            int type, beg, end, step, method;
            string fname;
            cout << "тип данных (1-случ,2-упор,3-обрат): ";
            cin >> type;
            cout << "диапазон размеров и шаг (начало конец шаг): ";
            cin >> beg >> end >> step;
            cout << "метод (1-прямое,2-естественное): ";
            cin >> method;
            cout << "имя файла для результатов: ";
            cin >> fname;
            
            ofstream res(fname + ".txt");
            
            for (int sz = beg; sz <= end; sz += step) {
                string tin = "temp_in.txt";
                generate_file(tin, sz, type);
                
                auto start = high_resolution_clock::now();
                if (method == 1)
                    straight_merge_sort(tin, "temp_out.txt");
                else
                    natural_merge_sort(tin, "temp_out.txt");
                auto stop = high_resolution_clock::now();
                auto dur = duration_cast<microseconds>(stop - start);
                
                res << "N=" << sz << " time=" << dur.count() << endl;
                cout << "готово N=" << sz << endl;
            }
            res.close();
        }
    }
    return 0;
}