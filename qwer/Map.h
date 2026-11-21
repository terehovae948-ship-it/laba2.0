#ifndef map_h
#define map_h
#define wall '#'
#define user '@'
#define empty '.'
#define Exit '0'
#define fier 'K'

#include "User.h"

typedef struct {
	int height, width;
	char** maap;
	int location;
}map;
void create(map* m, User* u);
void draw(const map* m, User* u, int distance);
void free_(map* m);
#endif