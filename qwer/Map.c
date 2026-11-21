#include "Map.h"
#include <stdio.h>
#include <stdlib.h>

void free_(map* m) {
	if (m->maap != NULL) {
		for (int i = 0; i < m->height; i++) {
			free(m->maap[i]);
		}
		free(m->maap);
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

void draw(map* m, User* u, int distance) {
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
}
