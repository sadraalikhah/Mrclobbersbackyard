#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct DICE {
    int player;
    int diceValue;
};


void sort(struct DICE Arr[], int lowBound, int upBound)
{
    int i, j;
    struct DICE key;
    for (i = lowBound + 1; i <= upBound; i++)
    {
        key = Arr[i];
        j = i - 1;
        while (j >= lowBound && Arr[j].diceValue < key.diceValue)
        {
            Arr[j + 1] = Arr[j];
            j = j - 1;
        }
        Arr[j + 1] = key;
    }
}

void roll(struct DICE Arr[4], int lowBound, int upBound) {

    for (int i = lowBound; i <= upBound; i++)
    {
        Arr[i].diceValue = (rand() % 6 + 1);
    }

    //check
    int up = lowBound + 1, low = lowBound, sw = 0;
    for (int i = lowBound; i <= upBound; i++)
    {
        sw = 0;
        low = i;
        for (int j = i + 1; j <= upBound; j++)
        {
            if (Arr[i].diceValue == Arr[j].diceValue)
            {
                sw = 1;
                up = j;
            }
            else break;
        }
        if (sw)
        {
            roll(Arr, low, up);
            i = up;
        }
    }
}

void throwDice(int order[], int diceValue[])
{
    struct DICE Arr[4];
    srand(time(NULL));

    for (int i = 0; i < 4; i++)
    {
        Arr[i].player = i;
    }
    roll(Arr, 0, 3);

    for (int i = 0; i < 4; i++)
    {
        order[i] = Arr[i].player;
        diceValue[i] = Arr[i].diceValue;
    }

}
