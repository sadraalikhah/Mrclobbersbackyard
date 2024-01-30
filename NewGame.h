#pragma once
#include "types.h"
#include "logics.h"
#include "map.h"
#include "Dice.h"


void new_game()
{
	///dice
	throwDice(order, dice_val);

	///walls
	generate_walls();

	///main board
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			for (int k = 0; k < 4; k++)
				board[i][j][k] = 0;

	///filled house switch
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			sw[i][j] = 0;

	///trap board
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			trapBoard[i][j] = 0;

	///trap visibility
	for (int i = 0; i < 8; i++)
		trap_vis[i] = 0;

	///Number of Fish
	int NoFish = 10;

	///dog stats
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
	dog_stat[3].defense = 5;
	dog_stat[3].speed = 1;

	///cat stats
	for (int i = 0; i < 4; i++)
	{
		cat_stat[i].attack = 2;
		cat_stat[i].defense = 5;
	}
	
	///cat pos
	for (int i = 0; i < 4; i++)
	{
		cat[i].x = 7;
		cat[i].y = 7;
		cat[i].type = 100 + i;
		putInBoard(&cat[i], 7, 7);
	}

	for (int i = 0; i < 15; i++)
	{
		cat_points[i] = 0;
		cat_stun[i] = 0;
	}

	///spawns
	for (int i = 0; i < 4; i++) dog[i].type = 200 + i;
	spawn(dog, 4);
	//mice
	for (int i = 0; i < 10; i++) mouse1[i].type = 300 + i;
	spawn(mouse1, 10);
	for (int i = 0; i < 6; i++) mouse2[i].type = 400 + i;
	spawn(mouse2, 6);
	for (int i = 0; i < 4; i++) mouse3[i].type = 500 + i;
	spawn(mouse3, 4);
	//chocolates
	for (int i = 0; i < 6; i++) candy[i].type = 600 + i;
	spawn(candy, 6);
	//traps
	for (int i = 0; i < 8; i++) trap[i].type = 700 + i;
	spawn(trap, 8);
	//fish
	for (int i = 0; i < 10; i++) fish[i].type = 800 + i;
	spawn(fish, 10);

	///save spawn points
	for (int i = 0; i < 8; i++)
		mouse1Spawn[i] = mouse1[i];
	for (int i = 0; i < 6; i++)
		mouse2Spawn[i] = mouse2[i];
	for (int i = 0; i < 4; i++)
		mouse3Spawn[i] = mouse3[i];
	for (int i = 0; i < 10; i++)
		fishSpawn[i] = fish[i];


	_round = 1;
	_turn = 1;
	_move = 1;

	start_game();
}