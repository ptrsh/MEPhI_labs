#include "common_helper.h"
#include "../models/keyspace2.h"

#ifndef KEYSPACE2_HELPER_H
#define KEYSPACE2_HELPER_H

unsigned long file_append_keyspace2(KeySpace2 *keySpace);
KeySpace2 *file_load_keyspace2(unsigned long ptr);
void file_update_keyspace2(KeySpace2 *keySpace, unsigned long ptr);

#endif 
