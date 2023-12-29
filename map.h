#pragma once
#include <stdlib.h>
#include <math.h>
#include "types.h"

int distance(struct pos point1, struct pos point2);
int isExcludedRegion(int x, int y);

int generate_walls(int board[][14], int seed)
{
    int c;
    int NoWalls = 0;

	for (int i = 0; i < 14;i++)
	{
        for (int j = 0; j < 14;j++)
        {
            if ((i >= 6 && i <= 9) && (j >= 6 && j <= 9)) continue;
            c = (j*i);
            if (seed * c % 13 == 5) board[i][j] = 1, NoWalls++; //vertical
            if (seed * c % 13 == 1) board[i][j] = 2, NoWalls++; //horizontal
        }
    }
    if (NoWalls < 18 || NoWalls > 40) return 1;
    return 0;
}

int random_pos(struct pos part[], int n, int sw[][15], int seed)
{
    srand(seed);
    int MIN_Dist = 6;
    for (int i = 0; i < n; i++) {
        do {
            part[i].x = rand() % 15;
            part[i].y = rand() % 15;
        } while (isExcludedRegion(part[i].x, part[i].y) ||  (i > 0 && (part[i].x == part[i - 1].x || part[i].y == part[i - 1].y) || distance(part[i], part[i - 1]) < MIN_Dist));
    }
}

int distance(struct pos point1,struct pos point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}
int isExcludedRegion(int x, int y) {
    return x >= 3 && x <= 11 && y >= 3 && y <= 11;
}