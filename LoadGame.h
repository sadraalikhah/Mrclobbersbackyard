#pragma once
#pragma warning(disable : 4996).
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void load_game()
{
	FILE* save_state;
	save_state = fopen("SaveState.dat", "r");
	if (save_state == NULL)
	{
		printf("can't open SaveState.dat\n");
		exit(0);
	}

	//if the game was finished just start a new game
	fseek(save_state, 3, SEEK_END);
	int ROUND_CHECK;
	fread(&ROUND_CHECK, sizeof(int), 1, save_state);
	if (ROUND_CHECK > 15) return;

	fseek(save_state, 0, SEEK_CUR);


	///dice
	fread(order, sizeof(int), 4, save_state);
	fread(dice_val, sizeof(int), 4, save_state);

	///walls
	fread(wall, sizeof(char), 15 * 15, save_state);

	///main board
	fread(board, sizeof(int), 15 * 15 * 4, save_state);

	///filled house switch
	fread(sw, sizeof(int), 15 * 15, save_state);


	///trap board
	fread(trapBoard, sizeof(int), 15 * 15, save_state);


	///trap visibility
	fread(trap_vis, sizeof(int), 8, save_state);

	///positions
	fread(cat, sizeof(struct obj), 4, save_state);
	fread(dog, sizeof(struct obj), 4, save_state);
	fread(mouse1, sizeof(struct obj), 10, save_state);
	fread(mouse2, sizeof(struct obj), 6, save_state);
	fread(mouse3, sizeof(struct obj), 4, save_state);
	fread(candy, sizeof(struct obj), 6, save_state);
	fread(trap, sizeof(struct obj), 8, save_state);
	fread(fish, sizeof(struct obj), 10, save_state);

	///number of fish
	fread(&NoFish, sizeof(int), 1, save_state);

	///spawn saves
	fread(mouse1Spawn, sizeof(struct obj), 10, save_state);
	fread(mouse2Spawn, sizeof(struct obj), 6, save_state);
	fread(mouse3Spawn, sizeof(struct obj), 4, save_state);
	fread(fishSpawn, sizeof(struct obj), 10, save_state);

	///dog stats
	fread(dog_stat, sizeof(struct stats), 4, save_state);

	///cat stats
	fread(cat_stat, sizeof(struct stats), 4, save_state);
	fread(cat_points, sizeof(int), 4, save_state);
	fread(cat_stun, sizeof(int), 4, save_state);

	///game
	fread(&_round, sizeof(int), 1, save_state);
	fread(&_turn, sizeof(int), 1, save_state);
	fread(&_move, sizeof(int), 1, save_state);

	fclose(save_state);
}