#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#pragma warning(disable : 4996)
#include "Map.h"
#include "User.h"
#include "Utils.h"

void load_item_names();
		

int main()
{
	int current_day = 1;
	int current_hour = 8;
	User* u = NULL;
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	int user_action;
	load_item_names();

	while (1)
	{
		printf("Привет, %s! Что же ты хочешь сделать?\n 0 - выход, 1 - создать перссонажа, 2 - карточка персонажа 3 - управлять временем, "
			"4 - показать инвентарь\n 5 - поработать, 6 - положить предмет в инвентарь 7 - выбросить предмет из инвентаря "
			"8 - уникальные находеи\n 9 - поиск по имени, 10 - записать в дневничок \n, 11 - Где НПС, 12 - отправится в приключение\n", u->name);
		while (1) {
			if (scanf("%d", &user_action) != 1) {
				scanf("%*s");
				printf("Дурак. Введи число от 0 до 9 \n");
			}
			else {
				break;
			}
		}
		switch (user_action)
		{
		case EEExit:
			printf("Пока! \n");
			exit(0);
		case User_create:
			u = create_user(u);
			break;
		case User_card:
			user_card(u, current_day, current_hour);
			break;
		case Control_hour:
			printf("Ты хочешь: 1 - посмотреть время, 2 - пропустить время (но дальше 02:00 нельзя за раз), 3 - Спать\n");
			int choice;
			while (1) {
				if (scanf("%d", &choice) != 1) {
					scanf("%*s");
					printf("Дурак. Введи число от 0 до 9 \n");
				}
				else {
					break;
				}
			}
			if (choice == 1) {
				printf("Сейчас: %d день, %d часов \n", current_day, current_hour);
				break;
			}
			else if (choice == 2) {
				skip_time(&current_day, &current_hour);
				break;
			}
			else if (choice == 3) {
				slepp(u, &current_day, &current_hour);
				break;
			}
		case Wooork:
			case_2(&current_day, &current_hour);
			break;
		case Watch_inventory:
			case_3(u);
			break;
		case Put_in_inventory:
			case_4(u);
			break;
		case Put_out_inventory:
			case_5(u);
			break;
		case Unic_find:
			case_3(u);
			case_6(u);
			break;
		case Find_name:
			find_item(u);
			break;
		case Write_diary:
			save_diary(u);
			break;
		case NPC_were:
			where_NPC(current_hour);
			break;
		case Trip:
			adventure(u, &current_day, &current_hour);
			break;
		default:
			printf("Ты по-моему чё-то перепутал... \n");
			break;
		}
	}
	return 0;
}