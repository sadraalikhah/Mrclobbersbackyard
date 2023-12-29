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
    int i, j;
    int check;
    for (int k = 0; k < n; k++) {
        do {
            i = rand() % 15;
            j = rand() % 15;
            if (sw[i][j] == 1) continue;
            part[k].x = i;
            part[k].y = j;
            sw[i][j] = 1;
            
        } while (isExcludedRegion(part[k].x, part[k].y) || (k > 0 && (part[k].x == part[k - 1].x || part[k].y == part[k - 1].y)));
    }
}

int distance(struct pos point1,struct pos point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}
int isExcludedRegion(int x, int y) {
    return x >= 3 && x <= 11 && y >= 3 && y <= 11;
}