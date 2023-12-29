#pragma once
#include <stdlib.h>
#include "types.h"

int generate_walls(int board[][14], long int seed)
{
    int c;
    int NoWalls = 0;

	for (int i = 0; i < 14;i++)
	{
        for (int j = 0; j < 14;j++)
        {
            if ((i >= 6 && i <= 9) && (j >= 6 && j <= 9)) continue;
            c = (j*i);
            if ((seed * c) % 13 == 5) board[i][j] = 1, NoWalls++; //vertical
            if ((seed * c) % 13 == 1) board[i][j] = 2, NoWalls++; //horizontal
        }
    }
    if (NoWalls < 18 || NoWalls > 40) return 1;
    return 0;
}

int random_pos(struct pos part[], int n, int sw[][15], long int seed)
{
    int c;
    for (int k = 0; k < n;)
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                c = (i * j);
                if (sw[i][j] == 0 && ((seed*c % 15) == 3) && ((seed * c % 14) == 7))
                {
                    part[k].y = i;
                    part[k].x = j;
                    sw[i][j] = 1;
                    k++;
                }
                if (k == n) break;
            }
        }
        seed -= 21;
    }
}