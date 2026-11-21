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
int current_day = 1;
int current_hour = 8;
static int inventory [10]; //0 ничего 1 дерево 2 камень 3 семена 4 мотыга 5 лейка 6 топор 7 корзина 8 сено 9 лопата
char player_name[33];
struct NPS_Status {
	char name[40];
	char locate[40];
};

void case_2(int* day_ptr, int* hour_ptr) {
	int work_hours;
	printf("щас поработаем... \n");
	printf("сколько изволите работать? \n");

	while (1) {
		if (scanf("%d", &work_hours) != 1) {
			scanf("%*s");
			printf("Дурак. Введи кол-во часов, которое хочешь работать. Целыми числами. \n");
		}
		else {
			break;
		}
	}
	*hour_ptr += work_hours;

	if (*hour_ptr >= 24) {
		*day_ptr += *hour_ptr / 24;
		*hour_ptr = *hour_ptr % 24;
	}
	printf("Вы успешно поработали %d часов! Сейчас %d день, %d часов. \n ", work_hours, *day_ptr, *hour_ptr);
}

void save_diary(void) {
	User u;
	FILE* diary = fopen("diary.txt", "a");
	if (diary == NULL) {
		printf("Ошибочка, ни создать, ни открыть файл не получилось");
		return;
	}
	printf("Записываем в дневничочек...\n");
	printf("Имя -- %s\n", player_name);
	printf("День -- %d Время -- %d:00\n", current_day, current_hour);
	case_3(&u);
	fprintf(diary, "Записываем в дневничочек...\n");
	fprintf(diary, "Имя -- %s\n", player_name);
	fprintf(diary, "День -- %d Время -- %d:00\n", current_day, current_hour);
	fprintf(diary, "Вот ваш инвентарь: \n");
	for (int num = 0; num < 10; num++)
	{
		if (num >= 0 && num < 10) {
			fprintf(diary, "%d слот -- %s \n", num + 1, item_names[inventory[num]]);
		}
	}
	fprintf(diary, "\n");
	fclose(diary);
}

void where_NPC(int hour) {
	FILE* input = fopen("input.txt", "r");
	if (input == NULL) {
		printf("Не могу открыть input.txt\n");
		return;
	}
	char line[120];
	char npc_name[100];
	char locate[100];
	int time1;
	int time2;
	int npc_count = 0;
	struct NPS_Status nps_list[10];
	while (fgets(line, sizeof(line), input) != NULL) {
		int res = sscanf(line, "%99[^;];%d;%d;%99[^;\n\r]", npc_name, &time1, &time2, locate);
		if (res == 4) {
			int index = -1;
			for (int i = 0; i < npc_count; i++) {
				if (strcmp(nps_list[i].name, npc_name) == 0) {
					index = i;
					break;
				}
			}
			if (index == -1 && npc_count < 10) {
				index = npc_count;
				strncpy(nps_list[index].name, npc_name, 39);
				nps_list[index].name[39] = '\0';

				strncpy(nps_list[index].locate, "Спит дома", 39);
				nps_list[index].locate[39] = '\0';

				npc_count++;
			}

			if (index != -1 && hour >= time1 && hour < time2) {
				strncpy(nps_list[index].locate, locate, 39);
				nps_list[index].locate[39] = '\0';
			}
		}
	}
	fclose(input);
	printf("Сейчас %d час, где же наши нпс?\n", hour);

	FILE* output = fopen("output.txt", "a");
	if (output == NULL) {
		printf("Не могу открыть файл output.txt для записи\n");
		return;
	}

	for (int i = 0; i < npc_count; i++) {
			printf("%s сейчас тусит тут: %s\n", nps_list[i].name, nps_list[i].locate);
			fprintf(output, "%s сейчас тусит тут: %s\n", nps_list[i].name, nps_list[i].locate);
	}

	fclose(output);
}

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
	User u = { 0 };
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	int user_action;
	printf("Как тебя зовут, юный фермер?\n");
	fgets(player_name, 32, stdin);
	player_name[strcspn(player_name, "\n")] = '\0';
	load_item_names();

	while (1)
	{
		printf("Привет, %s! Что же ты хочешь сделать?\n 0 - выход, 1 - посмотреть на часы, 2 - поработать 3 - посмотреть инвентарь, "
			"4 - положить предмет в слот,\n 5 - выбросить предмет, 6 - уникальные находки, 7 - поиск предмета в сумке, "
			"8 - запись в дневничок,\n 9 - посмотреть, где сейчас тусят нпс, 10 - отправится в приключение \n", player_name);
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
			save_diary();
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