#include "../models/keyspace1.h"
#include "common_helper.h"

#ifndef KEYSPACE1_HELPER_H
#define KEYSPACE1_HELPER_H

unsigned long file_add_keyspace1(KeySpace1 *keySpace);
KeySpace1 *file_load_keyspace1(unsigned long ptr);
void file_update_keyspace1(KeySpace1 *keySpace, unsigned long ptr);

#endif 
