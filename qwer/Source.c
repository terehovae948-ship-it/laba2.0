#include <stdio.h>
int current_day = 1;
int current_hour = 8;
static inventory [10]; //0 ничего 1 дерево 2 камень 3 семена 4 мотыга 5 лейка 6 топор 7 корзина 8 сено 9 лопата
int work;
char item_names[10][15] = 
{
	"Ничего", "Дерево", "Камень", "Семена", "Мотыга", "Лейка", "Топор", "Корзина", "Сено", "Лопата"
};
int main()
{
	int user_action;
	while (1)
	{
		printf("0 - выход, 1 - посмотреть на часы, 2 - поработать 3 - посмотреть инвентарь, 4 - положить предмет в слот, 5 - выбросить предмет, 6 - уникальные находки \n");
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
			printf("Пока!");
			break;
		case 1:
			printf("Сейчас: %d день, %d часов \n", current_day, current_hour);
		case 2:
			printf("щас поработаем... \n");
			printf("сколько изволите работать? \n");
			while (1) {
				if (scanf("%d", &work) != 1) {
					scanf("%*s");
					printf("Дурак. Введи кол-во часов, которое хочешь работать. Целыми числами. \n");
				}
				else {
					break;
				}
			}
			current_hour += work;
				if (current_hour >= 24)
				{
					current_day += 1;
					current_hour -= 24;

				}
			printf("Вы успешно поработали %d часов! Сейчас %d день, %d часов. \n", work, current_day, current_hour);
		case 3:
			printf("Вот ваш инвентарь:");
			for (int num = 0; num < 10; num++)
			{
				printf("%d элемент -- %s", num + 1, item_names[num]);
			}
		case 4: {
			int num;
			int item;
			printf("В какой слот вы хотите положить предмет?");
			while (1) {
				if (scanf("%d", &num) != 1) {
					scanf("%*s");
					printf("Дурак. Введи номер слота, в который хочешь положить предмет. Целым числом.");
				}
				else {
					break;
				}
			}
			printf("Напоминаю, что: 0 - ничего, 1 - дерево, 2 - камень, 3 - семена, 4 - мотыга, 5 - лейка 6 - топор, 7 - корзина, 8 - сено, 9 - лопата");
			printf("Что вы хотите положить в этот слот?");
			while (1) {
				if (scanf("%d", &item) != 1) {
					scanf("%*s");
					printf("Дурак. номер желаемого предмета. Целым числом.");
				}
				else {
					break;
				}
			}
			inventory[num - 1] = item;
			printf("Круто! Теперь у тебя в %d слоте есть что-то!(или нет)", num);
		}
		case 5: {
			int num;
			printf("Из какого слота вы хотите выбросить предмет?");
			while (1) {
				if (scanf("%d", &num) != 1) {
					scanf("%*s");
					printf("Дурак. Введи номер слота, из которого хочешь убрать предмет. Целым числом.");
				}
				else {
					break;
				}
			}
			inventory[num - 1] = 0;
			printf("Вау! Теперь у тебя в %d слоте ничего нет!", num);
		}
		case 6:
			printf("Вот ваш массив...");
			for (int num = 0; num < 10; num++) {
				printf("%d слот -- %s", inventory[num] + 1, item_names[inventory[num]]);
			}
			for (int id = 1; id < 10; id++)
			{
				int count = 0;
				for (int i = 0; i < 10; i++) {
					if (inventory[i] != 0) {
						if ( inventory[i] == id ) {
							count++;
						}
					}
				} 
				printf("%s встречается %d раз", item_names[id], count);
			}
		default:
			printf("Ты по-моему чё-то перепутал...");
		}
	}
	return 0;
}