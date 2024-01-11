#pragma once
#include <stdio.h>
#include "types.h"


int isLegal(int y, int x, char move);
void move(struct pos *obj, char move);
void randomMove(struct pos obj);

void move(struct pos *obj ,char move)
{
	if (!isLegal(obj->y, obj->x, move))
		return;
	switch (move)
	{
	case 'U':
		obj->y--;
		break;
	case 'D':
		obj->y++;
		break;
	case 'L':
		obj->x--;
		break;
	case 'R':
		obj->x++;
		break;
	}
}

int isLegal(int y, int x, char move)  //1: up, 2: left, 3: down, 4: right
{
	switch (move)
	{
	case 'U':
		if (y < 1) return 0;
		if (wall[y][x] == 'U') return 0;
		if (sw[y - 1][x] == 1) return 0;
		break;
	case 'D':
		if (y > 13) return 0;
		if (wall[y+1][x] == 'U') return 0;
		if (sw[y + 1][x] == 1) return 0;
		break;
	case 'L':
		if (x < 1) return 0;
		if (wall[y][x] == 'L') return 0;
		if (sw[y][x-1] == 1) return 0;
		break;
	case 'R':
		if (x > 13) return 0;
		if (wall[y][x+1] == 'L') return 0;
		if (sw[y][x + 1] == 1) return 0;
		break;
	}
	return 1;
}

void randomMove(struct pos obj)
{

		switch (rand() % 5)
		{
		case 0: //do not move
			break;
		case 1:
			break;
		}
}