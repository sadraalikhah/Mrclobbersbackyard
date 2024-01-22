#pragma once
#include <stdio.h>
#include "types.h"
#include "Dice.h"
#include "map.h"


int isLegal(int y, int x, char move);
void move(struct obj *object, char move);
void checkCell(int y, int x, int type, int inBoard);
int free_mouse(int cat);
void respawnFish();


///sprites
void sprites_update(ALLEGRO_EVENT event);


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

	if ((object->type / 100) == 1)
	{
		cat_stat[(object->type % 10)].defense--;
		_move++;
	}

	putInBoard(object, object->y, object->x);
	checkCell(object->y, object->x, object->type, object->inBoard);

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

void checkCell(int y, int x, int type, int inBoard)
{
	if (!sw[y][x]) return;

	//traps bud
	if (trapBoard[y][x] > 0 && (type/100 == 1))
	{
		printf("trap!\n");
		trap_vis[(trapBoard[y][x] % 10)] = 1;
		int FreeMouseResult = free_mouse(cat[board[y][x][inBoard] % 10].type);
		if (!FreeMouseResult && cat_stat[board[y][x][inBoard] % 10].attack > 2) cat_stat[board[y][x][inBoard] % 10].attack -= 2;
		else if (!FreeMouseResult)
		{
			cat_stat[board[y][x][inBoard] % 10].defense -= 3;
			if (cat_stat[board[y][x][inBoard] % 10].defense < 0)
				cat_stat[(board[y][x][inBoard] % 10)].defense = 0;
		}
	}

	for (int j = 0; j < 4; j++)
	{
		if (j == inBoard) continue;
		switch (board[y][x][inBoard]/100)
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
				cat_points[(board[y][x][inBoard] % 10)]++;
				mouse1[(board[y][x][j] % 10)].inBoard = (-cat[board[y][x][inBoard]%10].type);
				board[y][x][j] = 0;
				sw[y][x]--;
				break;
			//mouse2
			case 4:
				cat_points[board[y][x][inBoard] % 10] += 2;
				mouse2[(board[y][x][j] % 10)].inBoard = (-cat[board[y][x][inBoard] % 10].type);
				board[y][x][j] = 0;
				sw[y][x]--;
				break;
			//mouse3
			case 5:
				cat_points[(board[y][x][inBoard] % 10)] += 3;
				mouse3[(board[y][x][j] % 10)].inBoard = (-cat[board[y][x][inBoard] % 10].type);
				board[y][x][j] = 0;
				sw[y][x]--;
				break;
			//chocolate
			case 6:
				cat_stat[(board[y][x][inBoard] % 10)].attack++;
				chocolate[(board[y][x][j] % 10)].inBoard = (-cat[board[y][x][inBoard] % 10].type);
				board[y][x][j] = 0;
				sw[y][x]--;
				break;
			//fish
			case 8:
				cat_stat[board[y][x][inBoard] % 10].defense += (rand()%3 + 2);
				fish[board[y][x][j] % 10].inBoard = -1;
				NoFish--;
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
				mouse1[board[y][x][inBoard] % 10].inBoard = (-cat[board[y][x][j] % 10].type);
				board[y][x][inBoard] = 0;
				sw[y][x]--;
			}
			break;
		case 4:
			if (board[y][x][j] / 100 == 1)
			{
				cat_points[board[y][x][j] % 10] += 2;
				mouse2[board[y][x][inBoard] % 10].inBoard = (-cat[board[y][x][j] % 10].type);
				board[y][x][inBoard] = 0;
				sw[y][x]--;

			}
			break;
		case 5:
			if (board[y][x][j] / 100 == 1)
			{
				cat_points[board[y][x][j] % 10] += 3;
				mouse3[board[y][x][inBoard] % 10].inBoard = (-cat[board[y][x][j] % 10].type);
				board[y][x][inBoard] = 0;
				sw[y][x]--;
			}
			break;
		//mice-end
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

	system("cls");
	int sum = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			sum += sw[i][j];
			printf("%d ", sw[i][j]);
		}
		printf("\n");
	}
	printf("%d\n", sum);


	//new round
	if (_turn > 4)
	{
		_turn = 1;
		_round++;
		throwDice(order, dice_val);
		for (int i = 0; i < 4; i++)
			cat_stat[i].defense++;

		//call for random move
		if (dog[0].inBoard >= 0)
			move(&dog[0], 5);
		if (dog[1].inBoard >= 0)
			move(&dog[1], 2);
		if (dog[2].inBoard >= 0)
			move(&dog[2], 3);
		if (dog[3].inBoard >= 0)
			move(&dog[3], 1);

		for (int i = 0; i < 4; i++) {
			if (mouse3[i].inBoard >= 0)
				move(&mouse3[i], 3);
		}
		for (int i = 0; i < 6; i++) {
			if (mouse2[i].inBoard >= 0)
				move(&mouse2[i], 2);
		}
		for (int i = 0; i < 10; i++) {
			if (mouse1[i].inBoard >= 0)
				move(&mouse1[i], 1);
		}

		//set traps to invisible
		for (int i = 0; i < 8; i++) trap_vis[i] = 0;

		//respawn fish if needed
		if (NoFish < 4)
			respawnFish();
	}
}


int free_mouse(int cat)
{
	for (int i = 0; i < 4; i++)
	{
		if (mouse3[i].inBoard == -cat)
		{
			mouse3[i] = mouse3Spawn[i];
			putInBoard(&mouse3[i], mouse3Spawn[i].y, mouse3Spawn[i].x);
			return 1;
		}
	}	
	for (int i = 0; i < 6; i++)
	{
		if (mouse2[i].inBoard == -cat)
		{
			mouse2[i] = mouse2Spawn[i];
			putInBoard(&mouse2[i], mouse2Spawn[i].y, mouse2Spawn[i].x);
			return 1;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (mouse1[i].inBoard == -cat)
		{
			mouse1[i] = mouse1Spawn[i];
			putInBoard(&mouse1[i], mouse1Spawn[i].y, mouse1Spawn[i].x);
			return 1;
		}
	}
	return 0;
}

void respawnFish()
{
	for (int i = 0; i < 10; i++)
	{
		if (fish[i].inBoard == -1)
		{
			fish[i] = fishSpawn[i];
			putInBoard(&fish[i], fish[i].y, fish[i].x);
		}
	}
	NoFish = 10;

}