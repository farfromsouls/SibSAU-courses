#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

class PalindromeFinder
{
private:
    map<string, int> palindromeCount;

    string cleanWord(const string &word)
    {
        string cleaned;
        for (char c : word)
        {
            if (isalpha(c))
            {
                cleaned += tolower(c);
            }
        }
        return cleaned;
    }

    bool isPalindrome(const string &word)
    {
        if (word.length() < 2)
            return false;

        string reversed = word;
        reverse(reversed.begin(), reversed.end());

        return word == reversed;
    }

public:
    void findPalindromes(const string &text)
    {
        istringstream stream(text);
        string word;

        while (stream >> word)
        {
            string cleanedWord = cleanWord(word);

            if (!cleanedWord.empty() && isPalindrome(cleanedWord))
            {
                palindromeCount[cleanedWord]++;
            }
        }
    }

    void printResults()
    {
        if (palindromeCount.empty())
        {
            cout << "В тексте не найдено слов-палиндромов." << endl;
            return;
        }

        int totalPalindromes = 0;
        for (const auto &pair : palindromeCount)
        {
            cout << "слово: \"" << pair.first << "\"";
            cout << "встречается " << pair.second << " раз";
            cout << (pair.second == 1 ? "" : "а") << endl;
        }
        cout << "Всего найдено " << palindromeCount.size()
             << " уникальных слов-палиндромов" << endl;
    }
};

string readTextFromFile(const string &filename)
{
    ifstream inputFile(filename);
    string text;
    string line;
    int lineCount = 0;

    while (getline(inputFile, line))
    {
        lineCount++;
        if (line.length() > 80)
        {
            cerr << "" << lineCount
                 << " превышает 80 символов (" << line.length() << " символов)" << endl;
        }

        text += line + " ";
    }

    inputFile.close();

    if (lineCount < 10)
    {
        cerr << "Ошибка: В файле должно быть не менее 10 строк. Найдено: " << lineCount << endl;
        return "";
    }

    cout << "Файл прочитан, количеств строк" << lineCount << endl;
    return text;
}

int main()
{
    const string inputFilename = "input.txt";
    string inputText = readTextFromFile(inputFilename);
    {
        PalindromeFinder finder;
        finder.findPalindromes(inputText);
        finder.printResults();

        return 0;
    }
};