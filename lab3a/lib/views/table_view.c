#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "table_view.h"

void read_table_size(int *ks1_size, int *ks2_size) {
    printf("Введите размер первого пространства: \n");
    *ks1_size = read_num("Вы ввели некорректный размер!", 0, 100000);
    printf("Введите размер второго пространства: \n");
    *ks2_size = read_num("Вы ввели некорректный размер!", 0, 100000);
}

void read_element(char **data, char **key1, char **key2) {
    printf("Введите информацию:\n");
    *data = get_str();
    printf("Введите ключ 1:\n");
    *key1 = get_str();
    printf("Введите ключ 2:\n");
    *key2 = get_str();
}

void read_keys(char **key1, char **key2) {
    printf("Введите ключ 1:\n");
    *key1 = get_str();
    printf("Введите ключ 2:\n");
    *key2 = get_str();
}

void read_key(char **key) {
    printf("Введите ключ:\n");
    *key = get_str();
}

void read_key_version(char **key, int *version) {
    printf("Введите ключ:\n");
    *key = get_str();
    printf("Введите версию ключа:\n");
    *version = read_num("Вы ввели некорректную версию!", 0, 100000);
}

void check_delete(int result) {
    if (result)
        printf("Элементы были успешно удалены!\n");
    else 
        printf("Элементы для удаления не были найдены!\n");
}

void check_add(int result) {
    if (result)
        printf("Элемент был успешно добавлен!\n");
    else
        printf("Недостаточно места!\n");
}