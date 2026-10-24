#include <stdio.h>
#include <windows.h>
#include <string.h>
#pragma warning(disable : 4996)
int current_day = 1;
int current_hour = 8;
static int inventory [10]; //0 ничего 1 дерево 2 камень 3 семена 4 мотыга 5 лейка 6 топор 7 корзина 8 сено 9 лопата
char item_names[10][15];
char player_name[33];

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
		printf("Предмет с названием \"%s\" не существует в игре!\n", search_item);
		return;
	}
	int count = 0;
	printf("Результаты поиска для \"%s\" (ID: %d):\n", search_item, id);
	for (int slot = 0; slot < 10; slot++) {
		if (inventory[slot] == id) {
			printf("-> Предмет найден в слоте №%d\n", slot + 1);
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
			printf("%d элемент -- %s \n", num + 1, item_names[inventory[num]]);
		}
		else {
			printf("В %d слоте предмет, которого нет. Его ID: %d", num + 1, inventory[num]);
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
		printf("Привет, %s! Что же ты хочешь сделать?\n 0 - выход, 1 - посмотреть на часы, 2 - поработать 3 - посмотреть инвентарь, \n 4 - положить предмет в слот, 5 - выбросить предмет, 6 - уникальные находки, 7 - поиск предмета в сумке \n", player_name);
		while (1) {
			if (scanf("%d", &user_action) != 1) {
				scanf("%*s");
				printf("Дурак. Введи число от 0 до 6 \n");
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
		case 5: {
			case_5();
			break;
		}
		case 6:
			case_6();
			break;
		case 7:
			find_item();
			break;
		default:
			printf("Ты по-моему чё-то перепутал... \n");
			break;
		}
	}
	return 0;
}