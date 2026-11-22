#ifndef utils_h
#define utils_h
#include "User.h"

 struct NPS_Status {
	char name[40];
	char locate[40];
};

 enum Action {
	 EEExit = 0,
	 User_create,
	 User_card,
	 Watch_hour,
	 Watch_inventory,
	 Wooork,
	 Put_in_inventory,
	 Put_out_inventory,
	 Unic_find,
	 Find_name,
	 Write_diary,
	 NPC_were,
	 Trip
};

extern int current_day;
extern int current_hour;
extern char item_names[10][15];
void load_item_names(void);
void case_2(int* day_ptr, int* hour_ptr);
void save_diary(const User* u);
void where_NPC(int hour);
#endif