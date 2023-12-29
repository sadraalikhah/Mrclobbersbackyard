#include <stdio.h>
#include <time.h>
#include "map.h"
#include "types.h"
#include "allegro.h"

int main()
{
	//seeding
	srand(time(NULL));
    long int seed = rand() + 241281;
	//generate walls
	int wall[14][14] = { 0 };
	int generate_walls_con = 1;
	while (generate_walls_con)
	{
		generate_walls_con = generate_walls(&wall, seed);
	}

	//board for being filled or not
	int sw[15][15] = { 0 };

	//cats
	struct pos pos_cat[4];
	for (int i = 0; i < 5; i++)
	{
		pos_cat[i].x = 8;
		pos_cat[i].y = 8;
		pos_cat[i].type = 100 + i;

	}

	// dogs
	struct pos pos_dog[4]; // 0: bulldog ... ,3: bulldog.jr
	random_pos(&pos_dog, 4, &sw, seed);
	for (int i = 0; i < 4; i++) pos_dog[i].type = 200 + i;
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


    start(wall, pos_dog);
	return 0;
}