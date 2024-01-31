#pragma once
#pragma warning(disable : 4996).
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void save_game()
{
	FILE* save_state;
	save_state = fopen("Assets/SaveState.dat", "w");
	if (save_state == NULL)
	{
		printf("can't open SaveState.dat\n");
		exit(0);
	}

	///dice
	fwrite(order, sizeof(int), 4, save_state);
	fwrite(dice_val, sizeof(int), 4, save_state);

	///walls
	fwrite(wall, sizeof(char), 15*15, save_state);

	///main board
	fwrite(board, sizeof(int), 15 * 15 * 4, save_state);

	///filled house switch
	fwrite(sw, sizeof(int), 15 * 15, save_state);


	///trap board
	fwrite(trapBoard, sizeof(int), 15 * 15, save_state);


	///trap visibility
	fwrite(trap_vis, sizeof(int), 8, save_state);

	///positions
	fwrite(cat, sizeof(struct obj), 4, save_state);
	fwrite(dog, sizeof(struct obj), 4, save_state);
	fwrite(mouse1, sizeof(struct obj), 10, save_state);
	fwrite(mouse2, sizeof(struct obj), 6, save_state);
	fwrite(mouse3, sizeof(struct obj), 4, save_state);
	fwrite(candy, sizeof(struct obj), 6, save_state);
	fwrite(trap, sizeof(struct obj), 8, save_state);
	fwrite(fish, sizeof(struct obj), 10, save_state);

	///number of fish
	fwrite(&NoFish, sizeof(int), 1, save_state);

	///spawn saves
	fwrite(mouse1Spawn, sizeof(struct obj), 10, save_state);
	fwrite(mouse2Spawn, sizeof(struct obj), 6, save_state);
	fwrite(mouse3Spawn, sizeof(struct obj), 4, save_state);
	fwrite(fishSpawn, sizeof(struct obj), 10, save_state);

	///dog stats
	fwrite(dog_stat, sizeof(struct stats), 4, save_state);

	///cat stats
	fwrite(cat_stat, sizeof(struct stats), 4, save_state);
	fwrite(cat_points, sizeof(int), 4, save_state);
	fwrite(cat_stun, sizeof(int), 4, save_state);

	///game
	fwrite(&_round, sizeof(int), 1, save_state);
	fwrite(&_turn, sizeof(int), 1, save_state);
	fwrite(&_move, sizeof(int), 1, save_state);

	fclose(save_state);
}