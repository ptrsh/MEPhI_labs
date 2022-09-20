#include "stdlib.h"
#include "string.h"
#include "city.h"

city_t *city_parse(char *str) {
    city_t *city = malloc(sizeof(city_t));
    char *delim = ",", *word = strtok(str, delim);
    city->name = word;
    word = strtok(NULL, delim);
    city->x = atof(word);
    word = strtok(NULL, delim);
    city->y = atof(word);
    return city;
}
