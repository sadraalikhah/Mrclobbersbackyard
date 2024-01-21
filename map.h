#pragma once
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "types.h"

#define BOARD_SIZE 15


// Check if a position is in the excluded region
int isExcludedRegion(int x, int y);

//sets walls to zero if the number required is not provided
void setToZero();

// Generate walls on the board based on certain conditions
void generate_walls()
{
    do
    {
        int NoWalls = 0;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (rand() % 13 == 5)
                {
                    if (j == 0 || i == 0 || i == 14) continue;
                    else if (j > 6 && j < 9 && i > 5 && i < 8) continue;
                    wall[i][j] = 'L';
                    NoWalls++;
                }
                else if (rand() % 13 == 1)
                {
                    if (i == 0 || j == 0 || j == 14) continue;
                    else if (i > 6 && i < 9 && j > 5 && j < 8) continue;
                    wall[i][j] = 'U';
                    NoWalls++;
                }
            }
        }
        if (NoWalls < 18 || NoWalls > 40)
        {
            setToZero();
        }
        else break;

    } while (1);
}

//place objects after their spawn in the board (assists the move function)
void putInBoard(struct obj *object, int y, int x);

// Spawn entities at random positions on the board
void spawn(struct obj object[], int n)
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
        object[objectNumber].y = y;
        object[objectNumber].x = x;
        putInBoard(&object[objectNumber], y, x);
        objectNumber++;
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
        object[objectNumber].y = y;
        object[objectNumber].x = x;
        putInBoard(&object[objectNumber], y, x);
        objectNumber++;
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
        object[objectNumber].y = y;
        object[objectNumber].x = x;
        putInBoard(&object[objectNumber], y, x);
        objectNumber++;
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
        object[objectNumber].y = y;
        object[objectNumber].x = x;
        putInBoard(&object[objectNumber], y, x);
        objectNumber++;
    }
}

int isExcludedRegion(int y, int x) {
    return x > 5 && x < 9 && y > 5 && y < 9;
}

void setToZero()
{
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            wall[i][j] = 0;
}

void putInBoard(struct obj *object, int y, int x)
{
    for (int i = 0; i < 4; i++)
    {
        if (board[y][x][i]) continue;
        board[y][x][i] = object->type;
        object->inBoard = i;
        sw[y][x]++;
        break;
    }
}