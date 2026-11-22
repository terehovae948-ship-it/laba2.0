#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"
#include "Utils.h"
#pragma warning(disable : 4996)

void case_3(const User* u) {
	printf("Вот ваш инвентарь: \n");
	for (int num = 0; num < 10; num++)
	{
		if (num >= 0 && num < 10) {
			printf("%d слот -- %s \n", num + 1, item_names[u->inventory[num]]);
		}
	}
}

void case_4(User* u) {
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
	printf("Напоминаю, что: 0 - ничего, 1 - дерево, 2 - камень, 3 - семена, 4 - мотыга, 5 - лейка "
		"6 - топор, 7 - корзина, 8 - сено, 9 - лопата \n");
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
	u->inventory[num - 1] = item;
	printf("Круто! Теперь у тебя в %d слоте есть что-то!(или нет) \n", num);
}

void case_5(User* u) {
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
	u->inventory[num - 1] = 0;
	printf("Вау! Теперь у тебя в %d слоте ничего нет! \n", num);
}

void case_6(const User* u) {
	for (int id = 1; id < 10; id++)
	{
		int count = 0;
		for (int i = 0; i < 10; i++) {
			if (u->inventory[i] != 0) {
				if (u->inventory[i] == id) {
					count++;
				}
			}
		}
		if (count != 0) {
			printf("%s встречается %d раз \n", item_names[id], count);
		}
	}
}

void find_item(const User* u) {
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
		if (u->inventory[slot] == id) {
			printf("Предмет найден в слоте %d\n,", slot + 1);
			count++;
		}
	}
	if (count == 0) {
		printf("У тебя в инвентаре нет этого предмета.\n");
	}
}

void free_u(User* u) {
	if (u != NULL) {
		free(u);
		printf("Память структуры по адресу %p освобождена\n", (void*)u);
	}
}

User* create_user(User* curr_u) {
	if (curr_u != 0) {
		char choice;
		while (1) {
			printf("Но юнный фермер уже существует. Ты хочешь его променять на другого? Y/N\n");
			scanf(" %c", &choice);
			while (getchar() != '\n');
			if ( choice == 'N' || choice == 'n') {
				printf("Правильно, старых фермеров на новых не меняют\n");
				return curr_u;
			}
			else if (choice == 'Y' || choice == 'y') {
				printf("Эх ты, такого фермера теряешь. Ну ладно, дело твоё\n");
				free_u(curr_u);
				break;
			}
			else {
				printf("ес ор но?\n");
			}
		}
	}
	else {
		while (getchar() != '\n');
	}
	User* u = (User*)calloc(1, sizeof(User));

	printf("Назови своё имя, юнный фермер.\n");
	fgets(u->name, sizeof(u->name), stdin);
	u->name[strcspn(u->name, "\n")] = '\0';

	u->max_hp = 100;
	u->hp = u->max_hp;
	u->max_stamina = 100;
	u->stamina = u->max_stamina;
	u->gold = 50;
	u->userH = 1;
	u->userW = 1;

	return u;
}

void user_card(User* u) {

}