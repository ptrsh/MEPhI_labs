#include "../models/table.h"

#ifndef TABLE_CONTROLLER_H
#define TABLE_CONTROLLER_H

void add_element(Table *table);
void search_by_keys(Table *table);
void search_in_ks1(Table *table);
void search_in_ks2(Table *table);  
void delete_by_keys(Table *table); 
void delete_in_ks1(Table *table); 
void delete_in_ks2(Table *table); 
void reorganise_ks2(Table *table); 
void new_table_from_kp2(Table *table); 
void print_table(Table *table); 

#endif 
