#pragma once
#include <stdio.h>
#include "types.h"

int isLegal(int y, int x, int move)  //1: up, 2: left, 3: down, 4: right
{
	if (y < 0 || y > 14 || x < 0 || x > 14) return 0;

	return 1;
}

