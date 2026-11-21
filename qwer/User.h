#ifndef user_h
#define user_h
typedef struct {
    char name[32];
    int hp;
    int max_hp;
    int stamina;
    int max_stamina;
    int gold;
    int userH, userW;
    int inventory[11];
} User;
#endif
