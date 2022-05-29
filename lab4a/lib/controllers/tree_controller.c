#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree_controller.h"

node_t *load_from_file() {
    FILE *file = fopen("data.txt", "r");

    char *key = get_str_file(file);
    char *value_str = get_str_file(file);
    int value = atoi(value_str);
    free(value_str);
    node_t *root = create_node(key, value);

    while (!feof(file)) {
        key = get_str_file(file);
        value_str = get_str_file(file); 
        if (key && value_str) {
            value = atoi(value_str);
            free(value_str);
            node_t *node = create_node(key, value);
            insert_node(root, node);
        }
          
    }

    fclose(file);
    return root;
}

void init_tree(node_t **root) {
    int tree_from_file;
    file_or_input(&tree_from_file);
    init_message(tree_from_file);
    if (tree_from_file) {
        *root = load_from_file();
    }
    else {
        char *key;
        int value;
        read_node(&key, &value);
        *root = create_node(key, value);
    }

}

void add_element(node_t *root) {
    char *key;
    int value;
    read_node(&key, &value);
    node_t *node = create_node(key, value);
    insert_node(root, node);
}

void search_by_key(node_t *root) {
    char *key;
    read_key(&key);
    node_t **nodes = search(root, key);
    print_nodes(nodes);
    free(nodes);
    free(key);
}

void special_search_by_key(node_t *root) {
    char *key;
    read_key(&key);
    node_t **nodes = find_nearest_max(root, key);
    print_nodes(nodes);
    free(nodes);
    free(key);
}

void delete_by_key(node_t *root) {
    char *key;
    int version;
    read_key_version(&key, &version);
    int delete_status = delete(root, key, version);
    check_delete(delete_status);
    free(key);
}

void traversal(node_t *root) {
    traversal_tree(root);
}

void print(node_t *root) {
    print_tree(root, 0, false);
} 

char *generate_random_key() {
    int size = rand() % 6 + 1;
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    char *str = calloc(sizeof(char), size);

    for (int i = 0; i < size - 1; i++) {
        int key = rand() % 36;
        str[i] = charset[key];
    }
    if (strlen(str) > 0) 
        return str;
    
    free(str);
    generate_random_key();
}

void timing(node_t *node) {
    node_t *root = create_node("root", 1);
    int n = 10, k, cnt=20000, m;
    char *keys[1000];
    clock_t first, last;
    srand(time(NULL));
    while (n) {
        n -= 1;
        for (int i = 0; i < 1000; ++i) 
            keys[i] = generate_random_key();
        
        for (int i = 0; i < cnt; i++) {
            char *key = generate_random_key();
            node_t *tmp = create_node(key, sizeof(key));
            insert_node(root, tmp);
        }
        m = 0;
        first = clock();
        for (int i = 0; i < 1000; ++i) {
            node_t **nodes = search(root, keys[i]);
            if (nodes)
                ++m;
            free(nodes);
        }
        last = clock();
        printf("%d элементов было найдено\n", m);
        printf("тест #%d, количество узлов = %d, время = %ld\n", 10 - n, (10 - n)*cnt, last - first);
    }
    
    //free_tree(root);
}