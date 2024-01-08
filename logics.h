#pragma once
#include <stdio.h>
#include "types.h"

int isLegal(int y, int x, char move)  //1: up, 2: left, 3: down, 4: right
{
	switch (move)
	{
	case 'U':
		if (y < 1) return 0;
		if (wall[y][x] == 'U') return 0;
		break;
	case 'D':
		if (y > 13) return 0;
		if (wall[y-1][x] == 'U') return 0;
		break;
	case 'L':
		if (x < 1) return 0;
		if (wall[y][x] == 'L') return 0;
		break;
	case 'R':
		if (x > 13) return 0;
		if (wall[y][x+1] == 'L') return 0;
		break;
	}

	

	return 1;
}

