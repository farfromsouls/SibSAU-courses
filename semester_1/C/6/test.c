#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    char sur[50];
    char name[50];
    char fname[50];

    printf("Введите ваше ФИО: ");
    scanf("%s %s %s", sur, name, fname);

    printf("Фамилия и инициалы: %c %c.%s.", name[0], fname[0], sur);
}