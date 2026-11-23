#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"

void free_(map* m) {
	if (m->maap != NULL) {
		for (int i = 0; i < m->height; i++) {
			free(m->maap[i]);
		}
		free(m->maap);
		printf("Память структуры по адресу %p освобождена\n", (void*)m);
	}
}

void create(map* m, User* u) {
	free_(m);

	if (m->location == 1) {
		m->height = (rand() % (30 - 5 + 1) + 5);
		m->width = (rand() % (30 - 5 + 1) + 5);
	}
	else {
		m->height = (rand() % (8 - 5 + 1) + 5);
		m->width = (rand() % (8 - 5 + 1) + 5);
	}

	m->maap = (char**)malloc(m->height * sizeof(char*));
	for (int i = 0; i < m->height; i++) {
		m->maap[i] = (char*)malloc(m->width * sizeof(char));
	}

	for (int h = 0; h < m->height; h++) {
		for (int w = 0; w < m->width; w++) {
			if (h == 0 || h == m->height - 1 || w == 0 || w == m->width - 1) {
				m->maap[h][w] = wall;
			}
			else {
				if (rand() % 5 == 0 && m->location == 1) {
					m->maap[h][w] = 'T';
				}
				else if (rand() % 5 == 0 && m->location == 0) {
					m->maap[h][w] = 'R';
				}
				else {
					m->maap[h][w] = empty;
				}
			}
		}
	}
	u->userH = 1;
	u->userW = 1;
	m->maap[u->userH][u->userW] = empty;

	int exitH = rand() % (m->height - 3) + 1;
	int exitW = rand() % (m->width - 3) + 1;
	if (exitH == 1 && exitW == 1) {
		exitH++;
		exitW++;
	}
	m->maap[exitH][exitW] = Exit;

	int fireH = rand() % (m->height - 4) + 1;
	int fireW = rand() % (m->width - 4) + 1;
	if ((fireH == 1 && fireW == 1) || (fireH == exitH && fireW == exitW)) {
		fireH = fireH + 2;
		fireW = fireW + 2;
	}
	m->maap[fireH][fireW] = fier;
}

void draw(const map* m, User* u, int distance, int* current_hour) {
	system("cls");
	if (m->location == 1) {
		printf("Ты забрёл в лес %d * %d метров. Ты уже в %d км от дома! Ходить на wasd. Для выхода встань на 'K' и нажми Q\n", m->height, m->width, distance);
	}
	else {
		printf("Ты забрёл в пещеру %d * %d метров. Ты уже в %d км от дома! Ходить на wasd. Для выхода встань на 'K' и нажми Q\n", m->height, m->width, distance);
	}

	for (int h = 0; h < m->height; h++) {
		for (int w = 0; w < m->width; w++) {
			if (h == u->userH && w == u->userW) {
				printf("%c", user);
			}
			else {
				printf("%c", m->maap[h][w]);
			}
		}
		printf("\n");
	}
	printf("HP: %d | Stamina: %d | Gold: %d | Hour: %d\n", u->hp, u->stamina, u->gold, *current_hour);
}

void adventure(User* u, int* current_day, int* current_hour) {
	if (u == NULL) {
		printf("А какое может быть путешествие фермера, если фермера не существует?\n");
		return;
	}
	if (u->stamina <= 0) {
		printf("Какое тебе приключение? Иди спать, не позорься.");
		return;
	}
	if (*current_hour == 2) {
		printf("Ты время видел? Спать.");
		return;
	}

	map m;
	m.maap = NULL;
	m.location = 1;

	int needNewMap = 1;
	int game = 1;
	int distanse = 1;
	int lose = 0;
	int found = 0;
	int found_relic;
	char relic_name[3][50] = { "Кольцо Жадности", "Сапоги-Скороходы", "Браслет Восстановления" };
	char explain[3][60] = { "Золото Х2, но за шаг -2 стамины", "Смена этажа: -1 стамина", "При смене этажа +10 стамины" };

	while (game == 1) {
		if (needNewMap == 1) {
			create(&m, u);
			needNewMap = 0;
		}

		draw(&m, u, distanse, current_hour);
		if (found == 1) {
			found = 0;
			found_relic = rand() % 3;
			printf("Вау! Исследуя местность ты нашёл %s! Хочешь надеть (Уже надетая реликвия пропадёт) или предпочтёшь продать за 25 золота?\n", relic_name[found_relic]);
			printf("%s", explain[found_relic]);
			while (1) {
				printf("K - оставить, S - продать.\n");
				char coice = _getch();
				if (coice == 'K' || coice == 'k') {
					u->relic = found_relic;
					break;
				}
				else if (coice == 'S' || coice == 's') {
					u->gold += 25;
					break;
				}
				else {
					printf("Не поняла твоего ответа. S или K\n");
				}
			}
		}

		char way = _getch();
		int nextH = u->userH;
		int nextW = u->userW;

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

		if ((way == 'q' || way == 'Q') && m.maap[u->userH][u->userW] == fier) {
			game = 0;
		}

		if (m.maap[nextH][nextW] != wall && m.maap[nextH][nextW] != 'R' && m.maap[nextH][nextW] != 'T') {
			u->userH = nextH;
			u->userW = nextW;
			if (u->relic == Ring_of_stingy) {
				u->stamina -= 2;
			}
			else {
				u->stamina -= 1;
			}
			if (u->stamina <= 0) {
				game = 0;
				lose = 1;
				u->gold = u->gold / 2;
				continue;
			}
		}

		if (m.maap[u->userH][u->userW] == Exit) {
			if (u->relic == Fast_boots) {
				u->stamina -= 1;
			}
			else if (u->relic == Recover_Armlet) {
				u->stamina += 10;
			}
			else {
				u->stamina -= 5;
			}
			*current_hour += 1;
			if (*current_hour >= 24) {
				*current_day += *current_hour / 24;
				*current_hour = *current_hour % 24;
			}
			if (u->stamina <= 0 || *current_hour == 2) {
				game = 0;
				lose = 1;
				u->gold = u->gold / 2;
				continue;
			}
			if (m.location == 1) {
				m.location = 0;
			}
			else {
				m.location = 1;
			}
			if (u->relic == Ring_of_stingy) {
				u->gold += coefficient_gold * distanse * 2;
			}
			else {
				u->gold += coefficient_gold * distanse;
			}
			distanse++;
			needNewMap = 1;
			if (rand() % 100 < 20) {
				found = 1;
			}
		}
	}

	free_(&m);
	if (lose == 1) {
		printf("О нет, ты свалился в обморок от бессилия! Благо, добрые люди дотащили тебя домой, но половину твоего золота, увы, нет\n");
	}
}
