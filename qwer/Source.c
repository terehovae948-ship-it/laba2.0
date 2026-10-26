#include <stdio.h>
#include <windows.h>
#include <string.h>
#pragma warning(disable : 4996)
int current_day = 1;
int current_hour = 8;
static int inventory [10]; //0 ничего 1 дерево 2 камень 3 семена 4 мотыга 5 лейка 6 топор 7 корзина 8 сено 9 лопата
char item_names[10][15];
char player_name[33];
struct NPS_Status {
	char name[40];
	char locate[40];
};

void find_item(void) {
	char search_item[15];
	int id = -1;
	printf("Введите название искомого предмета: ");
	while (getchar() != '\n' && getchar() != EOF);
	if (fgets(search_item, sizeof(search_item), stdin) == NULL) {
		return;
	}
	search_item[strcspn(search_item, "\n")] = '\0';
	for (int i = 0; i < 10; i++) {
		if (strcmp(item_names[i], search_item) == 0) {
			id = i;
			break;
		}
	}
	if (id == -1) {
		printf("А предмета с названием %s не существует в этой реальности!\n", search_item);
		return;
	}
	int count = 0;
	printf("Ищем %s у тебя в сумке...\n", search_item);
	for (int slot = 0; slot < 10; slot++) {
		if (inventory[slot] == id) {
			printf("Предмет найден в слоте %d\n,", slot + 1);
			count++;
		}
	}
	if (count == 0) {
		printf("У тебя в инвентаре нет этого предмета.\n");
	}
}

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

void case_3(void) {
	printf("Вот ваш инвентарь: \n");
	for (int num = 0; num < 10; num++)
	{
		if (num >= 0 && num < 10) {
			printf("%d слот -- %s \n", num + 1, item_names[inventory[num]]);
		}
	}
}

void case_4(void) {
	int num;
	int item;
	while (1) {
		printf("В какой слот вы хотите положить предмет? \n");
		if (scanf("%d", &num) != 1) {
			scanf("%*s");
			printf("Дурак. Введи номер слота, в который хочешь положить предмет. Целым числом. \n");
			continue;
		}
		if (num < 1 || num > 10) {
			printf("У тебя 10 слотов в инвентаре, от 1 до 10. Какой %d слот? \n", num);
		}
		else {
			break;
		}
	}
	printf("Напоминаю, что: 0 - ничего, 1 - дерево, 2 - камень, 3 - семена, 4 - мотыга, 5 - лейка 6 - топор, 7 - корзина, 8 - сено, 9 - лопата \n");
	while (1) {
		printf("Что вы хотите положить в этот слот? \n");
		if (scanf("%d", &item) != 1) {
			scanf("%*s");
			printf("Дурак. номер желаемого предмета. Целым числом. \n");
			continue;
		}
		if (item < 0 || item > 9) {
			printf("Я кому напоминала, что ID предметов от 0 до 9? Какой %d? \n", item);
		}
		else {
			break;
		}
	}
	inventory[num - 1] = item;
	printf("Круто! Теперь у тебя в %d слоте есть что-то!(или нет) \n", num);
}

void case_5(void) {
	int num;
	while (1) {
		printf("Из какого слота вы хотите выбросить предмет? \n");
		if (scanf("%d", &num) != 1) {
			scanf("%*s");
			printf("Дурак. Введи номер слота, из которого хочешь убрать предмет. Целым числом. \n");
			continue;
		}
		if (num < 1 || num > 10) {
			printf("Какой %d слот? Их всего 10, от 1 до 10. \n", num);
		}
		else {
			break;
		}
	
	}
	inventory[num - 1] = 0;
	printf("Вау! Теперь у тебя в %d слоте ничего нет! \n", num);
}

void case_6(void) {
	printf("Вот ваш инвентарь... \n");
	for (int num = 0; num < 10; num++) {
		printf("%d слот -- %s \n", num + 1, item_names[inventory[num]]);
	}
	for (int id = 1; id < 10; id++)
	{
		int count = 0;
		for (int i = 0; i < 10; i++) {
			if (inventory[i] != 0) {
				if (inventory[i] == id) {
					count++;
				}
			}
		}
		if (count != 0) {
			printf("%s встречается %d раз \n", item_names[id], count);
		}
	}
}

void save_diary(void) {
	FILE* diary = fopen("diary.txt", "a");
	if (diary == NULL) {
		printf("Ошибочка, ни создать, ни открыть файл не получилось");
		return;
	}
	printf("Записываем в дневничочек...\n");
	printf("Имя -- %s\n", player_name);
	printf("День -- %d Время -- %d:00\n", current_day, current_hour);
	case_3();
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

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	int user_action;
	printf("Как тебя зовут, юный фермер?\n");
	fgets(player_name, 32, stdin);
	player_name[strcspn(player_name, "\n")] = '\0';
	load_item_names();

	while (1)
	{
		printf("Привет, %s! Что же ты хочешь сделать?\n 0 - выход, 1 - посмотреть на часы, 2 - поработать 3 - посмотреть инвентарь, 4 - положить предмет в слот,\n 5 - выбросить предмет, 6 - уникальные находки, 7 - поиск предмета в сумке, 8 - запись в дневничок, 9 - посмотреть, где сейчас тусят нпс \n", player_name);
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
			case_3();
			break;
		case 4:
			case_4();
			break;
		case 5:
			case_5();
			break;
		case 6:
			case_6();
			break;
		case 7:
			find_item();
			break;
		case 8:
			save_diary();
			break;
		case 9:
			where_NPC(current_hour);
			break;
		default:
			printf("Ты по-моему чё-то перепутал... \n");
			break;
		}
	}
	return 0;
}