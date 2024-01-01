#pragma once
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "types.h"

float distance(struct pos point1, struct pos point2);
int isExcludedRegion(int x, int y);

int generate_walls(int board[][14])
{
    int c;
    int NoWalls = 0;
    srand(time(NULL));

	for (int i = 0; i < 14;i++)
	{
        for (int j = 0; j < 14;j++)
        {
            if ((i >= 6 && i <= 9) && (j >= 6 && j <= 9)) continue;
            c = (j*i);
            if (rand() * c % 13 == 5) board[i][j] = 1, NoWalls++; //vertical
            if (rand() * c % 13 == 1) board[i][j] = 2, NoWalls++; //horizontal
        }
    }
    if (NoWalls < 18 || NoWalls > 40) return 1;
    return 0;
}

int random_pos(struct pos part[], int n, int sw[][15])
{
    srand(time(NULL));
    int i, j;
    for (int k = 0; k < n;) {
        do {
            i = rand() % 15;
            j = rand() % 15;
            if (sw[i][j] == 1 || ((i >= 6 && i <= 9) && (j >= 6 && j <= 9))) continue;
            part[k].x = j;
            part[k].y = i;
            printf("i = %d j = %d\n", i, j);
            sw[i][j] = 1;
            k++;
            
        } while (k < n && isExcludedRegion(part[k].x, part[k].y));

    }
}

float distance(struct pos point1,struct pos point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}
int isExcludedRegion(int x, int y) {
    return x >= 3 && x <= 11 && y >= 3 && y <= 11;
}