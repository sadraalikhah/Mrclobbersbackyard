#pragma once
#include <stdio.h>
#include "types.h"

int isLegal(int y, int x, int move)  //1: up, 2: left, 3: down, 4: right
{
	if (y < 0 && y > 15 && x > 0 && x < 15) return 0;
	//move up
	if (wallH[y-1][x] && move == 1) return 0;
	//move down
	if (wallH[y - 1][x - 1] && move == 3) return 0;
	//move left
	if (wallV[y - 1][x] && move == 2) return 0;
	//move right
	if (wallV[y - 1][x - 1] && move == 4) return 0;
	return 1;
}

