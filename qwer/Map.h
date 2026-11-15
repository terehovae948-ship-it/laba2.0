#ifndef map_h
#define map_h
#define wall '#'
#define user '@'
#define empty '.'
#define exit '0'
#define fier 'K'
typedef struct {
	int height, width;
	char** maap;
	int location;
}map;
void init_m(map *m);
void generate(map* m, int location);
void render(const map* m, int userH, int userW, int distance);
int is_walk(const map* m, int h, int w);
char get_tile(const map* m, int h, int w);
void free(map* m);
#endif