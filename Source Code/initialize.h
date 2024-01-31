#include <stdio.h>
#include "types.h"

void init()
{
	//board for being filled or not
	int board[15][15] = { 0 };

	//cats
	struct pos cat[4];
	for (int i = 0; i < 5; i++)
	{
		cat[i].x = 8;
		cat[i].y = 8;
	}
	// dogs
	struct pos pos_dog[4]; // 0: bulldog, 1: pitbull, 2: shepherd, 3: bulldog.jr
	struct stats dog[4];
	dog[0].attack = 5;
	dog[1].attack = 2;
	dog[2].attack = 2;
	dog[3].attack = 1;
	dog[0].deffense = 30;
	dog[1].deffense = 15;
	dog[2].deffense = 20;
	dog[3].deffense = 1;
	dog[0].speed = 5;
	dog[1].speed = 2;
	dog[2].speed = 3;
	dog[3].speed = 1;

	random(pos_dog);
	//mice
	struct pos mouse1[10];
	struct pos mouse2[6];
	struct pos mouse3[4];
	//chocolates
	struct pos chocolate[6];
	//traps
	struct pos trap[6];
	//fish
	struct pos fish[10];
}
