#pragma once
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "types.h"

#define BOARD_SIZE 15

// Calculate the Euclidean distance between two points
float distance(struct pos point1, struct pos point2);

// Check if a position is in the excluded region
int isExcludedRegion(int x, int y);

// Generate walls on the board based on certain conditions
int generate_walls()
{
    int c;
    int NoWalls = 0;

	for (int i = 0; i < BOARD_SIZE;i++)
	{
        for (int j = 0; j < BOARD_SIZE;j++)
        {
            if ((i >= 6 && i <= 9) && (j >= 6 && j <= 9)) continue;
            if (i < 0 || i > 13 || j < 0 || j > 13) continue;

            c = (j*i);
            if (rand() * c % 13 == 5)
            {
                wall[i][j] = 'D';
                wall[i+1][j] = 'U';
                NoWalls++;
            }
            if (rand() * c % 13 == 1)
            {
                wall[i][j] = 'R';
                wall[i][j+1] = 'L';
                NoWalls++;
            }
            //IN CASE THAT THERE IS AN ENCLOSURE
            if ((i > 0 && j > 0) && (wall[i][j] && wall[i+1][j] && wall[i][j+1] && wall[i+1][j+1]))
            {
                int q = rand() % 4;
                switch (q)
                {
                case 1:
                    wall[i - 1][j] = 0;
                    break;
                case 2:
                    wall[i][j] = 0;
                    break;
                case 3:
                    wall[i][j - 1] = 0;
                    break;
                case 4:
                    wall[i][j] = 0;
                    break;
                }
            }
        }
    }
    if (NoWalls < 18 || NoWalls > 40) return 1;
    return 0;
}

// Spawn entities at random positions on the board
void spawn(struct pos object[], int n, int sw[][BOARD_SIZE])
{
    srand(time(NULL));
    int i, j;
    float minDist = 30.00 / n;
    for (int k = 0; k < n;) {
        do {
            i = rand() % BOARD_SIZE;
            j = rand() % BOARD_SIZE;
            if (sw[i][j] == 1 || ((i >= 6 && i <= 9) && (j >= 6 && j <= 9))) continue;

            object[k].x = j;
            object[k].y = i;
            if (k > 1 && distance(object[k], object[k - 1]) < minDist) continue;

            sw[i][j] = 1;
            k++;
            
        } while (k < n || isExcludedRegion(object[k].x, object[k].y));
    }
}

float distance(struct pos point1,struct pos point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}
int isExcludedRegion(int x, int y) {
    return x >= 3 && x <= 11 && y >= 3 && y <= 11;
}