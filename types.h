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

///dice
int order[4];
int dice_val[4];

///walls
char wall[15][15] = { 0 };

///main board
int board[15][15][4];

///filled house switch
int sw[15][15] = { 0 };

///trap board
int trapBoard[15][15] = { 0 };

///trap visibility
int trap_vis[8] = { 0 };

//positions
struct obj cat[4];
struct obj dog[4]; // 0: bulldog ... ,3: bulldog.jr
struct obj mouse1[10];
struct obj mouse2[6];
struct obj mouse3[4];
struct obj chocolate[6];
struct obj trap[8];
struct obj fish[10];




///spawn saves
struct obj mouse1Spawn[10];
struct obj mouse2Spawn[6];
struct obj mouse3Spawn[4];
struct obj fishSpawn[10];


///Stats
struct stats dog_stat[4];



/// <summary>
/// cats
/// </summary>
struct stats cat_stat[4];

int cat_points[4];

int _round = 1;
int _turn = 1;
int _move = 1;

