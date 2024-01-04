#include <stdio.h>
#include "map.h"
#include "types.h"
#include "allegro.h"


//SADRA's new branch 101

int main()
{
	//seeding
	srand(time(NULL));

	//generate walls
	int generate_walls_con = 1;
	while (generate_walls_con)
	{
		generate_walls_con = generate_walls(&wall);
	}


	//cats
	for (int i = 0; i < 4; i++)
	{
		pos_cat[i].x = 8;
		pos_cat[i].y = 8;
		pos_cat[i].type = 100 + i;
	}

	// dogs
	spawn(&pos_dog, 4, &sw);
	for (int i = 0; i < 4; i++) pos_dog[i].type = 200 + i;
	//mice
	spawn(&mouse1, 10, &sw);
	for (int i = 0; i < 10; i++) mouse1[i].type = 300 + i;
	spawn(&mouse2, 6, &sw);
	for (int i = 0; i < 6; i++) mouse2[i].type = 400 + i;
	spawn(&mouse3, 4, &sw);
	for (int i = 0; i < 4; i++) mouse3[i].type = 500 + i;
	//chocolates
	spawn(&chocolate, 6, &sw);
	for (int i = 0; i < 6; i++) chocolate[i].type = 600 + i;
	//traps
	spawn(&trap, 8, &sw);
	for (int i = 0; i < 8; i++) trap[i].type = 700 + i;
	//fish
	spawn(&fish, 10, &sw);
	for (int i = 0; i < 10; i++) fish[i].type = 800 + i;


    start();
	return 0;
}