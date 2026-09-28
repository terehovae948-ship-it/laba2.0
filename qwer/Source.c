#include <stdio.h>
int current_day = 1;
int current_hour = 8;
static inventory [10]; //0 ничего 1 дерево 2 камень 3 семена 4 мотыга 5 лейка 6 топор 7 корзина 8 сено 9 лопата
int work;
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
				switch (inventory[num])
				{
				case 0:
					printf("%d Слот - Ничего \n", num + 1);
				case 1:
					printf("%d Слот - Дерево \n", num + 1);
				case 2:
					printf("%d Слот - Камень \n", num + 1);
				case 3:
					printf("%d Слот - Семена", num + 1);
				case 4:
					printf("%d Слот - Мотыга", num + 1);
				case 5:
					printf("%d Слот - Лейка", num + 1);
				case 6:
					printf("%d Слот - Топор", num + 1);
				case 7:
					printf("%d Слот - Корзина", num + 1);
				case 8:
					printf("%d Слот - Сено", num + 1);
				case 9:
					printf("%d Слот - Лопата", num + 1);
				}
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
			inventory[num] = item;
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
			inventory[num] = 0;
			printf("Вау! Теперь у тебя в %d слоте ничего нет!", num);
		}
		case 6:
			printf("6");
		default:
			printf("Ты по-моему чё-то перепутал...");
		}
	}
	return 0;
}