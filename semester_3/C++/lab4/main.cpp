#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <locale.h>
#include <windows.h>

using namespace std;

class TextProcessor {
private:
    map<string, int> wordCount;
    
    bool hasDoubledLetters(const string& word) {
        if (word.length() < 2) return false;
        
        for (size_t i = 0; i < word.length() - 1; i++) {
            if (tolower(word[i]) == tolower(word[i + 1])) {
                return true;
            }
        }
        return false;
    }
    
    string cleanWord(const string& word) {
        string cleaned;
        for (char c : word) {
            if (isalpha((unsigned char)c)) {
                cleaned += tolower((unsigned char)c);
            }
        }
        return cleaned;
    }
    
    static bool compareByCount(const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    }

public:
    bool processFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла: " << filename << endl;
            return false;
        }
        
        string line;
        wordCount.clear();
        
        while (getline(file, line)) {
            istringstream iss(line);
            string word;
            
            while (iss >> word) {
                string cleanedWord = cleanWord(word);
                
                if (cleanedWord.empty() || cleanedWord.length() < 2) continue;
                
                if (hasDoubledLetters(cleanedWord)) {
                    wordCount[cleanedWord]++;
                }
            }
        }
        
        file.close();
        return true;
    }
    
    void printResults(int NUM) {
        vector<pair<string, int>> sortedWords;
        
        for (const auto& pair : wordCount) {
            if (pair.second >= NUM) {
                sortedWords.push_back(pair);
            }
        }
        
        if (sortedWords.empty()) {
            cout << "Нет слов с удвоенными буквами, встречающихся " << NUM << " или более раз." << endl;
            return;
        }
        
        sort(sortedWords.begin(), sortedWords.end(), compareByCount);
        
        cout << "Слова с удвоенными буквами (встречаются " << NUM << " или более раз):" << endl;
        
        for (const auto& pair : sortedWords) {
            cout << pair.first << " : " << pair.second << " раз(а)" << endl;
        }
    }
};

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    TextProcessor processor;
    string filename;
    int NUM;
    
    cout << "Введите имя файла для обработки: ";
    getline(cin, filename);
    
    if (!processor.processFile(filename)) {
        return 1;
    }
    
    cout << "Введите минимальное количество вхождений (NUM): ";
    cin >> NUM;
    
    processor.printResults(NUM);
    
    return 0;
}
