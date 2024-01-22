#pragma once
#include <stdio.h>
#include "types.h"
#include "Dice.h"


int isLegal(int y, int x, char move);
void move(struct obj *object, char move);
void random_move(struct obj *object);
void checkCell(int y, int x);
int free_mouse(int cat);

///sprites
void sprites_update(ALLEGRO_EVENT event);


void random_move(struct obj *object) {
	int amount;
	switch (object->type/100)
	{
	case 2:
		amount = dog_stat[object->type % 10].speed;
		break;
	case 3:
		amount = 1;
		break;
	case 4:
		amount = 2;
		break;
	case 5:
		amount = 3;
		break;
	}
	switch (rand() % 5)
	{
	case 1:
		for (int i =0; i < amount; i++)
			move(object, 'U');
		break;
	case 2:
		for (int i = 0; i < amount; i++)
			move(object, 'D');
		break;
	case 3:
		for (int i = 0; i < amount; i++)
			move(object, 'L');
		break;
	case 4:
		for (int i = 0; i < amount; i++)
			move(object, 'R');
		break;
	}
}

void move(struct obj *object ,char move)
{
	if (object->inBoard < 0) return;
	if (!isLegal(object->y, object->x, move) || _move > 3)
		return;
	sw[object->y][object->x]--;
	board[object->y][object->x][object->inBoard] = 0;
	switch (move)
	{
	case 'U':
		object->y--;
		break;
	case 'D':
		object->y++;
		break;
	case 'L':
		object->x--;
		break;
	case 'R':
		object->x++;
		break;
	}
	putInBoard(object, object->y, object->x);
	checkCell(object->y, object->x);
	if ((object->type / 100) == 1)
	{
		cat_stat[(object->type % 10)].defense--;
		_move++;
	}
}

int isLegal(int y, int x, char move)  //1: up, 2: left, 3: down, 4: right
{
	switch (move)
	{
	case 'U':
		if (y < 1) return 0;
		if (wall[y][x] == 'U') return 0;
		if (sw[y - 1][x] > 3) return 0;
		break;
	case 'D':
		if (y > 13) return 0;
		if (wall[y+1][x] == 'U') return 0;
		if (sw[y + 1][x] > 3) return 0;
		break;
	case 'L':
		if (x < 1) return 0;
		if (wall[y][x] == 'L') return 0;
		if (sw[y][x-1] > 3) return 0;
		break;
	case 'R':
		if (x > 13) return 0;
		if (wall[y][x+1] == 'L') return 0;
		if (sw[y][x + 1] > 3) return 0;
		break;
	}
	return 1;
}

void checkCell(int y, int x)
{
	if (sw[y][x] <= 1) return;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == i) continue;
			switch (board[y][x][i]/100)
			{
			//cat
			case 1:
				//traps bud
				if (trapBoard[y][x] > 0)
				{
					printf("trap!\n");
					trap_vis[(trapBoard[y][x] % 10)] = 1;
					int FreeMouseResult = free_mouse(cat[board[y][x][i] % 10].type);
					if (!FreeMouseResult && cat_stat[board[y][x][i] % 10].attack > 2) cat_stat[board[y][x][i] % 10].attack -= 2;
					else if (!FreeMouseResult)
					{
						cat_stat[board[y][x][i] % 10].defense -= 3;
						if (cat_stat[board[y][x][i] % 10].defense < 0)
							cat_stat[(board[y][x][i] % 10)].defense = 0;
					}
				}
				switch (board[y][x][j] / 100)
				{
				//cat
				case 1:
					//fight
					break;
				//dog
				case 2:
					//fight
					break;
				//mouse1
				case 3:
					cat_points[(board[y][x][i] % 10)]++;
					mouse1[(board[y][x][j] % 10)].inBoard = -(cat[board[y][x][i]%10].type);
					board[y][x][j] = 0;
					sw[y][x]--;
					break;
				//mouse2
				case 4:
					cat_points[board[y][x][i] % 10] += 2;
					mouse2[(board[y][x][j] % 10)].inBoard = -(cat[board[y][x][i] % 10].type);
					board[y][x][j] = 0;
					sw[y][x]--;
					break;
				//mouse3
				case 5:
					cat_points[(board[y][x][i] % 10)] += 3;
					mouse3[(board[y][x][j] % 10)].inBoard = -(cat[board[y][x][i] % 10].type);
					board[y][x][j] = 0;
					sw[y][x]--;
					break;
				//chocolate
				case 6:
					cat_stat[(board[y][x][i] % 10)].attack++;
					chocolate[(board[y][x][j] % 10)].inBoard = -(cat[board[y][x][i] % 10].type);
					board[y][x][j] = 0;
					sw[y][x]--;
					break;
				//fish
				case 8:
					cat_stat[board[y][x][i] % 10].defense += (rand()%3 + 2);
					chocolate[board[y][x][j] % 10].inBoard = -(cat[board[y][x][i] % 10].type);
					board[y][x][j] = 0;
					sw[y][x]--;

					break;
				}
				break;
			//dog
			case 2:
				//fight
				break;
			//mice-start
			case 3:
				if (board[y][x][j] / 100 == 1)
				{
					cat_points[board[y][x][j] % 10]++;
					mouse1[board[y][x][i] % 10].inBoard = -(cat[board[y][x][j] % 10].type);
					board[y][x][i] = 0;
					sw[y][x]--;
				}
				break;
			case 4:
				if (board[y][x][j] / 100 == 1)
				{
					cat_points[board[y][x][j] % 10] += 2;
					mouse2[board[y][x][i] % 10].inBoard = -(cat[board[y][x][j] % 10].type);
					board[y][x][i] = 0;
					sw[y][x]--;

				}
				break;
			case 5:
				if (board[y][x][j] / 100 == 1)
				{
					cat_points[board[y][x][j] % 10] += 3;
					mouse3[board[y][x][i] % 10].inBoard = -(cat[board[y][x][j] % 10].type);
					board[y][x][i] = 0;
					sw[y][x]--;
				}
				break;
			//mice-end
			}
		}
	}

}

///sprites
void sprites_update(ALLEGRO_EVENT event)
{
	switch (event.keyboard.keycode)
	{
	case ALLEGRO_KEY_UP:
	case ALLEGRO_KEY_W:
		if (cat_stat[order[_turn - 1]].defense > 0)
			move(&cat[order[_turn-1]], 'U');
		break;
	case ALLEGRO_KEY_DOWN:
	case ALLEGRO_KEY_S:
		if (cat_stat[order[_turn - 1]].defense > 0)
			move(&cat[order[_turn - 1]], 'D');
		break;
	case ALLEGRO_KEY_LEFT:
	case ALLEGRO_KEY_A:
		if (cat_stat[order[_turn - 1]].defense > 0)
			move(&cat[order[_turn - 1]], 'L');
		break;
	case ALLEGRO_KEY_RIGHT:
	case ALLEGRO_KEY_D:
		if (cat_stat[order[_turn - 1]].defense > 0)
			move(&cat[order[_turn - 1]], 'R');
		break;
	case ALLEGRO_KEY_SPACE:
	case ALLEGRO_KEY_ENTER:
		_move = 1;
		_turn++;
		break;
	}

	//new round
	if (_turn > 4)
	{
		_turn = 1;
		_round++;
		throwDice(order, dice_val);
		for (int i = 0; i < 4; i++)
			cat_stat[i].defense++;

		//call for random move
		for (int i = 0; i < 4; i++) {
			if (dog[i].inBoard < 0) continue;
			random_move(&dog[i]);
		}
		for (int i = 0; i < 4; i++) {
			if (mouse3[i].inBoard < 0) continue;
			random_move(&mouse3[i]);
		}
		for (int i = 0; i < 6; i++) {
			if (mouse2[i].inBoard < 0) continue;
			random_move(&mouse2[i]);
		}
		for (int i = 0; i < 10; i++) {
			if (mouse1[i].inBoard < 0) continue;
			random_move(&mouse1[i]);
		}

		//set traps to invisible
		for (int i = 0; i < 8; i++) trap_vis[i] = 0;

	}
}


int free_mouse(int cat)
{
	for (int i = 0; i < 4; i++)
	{
		if (mouse3[i].inBoard == -cat)
		{
			putInBoard(&mouse3[i], mouse3Spawn[i].y, mouse3Spawn[i].x);
			return 1;
		}
	}	
	for (int i = 0; i < 6; i++)
	{
		if (mouse2[i].inBoard == -cat)
		{
			putInBoard(&mouse2[i], mouse2Spawn[i].y, mouse2Spawn[i].x);
			return 1;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (mouse1[i].inBoard == -cat)
		{
			putInBoard(&mouse1[i], mouse1Spawn[i].y, mouse1Spawn[i].x);
			return 1;
		}
	}
	return 0;
}