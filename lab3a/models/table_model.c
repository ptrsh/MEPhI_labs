#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "table_model.h"

Table *table_init(int ks1_size, int ks2_size) {
    Table *table = (Table*)malloc(sizeof(Table));
    table->ks1 = keyspace_init(ks1_size);
    table->ks2 = keyspace_init(ks2_size);
    table->ks1_size = ks1_size;
    table->ks2_size = ks2_size;
    return table;
}

int table_add(Table* table, char *data, char *key1, char *key2) {
    Item *item1 = item_create(data, key1, key2);
    Item *item2 = item_create(data, key1, key2);
    int kp1_found_position = keyspace1_check(table->ks1, table->ks1_size, key1);
    int kp2_found_position = keyspace2_check(table->ks2, table->ks2_size, key2);
    if ((kp1_found_position == -2)||(kp2_found_position == -2))
        return 0;
    keyspace1_add(table->ks1, kp1_found_position, item1);
    keyspace2_add(table->ks2, kp2_found_position, table->ks2_size, item2);
    return 1;
}

Item *table_search_by_keys(Table *table, char *key1, char *key2) {
    int position = keyspace2_check(table->ks2, table->ks2_size, key2);
    if (position == -1) 
        return 0;

    Key **head = &(table->ks2->keys[position]);
    while (*head) {
        if (strcmp((*head)->item->key1, key1) == 0)
            return (*head)->item;
        head = &(*head)->next;
    }
    return 0;
}

Key *table_search_in_ks1(Table *table, char *key) {
    int position = keyspace1_check(table->ks1, table->ks1_size, key);
    if (position == -1) 
        return 0;
    return table->ks1->keys[position];
}

Key *table_search_in_ks2(Table *table, char *key) {
    int position = keyspace2_check(table->ks2, table->ks2_size, key);
    if (position == -1) 
        return 0; 
    return table->ks2->keys[position];
}

void table_delete_in_ks1(Table *table, char *key) {
    int ks1_found_position = keyspace1_check(table->ks1, table->ks1_size, key);
    if (ks1_found_position < 0)
        return;
    delete_in_ks(table->ks1, ks1_found_position);
}

void table_delete_in_ks2(Table *table, char *key) {
    int ks2_found_position = keyspace2_check(table->ks2, table->ks2_size, key);
    if (ks2_found_position < 0)
        return;
    delete_in_ks(table->ks2, ks2_found_position);
}

void table_delete_version_in_ks1(Table *table, char *key, int version) {
    int ks1_found_position = keyspace1_check(table->ks1, table->ks1_size, key);  
    if ((ks1_found_position < 0))
        return;
    else {
        Key **head = &(table->ks1->keys[ks1_found_position]);
        Key *tmp;
        if ((*head)->item->release == version)
            delete_key_base(head);
        else {
            while (*head) {
                if ((*head)->next->item->release == version){
                    tmp = (*head)->next;
                    if ((*head)->next->next)
                        (*head)->next->next->release -= 1;
                    (*head)->next = tmp->next;
                    item_free(tmp->item);
                    free(tmp);
                    break;
                }
                head = &(*head)->next;
            }
        }
    }
}

void table_reorganise_ks1(Table *table) {
    table->ks1_size = keyspace1_reorganise(table->ks1, table->ks1_size);
}

void table_delete_by_keys(Table *table, char *key1, char *key2) {
    int ks1_found_position = keyspace1_check(table->ks1, table->ks1_size, key1);  
    int ks2_found_position = keyspace2_check(table->ks2, table->ks2_size, key2);
    if ((ks1_found_position < 0) || (ks2_found_position < 0))
        return;
    else {
        Key **head = &(table->ks1->keys[ks1_found_position]);
        Key *tmp;
        if (strcmp((*head)->item->key2, key2) == 0) 
            delete_key_base(head);
        else {
            while (*head) {
                if (strcmp((*head)->next->item->key2, key2) == 0){
                    tmp = (*head)->next;
                    if ((*head)->next->next)
                        (*head)->next->next->release -= 1;
                    (*head)->next = tmp->next;
                    item_free(tmp->item);
                    free(tmp);
                    break;
                }
                head = &(*head)->next;
            }
        }
        Key **head2 = &(table->ks2->keys[ks2_found_position]);
        Key *tmp2;
        if (strcmp((*head2)->item->key1, key1) == 0)
            delete_key_base(head2);
        else {
            while (*head2) {
                if (strcmp((*head2)->next->item->key1, key1) == 0){
                    tmp2 = (*head2)->next;
                    if((*head2)->next->next)
                        (*head2)->next->next->release -= 1;
                    (*head2)->next = tmp2->next;
                    item_free(tmp2->item);
                    free(tmp2);
                    return;
                }
                head2 = &(*head2)->next;
            }
        }
    }
    return;
}

Table *table_new_from_kp2(Table *table, char *key) {
    int position = keyspace2_check(table->ks2, table->ks2_size, key);
    if (position == -1) 
        return 0; 
    Key **head = &(table->ks2->keys[position]);
    Table *new_table = table_init(table->ks1_size, table->ks2_size);
    while (*head) {
        table_add(new_table, (*head)->item->info, (*head)->item->key1, (*head)->item->key2);
        head = &(*head)->next;
    }
    return new_table;
}

void table_free(Table* table) {
    keyspace_free(table->ks1, table->ks1_size);
    keyspace_free(table->ks2, table->ks2_size);
    free(table);
}
