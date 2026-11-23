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
    int inventory[10];
    int relic;
} User;

enum Relic {
    No_relic = -1,
    Ring_of_stingy,
    Fast_boots,
    Recover_Armlet,
};

void case_3(const User* u);
void case_4(User* u);
void case_5(User* u);
void case_6(const User* u);
void find_item(const User* u);
User* create_user(User* curr_u);
void free_u(User* u);
void user_card(const User* u, int day, int hour);
#endif
