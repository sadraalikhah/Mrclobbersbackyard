#pragma once
#include <stdio.h>
#include "types.h"
#include "Dice.h"
#include "map.h"
#include "Pause.h"

int isLegal(int y, int x, char move);
void move(struct obj *object, char move);
void random_move(struct obj* object);
void checkCell(int y, int x, int type, int inBoard);
int free_mouse(int cat);
void free_ALL_mice(int cat);
void respawnFish();
void fight(int type1, int type2);



///sprites
void sprites_update(ALLEGRO_EVENT event);

void random_move(struct obj* object) {
	int amount;
	switch (object->type / 100)
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
		for (int i = 0; i < amount; i++)
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
	if ((object->type / 100 == 1) && (cat_stun[object->type % 10])) return;
	if (!isLegal(object->y, object->x, move) || _move > 3) return;


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
	//traps bud
	if (trapBoard[y][x] > 0 && (type/100 == 1))
	{
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

	if (!sw[y][x]) return;

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
			case 2:
				fight(board[y][x][j], board[y][x][inBoard]);
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
			//candy
			case 6:
				cat_stat[(board[y][x][inBoard] % 10)].attack++;
				candy[(board[y][x][j] % 10)].inBoard = (-cat[board[y][x][inBoard] % 10].type);
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
			if (board[y][x][j] / 100 == 1)
				fight(board[y][x][inBoard], board[y][x][j]);
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
	///keyboard input call
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

	///new round
	if (_turn > 4)
	{
		_turn = 1;
		_round++;
		for (int i = 0; i < 4; i++)
			cat_stat[i].defense++;

		//cat_stun
		for (int i = 0; i < 4; i++)
		{
			if (cat_stun[i])
			{
				cat_stun[i]--;
				if (cat_stun[i] == 1)
				{
					cat_stun[i]--;
					cat_stat[i].attack = 2;
					cat_stat[i].defense = 5;
				}
			}
		}

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

		//respawn fish if needed
		if (NoFish < 4)
			respawnFish();

		throwDice(order, dice_val);

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
			cat_points[cat % 10] -= 3;
			return 1;
		}
	}	
	for (int i = 0; i < 6; i++)
	{
		if (mouse2[i].inBoard == -cat)
		{
			mouse2[i] = mouse2Spawn[i];
			putInBoard(&mouse2[i], mouse2Spawn[i].y, mouse2Spawn[i].x);
			cat_points[cat % 10] -= 2;
			return 1;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (mouse1[i].inBoard == -cat)
		{
			mouse1[i] = mouse1Spawn[i];
			putInBoard(&mouse1[i], mouse1Spawn[i].y, mouse1Spawn[i].x);
			cat_points[cat % 10] --;
			return 1;
		}
	}
	return 0;
}

void free_ALL_mice(int cat)
{
	while (free_mouse(cat));
}

void get_ALL_mice(int winner, int loser)
{
	for (int i = 0; i < 4; i++)
	{
		if (mouse3[i].inBoard == -loser)
		{
			mouse3[i].inBoard = -winner;
			cat_points[loser % 10] -= 3;
			cat_points[winner % 10] += 3;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (mouse2[i].inBoard == -loser)
		{
			mouse2[i].inBoard = -winner;
			cat_points[loser % 10] -= 2;
			cat_points[winner % 10] += 2;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (mouse1[i].inBoard == -loser)
		{
			mouse1[i].inBoard = -winner;
			cat_points[loser % 10]--;
			cat_points[winner % 10]++;
		}
	}
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

//type1 is the object that was in the cell first
void fight(int type1, int type2)
{
	if (cat_stun[type1 % 10]) return;
	switch (type1 / 100)
	{
	case 1:
		switch (type2 / 100)
		{
		//cat - cat fight
		case 1:
			if ((cat_stat[type1 % 10].attack * cat_stat[type1 % 10].defense) >= (cat_stat[type2 % 10].attack * cat_stat[type2 % 10].defense))
			{
				//cat2 lost
				cat_stat[type2 % 10].attack = 1;
				cat_stat[type2 % 10].defense = 0;
				cat_stun[type2 % 10] = 3;
				get_ALL_mice(type1, type2);
				//cat1
				cat_stat[type1 % 10].defense -= (cat_stat[type1 % 10].attack/ cat_stat[type2 % 10].attack)* cat_stat[type1 % 10].defense;
				if (cat_stat[type1 % 10].defense < 0) cat_stat[type1 % 10].defense = 0;
			}
			else
			{
				//cat1 lost
				cat_stat[type1 % 10].attack = 1;
				cat_stat[type1 % 10].defense = 0;
				cat_stun[type1 % 10] = 3;
				get_ALL_mice(type2, type1);
				//cat2
				cat_stat[type2 % 10].defense -= (cat_stat[type2 % 10].attack / cat_stat[type1 % 10].attack) * cat_stat[type2 % 10].defense;
				if (cat_stat[type2 % 10].defense < 0) cat_stat[type2 % 10].defense = 0;
			}
			break;
		// cat - dog fight
		case 2:
			if ((cat_stat[type1 % 10].attack * cat_stat[type1 % 10].defense) >= (dog_stat[type2 % 10].attack * dog_stat[type2 % 10].defense))
			{
				//dog lost
				board[dog[type2 % 10].y][dog[type2 % 10].x][dog[type2 % 10].inBoard] = 0;
				dog[type2 % 10].inBoard = -1;
				sw[dog[type2 % 10].y][dog[type2 % 10].x]--;

				//cat
				cat_stat[type1 % 10].defense -= (cat_stat[type1 % 10].attack / dog_stat[type2 % 10].attack) * cat_stat[type1 % 10].defense;
				if (cat_stat[type1 % 10].defense < 0) cat_stat[type1 % 10].defense = 0;
			}
			else
			{
				//cat lost
				cat_stat[type1 % 10].attack = 1;
				cat_stat[type1 % 10].defense = 0;
				cat_stun[type1 % 10] = 4;
				free_ALL_mice(type1);
				//dog
				dog_stat[type2 % 10].defense -= (dog_stat[type2 % 10].attack / cat_stat[type1 % 10].attack) * dog_stat[type2 % 10].defense;
				if (dog_stat[type2 % 10].defense < 0) dog_stat[type2 % 10].defense = 0;
			}
			break;
		}
		break;
	// dog - cat fight
	case 2:
		if ((dog_stat[type1 % 10].attack * dog_stat[type1 % 10].defense) >= (cat_stat[type2 % 10].attack * cat_stat[type2 % 10].defense))
		{
			//cat lost
			cat_stat[type2 % 10].attack = 1;
			cat_stat[type2 % 10].defense = 0;
			cat_stun[type2 % 10] = 3;
			free_ALL_mice(type2);

			//dog
			dog_stat[type1 % 10].defense -= (dog_stat[type1 % 10].attack / cat_stat[type2 % 10].attack) * dog_stat[type1 % 10].defense;
			if (dog_stat[type1 % 10].defense < 0) dog_stat[type1 % 10].defense = 0;
		}
		else
		{
			//dog lost
			board[dog[type1 % 10].y][dog[type1 % 10].x][dog[type1 % 10].inBoard] = 0;
			dog[type1 % 10].inBoard = -1;
			sw[dog[type1 % 10].y][dog[type1 % 10].x]--;

			//cat
			cat_stat[type2 % 10].defense -= (cat_stat[type2 % 10].attack / dog_stat[type1 % 10].attack) * cat_stat[type2 % 10].defense;
			if (cat_stat[type2 % 10].defense < 0) cat_stat[type2 % 10].defense = 0;
		}
		break;
	}
}

