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

void adventure(void) {
	map m;
	m.maap = NULL;
	m.location = 1;

	User u;
	u.userH = 1;
	u.userW = 1;

	int needNewMap = 1;
	int game = 1;
	int distanse = 1;

	while (1) {
		if (needNewMap == 1) {
			create(&m, &u);
			needNewMap = 0;
		}

		draw(&m, &u, distanse);

		char way = _getch();
		int nextH = u.userH;
		int nextW = u.userW;

		if (way == 'w' || way == 'W') {
			nextH--;
		}
		if (way == 'a' || way == 'A') {
			nextW--;
		}
		if (way == 's' || way == 'S') {
			nextH++;
		}
		if (way == 'd' || way == 'D') {
			nextW++;
		}

		if ((way == 'q' || way == 'Q') && m.maap[u.userH][u.userW] == fier) {
			break;
		}

		if (m.maap[nextH][nextW] != wall && m.maap[nextH][nextW] != 'R' && m.maap[nextH][nextW] != 'T') {
			u.userH = nextH;
			u.userW = nextW;
		}

		if (m.maap[u.userH][u.userW] == Exit) {
			needNewMap = 1;
			distanse++;
			if (m.location == 1) {
				m.location = 0;
			}
			else {
				m.location = 1;
			}
		}
	}

	free_(&m);
}
		

int main()
{
	int current_day = 1;
	int current_hour = 8;
	User u = { 0 };
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	int user_action;
	printf("Как тебя зовут, юный фермер?\n");
	fgets(u.name, 32, stdin);
	u.name[strcspn(u.name, "\n")] = '\0';
	load_item_names();

	while (1)
	{
		printf("Привет, %s! Что же ты хочешь сделать?\n 0 - выход, 1 - посмотреть на часы, 2 - поработать 3 - посмотреть инвентарь, "
			"4 - положить предмет в слот,\n 5 - выбросить предмет, 6 - уникальные находки, 7 - поиск предмета в сумке, "
			"8 - запись в дневничок,\n 9 - посмотреть, где сейчас тусят нпс, 10 - отправится в приключение \n", u.name);
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
		case 0:
			printf("Пока! \n");
			exit(0);
		case 1:
			printf("Сейчас: %d день, %d часов \n", current_day, current_hour);
			break;
		case 2:
			case_2(&current_day, &current_hour);
			break;
		case 3:
			case_3(&u);
			break;
		case 4:
			case_4(&u);
			break;
		case 5:
			case_5(&u);
			break;
		case 6:
			case_3(&u);
			case_6(&u);
			break;
		case 7:
			find_item(&u);
			break;
		case 8:
			save_diary(&u);
			break;
		case 9:
			where_NPC(current_hour);
			break;
		case 10:
			adventure();
			break;
		default:
			printf("Ты по-моему чё-то перепутал... \n");
			break;
		}
	}
	return 0;
}