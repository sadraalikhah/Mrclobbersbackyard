#pragma once
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "types.h"

#define FENCE_SIZE 14
#define BOARD_SIZE 15

// Calculate the Euclidean distance between two points
float distance(struct pos point1, struct pos point2);

// Check if a position is in the excluded region
int isExcludedRegion(int x, int y);

// Generate walls on the board based on certain conditions
int generate_walls(int board[][FENCE_SIZE])
{
    int c;
    int NoWalls = 0;

	for (int i = 0; i < FENCE_SIZE;i++)
	{
        for (int j = 0; j < FENCE_SIZE;j++)
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

// Spawn entities at random positions on the board
void spawn(struct pos part[], int n, int sw[][BOARD_SIZE])
{
    srand(time(NULL));
    int i, j;
    for (int k = 0; k < n;) {
        do {
            i = rand() % BOARD_SIZE;
            j = rand() % BOARD_SIZE;
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