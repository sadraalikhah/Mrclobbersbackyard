#pragma once

// Structure to represent statistics of game entities
struct stats{
	int attack;
	int defense;
	int speed;
};

// Structure to represent the position and type of a game entity
struct obj {
	int type;
	int inBoard;
	int y;
	int x;
};

///walls
char wall[15][15] = { 0 };

///main board
int board[15][15][4];

///filled house switch
int sw[15][15] = { 0 };

//positions
struct obj cat[4];
struct obj dog[4]; // 0: bulldog ... ,3: bulldog.jr
struct obj mouse1[10];
struct obj mouse2[6];
struct obj mouse3[4];
struct obj chocolate[6];
struct obj trap[8];
struct obj fish[10];


///Stats
struct stats dog_stat[4] = {
	[0].attack = 5,
	[0].defense = 30,
	[0].speed = 5,
	[1].attack = 2,
	[1].defense = 15,
	[1].speed = 2,
	[2].attack = 2,
	[2].defense = 20,
	[2].speed = 3,
	[3].attack = 1,
	[3].defense = 1,
	[3].speed = 1,
};

/// <summary>
/// cats
/// </summary>
struct stats cat_stat[4] = {
	[0].attack = 2,
	[0].defense = 5,
	[1].attack = 2,
	[1].defense = 5,
	[2].attack = 2,
	[2].defense = 5,
	[3].attack = 2,
	[3].defense = 5,
};

cat_points[4];

int _round = 1;
int _turn = 1;
int _move = 1;

