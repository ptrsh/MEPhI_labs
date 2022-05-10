#include "../models/item.h"
#include "common_helper.h"

#ifndef ITEM_HELPER_H
#define ITEM_HELPER_H

unsigned long file_add_item(Item *item);
Item *file_load_item(unsigned long ptr);
void file_update_item(Item *item, unsigned long ptr);

#endif 