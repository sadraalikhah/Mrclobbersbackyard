#pragma once

// Structure to represent statistics of game entities
struct stats{
	int attack;
	int defense;
	int speed;
	int points;
};

// Structure to represent the position and type of a game entity
struct pos {
	int x; //position x
	int y; //position y
	int type;
};

///walls
char wall[15][15] = { 0 };

///filled house switch
int sw[15][15] = { 0 };

//positions
struct pos pos_cat[4];
struct pos pos_dog[4]; // 0: bulldog ... ,3: bulldog.jr
struct pos mouse1[10];
struct pos mouse2[6];
struct pos mouse3[4];
struct pos chocolate[6];
struct pos trap[8];
struct pos fish[10];


///Stats
struct stats dog[4] = {
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

struct stats cats[4] = {
	[0].attack = 2,
	[0].defense = 5,
	[1].attack = 2,
	[1].defense = 5,
	[2].attack = 2,
	[2].defense = 5,
	[3].attack = 2,
	[3].defense = 5,
};

int _round = 1;
int _turn = 1;
int _move = 1;

