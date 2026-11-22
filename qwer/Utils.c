#include <stdio.h>
#include <string.h>
#include "Utils.h"
#pragma warning(disable : 4996)

int current_day = 1;
int current_hour = 8;
char item_names[10][15];
void load_item_names(void) {
	int count = 0;
	int id;
	char name[15];
	FILE* file = fopen("items.txt", "r");
	if (file == NULL) {
		printf("А такого файлика-то нет. Ну ладно, так уж и быть, по стандарту тебе что-нибудь оформим.\n");
		char default_item[10][15] = {
			"Ничего", "Дерево", "Камень", "Семена", "Мотыга", "Лейка", "Топор", "Корзина", "Сено", "Лопата"
		};
		for (int i = 0; i < 10; i++) {
			strncpy(item_names[i], default_item[i], 14);
		}
		printf("Оформленно.\n");
		return;
	}
	while (count < 10 && fscanf(file, "%d %[^\n]", &id, name) == 2) {
		if (id >= 0 && id < 10) {
			strncpy(item_names[id], name, 14);
			count++;
		}
	}
	fclose(file);
	printf("Загружено.\n");
}

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

void save_diary(const User* u) {
	FILE* diary = fopen("diary.txt", "a");
	if (diary == NULL) {
		printf("Ошибочка, ни создать, ни открыть файл не получилось");
		return;
	}
	printf("Записываем в дневничочек...\n");
	printf("Имя -- %s\n", u->name);
	printf("День -- %d Время -- %d:00\n", current_day, current_hour);
	case_3(u);
	fprintf(diary, "Записываем в дневничочек...\n");
	fprintf(diary, "Имя -- %s\n", u->name);
	fprintf(diary, "День -- %d Время -- %d:00\n", current_day, current_hour);
	fprintf(diary, "Вот ваш инвентарь: \n");
	for (int num = 0; num < 10; num++)
	{
		if (num >= 0 && num < 10) {
			fprintf(diary, "%d слот -- %s \n", num + 1, item_names[u->inventory[num]]);
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