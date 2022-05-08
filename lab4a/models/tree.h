#ifndef tree_H
#define tree_H

typedef struct tree {
    int key;
    int value;
    int version;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
} tree_t;

tree_t *treeInit(int key, int value);
tree_t *treeSelect(tree_t *tree, int key);
tree_t *treeSelectMin(tree_t *tree);
int tree_IsDuplicated(tree_t *tree);
void treeInsert(tree_t *tree, tree_t *node);
void treeDrop(tree_t *tree);
void treeFree(tree_t *tree);

#endif 
