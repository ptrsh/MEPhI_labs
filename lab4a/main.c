#include <stdio.h>
#include "models/node.h"

int main() {
    node_t *root = create_node("bbbbbbbbb", 9);
    node_t *node1 = create_node("bb", 2);
    node_t *node2 = create_node("b",1);
    node_t *node3 = create_node("bbbbbbbbbbbbbbb", 15);
    node_t *node4 = create_node("a", 0);
    node_t *node5 = create_node("bbbbbb", 6);
    node_t *node6 = create_node("bbbbbbb", 7);
    node_t *node7 = create_node("bbbbbbbbbbbb", 12);
    node_t *node8 = create_node("bbbb", 4);
    node_t *node9 = create_node("bbbbbbbb", 8);
    node_t *node10 = create_node("bbbbbbbbbbbbbbbbb", 17);
    node_t *node11 = create_node("bbbbbbbbbbbbbbbbbb", 18);
    node_t *node12 = create_node("bbbbbbbbbbbbbbbbbbb", 19);
    node_t *node13 = create_node("bbbbbbbbbbb", 11);
    node_t *node14 = create_node("bbbbbbbbbbb", 111);
    node_t *node15 = create_node("bbbbbbbbbbb", 1111);

    insert_node(root, node1);
    insert_node(root, node2);
    insert_node(root, node3);
    insert_node(root, node4);
    insert_node(root, node5);
    insert_node(root, node6);
    insert_node(root, node7);
    insert_node(root, node8);
    insert_node(root, node9);
    insert_node(root, node10);
    insert_node(root, node11);
    insert_node(root, node12);
    insert_node(root, node13);
    insert_node(root, node14);
    insert_node(root, node15);
    
    /*
    delete(root, "bbbbbbbbbbbbbbb");
    delete(root, "bb");
    delete(root, "a");
    delete(root, "bbbbbbbbbbbbbbbbbbb");
    */

    node_t **found_nodes = search(root, "bbbbbbbbbbb");
    if (found_nodes) {
        for (int i = 1; i<=(int)found_nodes[0];i++) {

            printf("%d %s %d", found_nodes[i]->data->value, found_nodes[i]->data->key, found_nodes[i]->data->version);
            printf("\n");
        }
    }
    
    printf("\n");
    free(found_nodes);
    traversal(root);
    node_t *kek = find_nearest_max(root,"bbbbbbbbbbbbbbbb");
    printf("LOL: %d\n", kek->data->value);   

    free_tree(root);
    //printf("\n%d\n", root->right->left->right->key);
    
}