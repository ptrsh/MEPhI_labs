#ifndef EXTRA_NODE_H
#define EXTRA_NODE_H

typedef struct Node {
    unsigned key;
    unsigned value;
    unsigned height;

    struct Node *left;
    struct Node *right;
} Node;

Node *nodeInit(unsigned key, unsigned value);
Node *nodeInsert(Node *this, unsigned key, unsigned value);
Node *nodeSearch(Node *this, unsigned key);
void nodeFree(Node *this);

#endif 
