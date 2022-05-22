#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "node.h"

node_t *create_node(char *key, unsigned int value) {
    node_t *node = malloc(sizeof(node_t));
    node->data = malloc(sizeof(item));
    node->data->key = key;
    node->data->value = value;
    node->data->version = 0;
    node->left = NULL;
    node->right = NULL;
    // если ребенок, то true
    node->right_thread = false;
    node->left_thread = false;
    return node;
}

void insert_node(node_t *parent, node_t *child) {
    node_t *temp = parent;
    node_t *current = NULL;
    while (temp) {
        current = temp;
        if (strcmp(child->data->key, temp->data->key) <=0) {
            if (!temp -> left_thread)
                break;
            temp = temp -> left;
        }
        else {
            if (!temp->right_thread)
                break;
            temp = temp -> right;
        }
    }
    if (strcmp(child->data->key, current->data->key) == 0) {
        node_t *ptr = current;
        while (ptr->left_thread)
            ptr = ptr->left;
        child -> left = ptr -> left;
        child -> right = ptr;
        child->data->version = ptr->data->version + 1;
        ptr -> left_thread = true;
        ptr -> left = child;
    }
    else if (strcmp(child->data->key, current->data->key) < 0) {
        child -> left = current -> left;
        child -> right = current;
        current -> left_thread = true;
        current -> left = child;
    } else {
        child -> right = current -> right;
        child -> left = current;
        current -> right_thread = true;
        current -> right = child;
    }
}
 
void traversal(node_t *node) {
    node_t *current = node;
    do {
        while (current->left_thread) {
            printf("%d ", current->data->value);
            current = current->left;
        }
        printf("%d ", current->data->value);
        while (!current->right_thread) {
            current = current->right;
            if (current == NULL){
                printf("\n");
                return;
            }
        }
        current = current->right;
    } while(current); 
}

node_t *inPred(node_t *ptr)
{
    if (!ptr->left_thread)
        return ptr->left;
    ptr = ptr->left;
    while (ptr->right_thread)
        ptr = ptr->right;
    return ptr;
}


node_t *inSucc(node_t *ptr)
{
    if (!ptr->right_thread)
        return ptr->right;
    ptr = ptr->right;
    while (ptr->left_thread)
        ptr = ptr->left;
    return ptr;
}
 

node_t *caseA(node_t *root, node_t *par, node_t *ptr)
{
	if (par == NULL)
		root = NULL;
	else if (ptr == par->left) {
		par->left_thread = false;
		par->left = ptr->left;
	} else {
		par->right_thread = false;
		par->right = ptr->right;
	}
    //free(ptr->data);
	free(ptr);

}

node_t *caseB(node_t *root, node_t *par,
				node_t *ptr)
{
	node_t *child;

	if (ptr->left_thread)
		child = ptr->left;
	else
		child = ptr->right;

	if (par == NULL)
		root = child;
	else if (ptr == par->left)
		par->left = child;
	else
		par->right = child;

	node_t *s = inSucc(ptr);
	node_t *p = inPred(ptr);
    
	if (ptr->left_thread) 
        p->right = s;
	else if (ptr->right_thread) 
		s->left = p;
    
    //free(ptr->data);
	free(ptr);

}

node_t *caseC(node_t *root, node_t *par,
				node_t *ptr)
{
	node_t *parsucc = ptr;
	node_t *succ = ptr->right;
	while (succ->left_thread) {
		parsucc = succ;
		succ = succ->left;
	}

	ptr->data = succ->data;

	if ((!succ->left_thread) && (!succ->right_thread))
		caseA(root, parsucc, succ);
	else 
		caseB(root, parsucc, succ);
   

}

void delete(node_t *root, char *key)
{
	node_t *par = NULL, *ptr = root;
	int found = 0;
	while (ptr != NULL) {
		if (strcmp(key, ptr->data->key) == 0) {
			found = 1;
			break;
		}
		par = ptr;
		if (strcmp(key,ptr->data->key)<0) {
			if (ptr->left_thread)
				ptr = ptr->left;
			else
				break;
		}
		else {
			if (ptr->right_thread)
				ptr = ptr->right;
			else
				break;
		}
	}

	if (found == 0)
		printf("key not present in tree\n");

	else if (ptr->left_thread && ptr->right_thread)
		caseC(root, par, ptr);

	else if (ptr->left_thread)
		caseB(root, par, ptr);

	else if (ptr->right_thread)
		caseB(root, par, ptr);

	else
		caseA(root, par, ptr);

}

void free_tree(node_t *node) {
    if (!node)
        return;
    if (node->left_thread) 
        free_tree(node->left);
    if (node->right_thread)
        free_tree(node->right);

    free(node->data);
    free(node);
}

node_t **find_duplicates(node_t *head) {
    node_t **ptrs = malloc(2*sizeof(node_t*));
    int count = 1;
    ptrs[0] = count;
    char *key = head->data->key;
    ptrs[1] = head;

    while ((head->left)&&(head->left_thread)){
        if (strcmp(head->left->data->key, key) == 0) {
            count +=1 ;
            ptrs = realloc(ptrs, sizeof(node_t*) * (count+1));
            ptrs[count] = head->left;
            head = head->left;
            ptrs[0] = count;
        }
        else 
            break;
    }
    //free(key);
    return ptrs;
}

node_t **search(node_t *root, char *key) {
    node_t *ptr = root;
    node_t **nodes;
    while (ptr != NULL) {
        if (strcmp(key, ptr->data->key) == 0) {
            nodes = find_duplicates(ptr);
            return nodes;
        }
        if (strcmp(key,ptr->data->key)<0) {
            if (!ptr->left_thread)
                return 0;
            ptr = ptr->left;
        }
        else {
            if (!ptr->right_thread)
                return 0;
            ptr = ptr->right;
        }
    }
}

node_t *find_nearest_max(node_t *node, char *key) {   
    node_t *ptr = node;
    node_t *prev;
    node_t **nodes;
    while (ptr != NULL) {
        if (strcmp(key, ptr->data->key) == 0) 
            return ptr;

        if (strcmp(key,ptr->data->key)<0) {
            if (!ptr->left_thread)
                return prev;
            prev = ptr;
            ptr = ptr->left;
        }
        else {
            if (!ptr->right_thread)
                return ptr;
            prev = ptr;
            ptr = ptr->right;
        }
    }
}