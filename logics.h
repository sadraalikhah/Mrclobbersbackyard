#pragma once
#include <stdio.h>
#include "types.h"


int isLegal(int y, int x, char move);
void move(struct obj *object, char move);
void random_move(struct obj *object);
void checkCell(int y, int x);

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
	sw[object->y][object->x]++;
	putInBoard(object, object->y, object->x);
	checkCell(object->y, object->x);
	if ((object->type / 100) == 1) _move++;
}

int isLegal(int y, int x, char move)  //1: up, 2: left, 3: down, 4: right
{
	switch (move)
	{
	case 'U':
		if (y < 1) return 0;
		if (wall[y][x] == 'U') return 0;
		if (sw[y - 1][x] == 4) return 0;
		break;
	case 'D':
		if (y > 13) return 0;
		if (wall[y+1][x] == 'U') return 0;
		if (sw[y + 1][x] == 4) return 0;
		break;
	case 'L':
		if (x < 1) return 0;
		if (wall[y][x] == 'L') return 0;
		if (sw[y][x-1] == 4) return 0;
		break;
	case 'R':
		if (x > 13) return 0;
		if (wall[y][x+1] == 'L') return 0;
		if (sw[y][x + 1] == 4) return 0;
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
					cat_points[board[y][x][i] % 10]++;
					mouse1[board[y][x][j] % 10].inBoard = -(cat[board[y][x][i]%10].type);
					board[y][x][j] = 0;
					break;
				//mouse2
				case 4:
					cat_points[board[y][x][i] % 10] += 2;
					mouse2[board[y][x][j] % 10].inBoard = -(cat[board[y][x][i] % 10].type);
					board[y][x][j] = 0;
					break;
				//mouse3
				case 5:
					cat_points[board[y][x][i] % 10] += 3;
					mouse3[board[y][x][j] % 10].inBoard = -(cat[board[y][x][i] % 10].type);
					board[y][x][j] = 0;
					break;
				}
				break;
			case 3:
				if (board[y][x][j] / 100 == 1)
				{
					cat_points[board[y][x][j] % 10]++;
					mouse1[board[y][x][i] % 10].inBoard = -(cat[board[y][x][j] % 10].type);
					board[y][x][i] = 0;
				}
				break;
			case 4:
				if (board[y][x][j] / 100 == 1)
				{
					cat_points[board[y][x][j] % 10] += 2;
					mouse2[board[y][x][i] % 10].inBoard = -(cat[board[y][x][j] % 10].type);
					board[y][x][i] = 0;
				}
				break;
			case 5:
				if (board[y][x][j] / 100 == 1)
				{
					cat_points[board[y][x][j] % 10] += 3;
					mouse3[board[y][x][i] % 10].inBoard = -(cat[board[y][x][j] % 10].type);
					board[y][x][i] = 0;
				}
				break;
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
		move(&cat[_turn - 1], 'U');
		break;
	case ALLEGRO_KEY_DOWN:
	case ALLEGRO_KEY_S:
		move(&cat[_turn - 1], 'D');
		break;
	case ALLEGRO_KEY_LEFT:
	case ALLEGRO_KEY_A:
		move(&cat[_turn - 1], 'L');
		break;
	case ALLEGRO_KEY_RIGHT:
	case ALLEGRO_KEY_D:
		move(&cat[_turn - 1], 'R');
		break;
	case ALLEGRO_KEY_SPACE:
	case ALLEGRO_KEY_ENTER:
		_move = 1;
		_turn++;
		break;
	}

	if (_turn > 4)
	{
		_turn = 1;
		_round++;

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
	}
}