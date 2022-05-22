#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree_controller.h"

node_t *load_from_file() {
    FILE *file = fopen("data.txt", "r");
    node_t *root = NULL;

    while (!feof(file)) {
        char *key_str = get_str_file(file);
        char *info = get_str_file(file); 
        if (key_str && info) {
            int key = atoi(key_str);
            free(key_str);
            node_t *node = create_node(key, info);
            root = insert_node(root, node);
        }
          
    }
    
    fclose(file);
    return root;
}

node_t *init_tree() {
    node_t *root = NULL;
    int tree_from_file;
    file_or_input(&tree_from_file);
    init_message(tree_from_file);
    if (tree_from_file) {
        root = load_from_file();
    }
    else {
        int key;
        char *info;
        read_node(&key, &info);
        node_t *node = create_node(key, info);
        root = insert_node(root, node);
    }
    return root;

}

void add_element(node_t **root) {
    int key;
    char *info;
    read_node(&key, &info);
    node_t *node = create_node(key, info);
    *root = insert_node(*root, node);
}

void search_by_key(node_t **root) {
    int key;
    read_key(&key);
    node_t *node = search(*root, key);
    print_node(node);    
}

void special_search_by_key(node_t **root) {
    int key;
    read_key(&key);
    node_t **nodes = find_most_distant(*root, key);
    print_nodes(nodes);
    free(nodes);
    
}

void delete_by_key(node_t **root) {
    int key;
    read_key(&key);
    *root = delete(*root, key);
}

void traversal(node_t **root) {
    int num;
    read_number(&num);
    printf("\n");
    traversal_tree(*root, num);
}

void print(node_t **root) {
    print_tree(*root, 0, false);
} 

void timing(node_t **node) {
    node_t *root = NULL;
    srand(time(NULL));
    int keys[10000];
    for (int i = 0; i<10000; i++) {
        keys[i] = rand() % 10000 - rand() % 10000;
    }
    

    for (int n = 1; n <=10; n++ ) {
        
        for (int i = 0; i<1000; i++) {
            int k = rand() % 10000 - rand() % 10000;
            node_t *tmp = create_node(k, "test");
            root = insert_node(root, tmp);
        }
        printf("Количество элементов в дереве: %d\n", n*1000);
        clock_t start = clock();
        for (int i = (n-1) * 1000; i < n*1000; i++) {
            node_t *node = search(root, keys[i]);
        }
        clock_t finish = clock();
        printf("Время поиска: %ld\n",finish-start);
    }
    //free_tree(root);
}