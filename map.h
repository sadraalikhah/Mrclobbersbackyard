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
int generate_walls(int wallV[][FENCE_SIZE], int wallH[][FENCE_SIZE])
{
    int c;
    int NoWalls = 0;

	for (int i = 0; i < FENCE_SIZE;i++)
	{
        for (int j = 0; j < FENCE_SIZE;j++)
        {
            if ((i >= 6 && i <= 9) && (j >= 6 && j <= 9)) continue;
            c = (j*i);
            if (rand() * c % 13 == 5) wallV[i][j] = 1, NoWalls++; //vertical
            if (rand() * c % 13 == 1) wallH[i][j] = 1, NoWalls++; //horizontal
            //IN CASE THAT THERE IS AN ENCLOSURE
            if ((i > 0 && j > 0) && (wallV[i - 1][j] == wallH[i][j]) && (wallH[i][j - 1] == wallH[i][j]))
            {
                int q = rand() % 4;
                switch (q)
                {
                case 1:
                    wallV[i - 1][j];
                    break;
                case 2:
                    wallH[i][j];
                    break;
                case 3:
                    wallH[i][j - 1];
                    break;
                case 4:
                    wallH[i][j];
                    break;
                }
            }
            if (wallV[i][j]) printf("i = %d, j = %d, V\n", i, j);
            if (wallH[i][j]) printf("i = %d, j = %d, H\n", i, j);
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