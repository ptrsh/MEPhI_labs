#ifndef READLINE_H
#define READLINE_H

int read_num(char *msg, int min, int max);
char *get_str();
char *get_str_file(FILE *file);

#endif