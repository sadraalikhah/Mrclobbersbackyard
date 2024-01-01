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