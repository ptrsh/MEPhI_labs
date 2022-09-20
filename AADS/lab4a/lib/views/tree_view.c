#include <stdio.h>
#include "tree_view.h"

void file_or_input(int *choice) {
    printf("\n\nЕсли хотите загрузить дерево из файла, то введите 1\nИначе введите 0\n\n");
    *choice = read_num("Вы должны ввести 1 или 0!", 0, 1);
}

void read_node(char **key, int *value) {
    printf("Введите ключ:\n");
    *key = get_str();
    printf("Введите значение:\n");
    *value= read_num("Вы ввели некорректное число!", 0, 2147483647);
}

void read_key(char **key) {
    printf("Введите ключ:\n");
    *key = get_str();
}

void print_nodes(node_t **nodes) {
    printf("\n");
    if (nodes) {
        int count = (int)nodes[0];
        for (int i = 1; i <= count; i++)
            printf("Ключ: %s\nЗначение: %d\nВерсия: %d\n\n", nodes[i]->data->key, nodes[i]->data->value, nodes[i]->data->version);
        printf("\n");
    }
    else {
        printf("Элемент не был найден!\n");
    }
}

void read_key_version(char **key, int *version) {
    printf("Введите ключ:\n");
    *key = get_str();
    printf("Введите версию удаляемого элемента:\n");
    *version = read_num("Вы ввели некорректное число!", 0, 2147483647);
}

void print_tree(node_t *node, int padding, bool right_branch) {
    if (node == NULL) 
        return;
        
    for (int i = 0; i < padding; i += 4)
        printf("│   ");
        
    if (right_branch)
        printf("┕ %d\n", node->data->value);
    else 
        printf("┍ %d\n", node->data->value);

    if (node->left_thread)
        print_tree(node->left, padding + 4, false);
    if (node->right_thread)
        print_tree(node->right, padding + 4, true);
}

void check_delete(int status) {
    if (status)
        printf("Успешно удалено\n");
    else 
        printf("Элемент не был найден\n");
}

void init_message(int tree_from_file) {
    if (tree_from_file)
        printf("Дерево будет загружено из файла\n\n");
    else
        printf("Добавьте первый элемент в дерево\n");
}