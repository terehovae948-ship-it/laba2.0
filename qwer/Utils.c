#include <stdio.h>
#include <string.h>
#include "Utils.h"
#pragma warning(disable : 4996)

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