#ifndef COMMON_HELPER_H
#define COMMON_HELPER_H

#define FILENAME "data.bin"
#define MODE "rb+"

#include "app.h"

typedef unsigned long offset;

void fileInit();

offset fileStringAppend(char *str);

char *fileStringLoad(offset ptr);

#endif // COMMON_HELPER_H
