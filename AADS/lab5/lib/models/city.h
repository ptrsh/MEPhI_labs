#ifndef STATION_H
#define STATION_H

typedef struct city {
    char *name;
    double x;
    double y;
} city_t;

city_t *city_parse(char *str);

#endif 