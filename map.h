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
    int objectsPerCorner = n / 4;
    int objectsRemainder = (n % 4)/2;
    int objectNumber = 0;
    int y, x;
    for (int i = 0; i < objectsPerCorner + objectsRemainder; i++)
    {
        y = rand() % 7;
        x = rand() % 7;
        //duplicate check
        if (sw[y][x] || isExcludedRegion(y, x))
        {
            i--;
            continue;
        }
        object[objectNumber].x = x;
        object[objectNumber].y = y;
        objectNumber++;
        sw[y][x]++;
    }
    for (int i = 0; i < objectsPerCorner; i++)
    {
        y = rand() % 7;
        x = rand() % 7+8;
        //duplicate check
        if (sw[y][x] || isExcludedRegion(y, x))
        {
            i--;
            continue;
        }
        object[objectNumber].x = x;
        object[objectNumber].y = y;
        objectNumber++;
        sw[y][x]++;
    }
    for (int i = 0; i < objectsPerCorner; i++)
    {
        y = rand() % 7+8;
        x = rand() % 7;
        //duplicate check
        if (sw[y][x] || isExcludedRegion(y, x))
        {
            i--;
            continue;
        }
        object[objectNumber].x = x;
        object[objectNumber].y = y;
        objectNumber++;
        sw[y][x]++;
    }
    for (int i = 0; i < objectsPerCorner + objectsRemainder; i++)
    {
        y = rand() % 7+8;
        x = rand() % 7+8;
        //duplicate check
        if (sw[y][x] || isExcludedRegion(y, x))
        {
            i--;
            continue;
        }
        object[objectNumber].x = x;
        object[objectNumber].y = y;
        objectNumber++;
        sw[y][x]++;
    }
}

float distance(struct pos point1,struct pos point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}
int isExcludedRegion(int y, int x) {
    return x > 5 && x < 9 && y > 5 && y < 9;
}

