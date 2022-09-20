#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "../other/readline.h"

void print_menu() {
    printf("+---------------+--------------------------------+\n");
    printf("| Номер команды |            Команда             |\n");
    printf("+===============+================================+\n");
    printf("|             0 | Выход                          |\n");
    printf("|             1 | Добавить элемент               |\n");
    printf("|             2 | Поиск по (key1, key2)          |\n");
    printf("|             3 | Поиск по key1                  |\n");
    printf("|             4 | Поиск по key2                  |\n");
    printf("|             5 | Удалить по (key1, key2)        |\n");
    printf("|             6 | Удалить по key1                |\n");
    printf("|             7 | Удалить по key2                |\n");
    printf("|             8 | Реорганизовать 1е пространство |\n");
    printf("|             9 | Сфoрмировать новую таблицу из  |\n");
    printf("|               | элементов 2го пространства     |\n");
    printf("|            10 | Вывести таблицу                |\n");
    printf("+---------------+--------------------------------+\n");
    printf("Введите команду:\n");
}

int dialog() {
    print_menu();
    int input = read_num("Вы должны ввести число от 0 до 11! Попробуйте ещё раз:", 0, 11);
    return input;
}