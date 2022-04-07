#include "../models/table_model.h"
#include "../views/table_view.h"
#include "../views/key_view.h"
#include "../views/item_view.h"
#include "../views/keyspace_view.h"

#ifndef TABLE_CONTROLLER_H
#define TABLE_CONTROLLER_H

void create_table(Table **table);
void add_element(Table *table);
void search_by_keys(Table *table);
void search_in_ks1(Table *table);
void search_in_ks2(Table *table);  
void delete_by_keys(Table *table); 
void delete_in_ks1(Table *table); 
void delete_in_ks2(Table *table); 
void delete_version_in_ks1(Table *table); 
void reorganise_ks1(Table *table); 
void new_table_from_kp2(Table *table); 
void print_table(Table *table); 

#endif