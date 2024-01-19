#pragma once
#include <stdio.h>
#include "types.h"


int isLegal(int y, int x, char move);
void move(struct type *obj, char move);
void random_move(struct type obj);
void check(int y, int x);

///sprites
void sprites_update(ALLEGRO_EVENT event);


void random_move(struct type *obj) {
	switch (rand() % 5)
	{
	case 1:
		move(obj, 'U');
		break;
	case 2:
		move(obj, 'D');
		break;
	case 3:
		move(obj, 'L');
		break;
	case 4:
		move(obj, 'R');
		break;
	}
}

void move(struct obj *object ,char move)
{
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
	if ((object->type / 100) == 1) _move++;
	check(object->y, object->x);
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

void check(int y, int x)
{
	if (sw <= 1) return;

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
			random_move(&dog[i]);
		}
		for (int i = 0; i < 4; i++) {
			random_move(&mouse3[i]);
		}
		for (int i = 0; i < 6; i++) {
			random_move(&mouse2[i]);
		}
		for (int i = 0; i < 10; i++) {
			random_move(&mouse1[i]);
		}
	}
}