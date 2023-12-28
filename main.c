#include <stdio.h>
#include <time.h>
#include "map.h"
#include "types.h"
#include "allegro.h"

int main()
{
	//seeding
	srand(time(NULL));
    int seed = rand() + 241281;
	//generate walls
	int wall[14][14] = { 0 };
	int generate_walls_con = 1;
	while (generate_walls_con)
	{
		generate_walls_con = generate_walls(&wall, seed);
	}

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
	struct pos bulldog;
	struct pos pitbull;
	struct pos shepherd;
	struct pos bulldog_jr;
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


    start(wall);
	return 0;
}