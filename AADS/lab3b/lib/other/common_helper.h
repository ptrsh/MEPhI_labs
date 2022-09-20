#ifndef COMMON_HELPER_H
#define COMMON_HELPER_H

#define FILENAME "data.bin"
#define MODE "rb+"

void init_file();
unsigned long file_add_string(char *str);
char *file_load_string(unsigned long ptr);

#endif 
