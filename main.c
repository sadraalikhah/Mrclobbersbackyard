#include <stdio.h>
#include "map.h"
#include "types.h"
#include "allegro.h"

int main()
{
	//seeding
	srand(time(NULL));

	//generate walls
	int wall[14][14] = { 0 };
	int generate_walls_con = 1;
	while (generate_walls_con)
	{
		generate_walls_con = generate_walls(&wall);
	}

	//board for being filled or not
	int sw[15][15] = { 0 };

	//cats
	struct pos pos_cat[4];
	for (int i = 0; i < 4; i++)
	{
		pos_cat[i].x = 8;
		pos_cat[i].y = 8;
		pos_cat[i].type = 100 + i;
	}

	// dogs
	struct pos pos_dog[4]; // 0: bulldog ... ,3: bulldog.jr
	spawn(&pos_dog, 4, &sw);
	for (int i = 0; i < 4; i++) pos_dog[i].type = 200 + i;

	//mice
	struct pos mouse1[10];
	spawn(&mouse1, 10, &sw);
	for (int i = 0; i < 10; i++) mouse1[i].type = 300 + i;

	struct pos mouse2[6];
	spawn(&mouse2, 6, &sw);
	for (int i = 0; i < 6; i++) mouse2[i].type = 400 + i;

	struct pos mouse3[4];
	spawn(&mouse3, 4, &sw);
	for (int i = 0; i < 4; i++) mouse3[i].type = 500 + i;


	//chocolates
	struct pos chocolate[6];
	spawn(&chocolate, 6, &sw);
	for (int i = 0; i < 6; i++) chocolate[i].type = 600 + i;

	//traps
	struct pos trap[8];
	spawn(&trap, 8, &sw);
	for (int i = 0; i < 8; i++) trap[i].type = 700 + i;



	//fish
	struct pos fish[10];
	spawn(&fish, 10, &sw);
	for (int i = 0; i < 10; i++) fish[i].type = 800 + i;

	dog[1].attack = 5;
    start(wall, pos_cat, pos_dog, mouse1, mouse2, mouse3, chocolate, trap, fish);
	return 0;
}