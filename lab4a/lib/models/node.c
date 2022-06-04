#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"

node_t *create_node(char *key, int value) {
    node_t *node = malloc(sizeof(node_t));
    node->data = malloc(sizeof(item));
    node->data->key = key;
    node->data->value = value;
    node->data->version = 0;
    node->left = NULL;
    node->right = NULL;
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
        child -> data -> version = ptr -> data -> version + 1;
        ptr -> left = child;
        ptr -> left_thread = true;
    }
    else if (strcmp(child->data->key, current->data->key) > 0) {
        child -> right = current -> right;
        child -> left = current;
        current -> right = child;
        current -> right_thread = true;
    } else {
        child -> left = current -> left;
        child -> right = current;
        current -> left = child;
        current -> left_thread = true;
    }
}

node_t *get_predecessor(node_t *ptr)
{
    if (!ptr->left_thread)
        return ptr->left;
    ptr = ptr->left;
    while (ptr->right_thread)
        ptr = ptr->right;
    return ptr;
}

node_t *get_successor(node_t *ptr)
{
    if (!ptr->right_thread)
        return ptr->right;
    ptr = ptr->right;
    while (ptr->left_thread)
        ptr = ptr->left;
    return ptr;
}
 
void *delete_leaf(node_t *par, node_t *ptr)
{
    if (ptr == par->left) {
		par->left_thread = false;
		par->left = ptr->left;
	} else {
		par->right_thread = false;
		par->right = ptr->right;
	}
}

void *delete_node_with_1child(node_t *par, node_t *ptr) {
	node_t *child;
    
	if (ptr->left_thread)
		child = ptr->left;
	else
		child = ptr->right;

    if (ptr == par->right)
		par->right = child;
	else
        par->left = child;
		
	node_t *successor = get_successor(ptr);
	node_t *predecessor = get_predecessor(ptr);
    
	if (ptr->left_thread) 
        predecessor->right = successor;
	else if (ptr->right_thread) 
		successor->left = predecessor;

}

void *delete_node_with_2childs(node_t *ptr) {

	node_t *tmp = ptr;
	node_t *successor = ptr->right;

	while (successor->left_thread) {
		tmp = successor;
		successor = successor->left;
	}

    free(ptr->data->key);
    free(ptr->data);
	ptr->data = successor->data;

	if ((!successor->left_thread) && (!successor->right_thread))
		delete_leaf(tmp, successor);
	else 
		delete_node_with_1child(tmp, successor);
    
    free(successor);  
}

int delete(node_t *root, char *key, int version) {
	node_t *par = NULL, *ptr = root;
	bool found = false;

	while (ptr != NULL) {
		if (strcmp(key, ptr->data->key) == 0) {
            if (ptr->data->version == version) {
                found = true;
                break;
            } else {
                while((ptr->data->version != version)) {
                    par = ptr;
                    ptr = ptr->left;
                }
                found = true;
                break;
            }
        }
		
		par = ptr;
		if (strcmp(key,ptr->data->key)>0) {
			if (ptr->right_thread)
				ptr = ptr->right;
			else
				break;
		}
		else {
			if (ptr->left_thread)
				ptr = ptr->left;
			else
				break;
		}
	}

	if (!found)
		return 0;
        
	else if (ptr->left_thread && ptr->right_thread) {
		delete_node_with_2childs(ptr);
        return 1;
    }
	else if ((ptr->left_thread)||(ptr->right_thread))
		delete_node_with_1child(par, ptr);
	else
		delete_leaf(par, ptr);

    free(ptr->data->key);
    free(ptr->data);
    free(ptr);
    return 1;
}

void free_tree(node_t *node) {
    if (!node)
        return;
    if (node->left_thread) 
        free_tree(node->left);
    if (node->right_thread)
        free_tree(node->right);

    free(node->data->key);
    free(node->data);
    free(node);
}

node_t **find_next_duplicates(node_t *head) {
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
    return ptrs;
}

node_t **find_prev_duplicates(node_t *head) {
    node_t **ptrs = malloc(2*sizeof(node_t*));
    int count = 1;
    ptrs[0] = count;
    char *key = head->data->key;
    ptrs[1] = head;

    if (!head->right_thread) {

        while (strcmp(head->left->data->key, key)==0) {
            count +=1;
            ptrs = realloc(ptrs, sizeof(node_t*) * (count+1));
            ptrs[count] = head->left;
            ptrs[0] = count;
            head = head->left;
        }
        return ptrs;
    }
    return ptrs;
}

node_t **search(node_t *root, char *key) {
    node_t *ptr = root;
    node_t **nodes;
    while (ptr != NULL) {
        if (strcmp(key, ptr->data->key) == 0) {
            nodes = find_next_duplicates(ptr);
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

node_t **find_nearest_max(node_t *node, char *key) { 
    node_t *ptr = node;
    node_t *prev;
    node_t **nodes;
    while (ptr != NULL) {
        if (strcmp(key, ptr->data->key) == 0) {
            nodes = find_next_duplicates(ptr);
            return nodes;
        }
        if (strcmp(key,ptr->data->key)<0) {
            if (!ptr->left_thread) {
                nodes = find_prev_duplicates(prev);
                return nodes;
            }
            prev = ptr;
            ptr = ptr->left;
        }
        else {
            if (!ptr->right_thread) {
                nodes = find_prev_duplicates(ptr);
                return nodes;
            }
            prev = ptr;
            ptr = ptr->right;
        }
    }
}

void traversal_tree(node_t *node) {
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


void write_node(node_t *node) {
    FILE *file = fopen("tree.dot", "a+");
    if (node->left != NULL) {
        fprintf(file, "%d[%d] -> %d[%d] ", node->data->value, node->data->version, node->left->data->value, node->left->data->version);
        fclose(file);
        write_node(node->left);
    } else if (node->right != NULL) {
        fprintf(file, "%d[%d] -> %d[%d] ", node->data->value, node->data->version, node->right->data->value, node->right->data->version);
        fclose(file);
        write_node(node->right);
    } else {
        fprintf(file, "%d[%d] ", node->data->value, node->data->version);
        fclose(file);
    }

}
