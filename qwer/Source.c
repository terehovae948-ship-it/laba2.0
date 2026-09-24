#include <stdio.h>
int current_day = 1;
int current_hour = 8;
static inventory [10]; //0 ничего 1 дерево 2 камень 3 семена 4 мотыга 5 лейка 6 топор 7 корзина 8 сено 9 лопата
int work;
char predmet[15];
int main()
{
	int i = 1;
	int user_action;
	while (i == 1)
	{
		printf("0 - выход, 1 - посмотреть на часы, 2 - поработать 3 - посмотреть инвентарь, 4 = положить предмет в слот, 5 - выбросить предмет, 6 - уникальные находки");
		scanf(" %d", &user_action);
		switch (user_action)
		{
		case 0:
			printf("Пока!");
		case 1:
			printf("Сейчас: %d день, %d часов", current_day, current_hour);
		case 2:
			printf("щас поработаем...");
			printf("сколько изволите работать?");
			scanf(" %d", &work);
			current_hour += work;
				if (current_hour >= 24)
				{
					current_day += 1;
					current_hour -= 24;

				}
			printf("Вы успешно поработали %d часов! Сейчас %d день, %d часов.", work, current_day, current_hour);
		case 3:
			printf("Вот ваш инвентарь:");
			for (int a = 0; a < 10; a++)
			{
				switch (inventory[a])
				{
				case 0:
					predmet = "Ничего";
				case 1:
					predmet = "Дерево";
				case 2:
					predmet = "Камень";
				case 3:
					predmet = "Семена";
				case 4:
					predmet = "Мотыга";
				case 5:
					predmet = "Лейка";
				case 6:
					predmet = "Топор";
				case 7:
					predmet = "Коpзина";
				case 8:
					predmet = "Сено";
				case 9:
					predmet = "Лопата";
				}
				printf("%d Слот - %c", a + 1, predmet);
			}
		case 4:
			printf("4");
		case 5:
			printf("5");
		case 6:
			printf("6");
		}
	}
	return 0;
}