#include <stdio.h>
#include "map.h"
#include "types.h"
#include "allegro.h"
#include "Dice.h"

///SADRA's new branch 101

int main()
{
	//seeding
	srand(time(NULL));

	//generate walls
	generate_walls();

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (!wall[i][j]) wall[i][j] = '0';
			printf("%c ", wall[i][j]);
		}
		printf("\n");
	}


	//cat
	cat_stat[0].attack = 2;
	cat_stat[0].defense = 5;
	cat_stat[1].attack = 2;
	cat_stat[1].defense = 5;
	cat_stat[2].attack = 2;
	cat_stat[2].defense = 5;
	cat_stat[3].attack = 2;
	cat_stat[3].defense = 5;

	for (int i = 0; i < 4; i++)
	{
		cat[i].x = 7;
		cat[i].y = 7;
		cat[i].type = 100 + i;
		putInBoard(&cat[i], 7, 7);
	}

	// dogs
	dog_stat[0].attack = 5;
	dog_stat[0].defense = 30;
	dog_stat[0].speed = 5;
	dog_stat[1].attack = 2;
	dog_stat[1].defense = 15;
	dog_stat[1].speed = 2;
	dog_stat[2].attack = 2;
	dog_stat[2].defense = 20;
	dog_stat[2].speed = 3;
	dog_stat[3].attack = 1;
	dog_stat[3].defense = 1;
	dog_stat[3].speed = 1;
	for (int i = 0; i < 4; i++) dog[i].type = 200 + i;
	spawn(&dog, 4);
	//mice
	for (int i = 0; i < 10; i++) mouse1[i].type = 300 + i;
	spawn(&mouse1, 10);
	for (int i = 0; i < 6; i++) mouse2[i].type = 400 + i;
	spawn(&mouse2, 6);
	for (int i = 0; i < 4; i++) mouse3[i].type = 500 + i;
	spawn(&mouse3, 4);
	//chocolates
	for (int i = 0; i < 6; i++) chocolate[i].type = 600 + i;
	spawn(&chocolate, 6);
	//traps
	for (int i = 0; i < 8; i++) trap[i].type = 700 + i;
	spawn(&trap, 8);
	//fish
	for (int i = 0; i < 10; i++) fish[i].type = 800 + i;
	spawn(&fish, 10);

	///save spawn points
	for (int i = 0; i < 8; i++)
		mouse1Spawn[i] = mouse1[i];
	for (int i = 0; i < 6; i++)
		mouse2Spawn[i] = mouse2[i];
	for (int i = 0; i < 4; i++)
		mouse3Spawn[i] = mouse3[i];
	for (int i = 0; i < 8; i++)
		fishSpawn[i] = fish[i];


	throwDice();
    start();
	return 0;
}