#include <stdio.h>
#include "tree_view.h"

void file_or_input(int *choice) {
    printf("\n\nЕсли хотите загрузить дерево из файла, то введите 1\nИначе введите 0\n\n");
    *choice = read_num("Вы должны ввести 1 или 0!", 0, 1);
}

void read_node(int *key, char **info) {
    printf("Введите ключ:\n");
    *key = read_num("Вы ввели некорректное число!", 0, 2147483647);
    printf("Введите информацию:\n");
    *info = get_str();
}

void read_key(int *key) {
    printf("Введите ключ:\n");
    *key = read_num("Вы ввели некорректное число!", 0, 2147483647);
}

void read_number(int *num) {
    printf("Введите число разрядов:\n");
    *num = read_num("Вы ввели некорректное число!", 0, 2147483647);
}

void print_nodes(node_t **nodes) {
    if (nodes[0])
        printf("Подходящие элементы:\n[1]\nКлюч: %d\nИнформация: %s\n\n[2]\nКлюч: %d\nИнформация: %s\n", nodes[0]->key, nodes[0]->info, nodes[1]->key, nodes[1]->info);
    else
        printf("Подходящий элемент:\nКлюч: %d\nИнформация: %s\n", nodes[1]->key, nodes[1]->info);
}
void print_node(node_t *node) {
    printf("Ключ: %d\nИнформация: %s\n", node->key, node->info);
}
void print_tree(node_t *node, int padding, bool right_branch) {
    if (node == NULL) 
        return;
        
    for (int i = 0; i < padding; i += 4)
        printf("│      ");
        
    if (right_branch)
        printf("┕ %d(%s)\n", node->key, node->info);
    else 
        printf("┍ %d(%s)\n", node->key, node->info);

    if (node->left)
        print_tree(node->left, padding + 4, false);
    if (node->right)
        print_tree(node->right, padding + 4, true);
}

void init_message(int tree_from_file) {
    if (tree_from_file)
        printf("Дерево будет загружено из файла\n\n");
    else
        printf("Добавьте первый элемент в дерево\n");
}