#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct dice {
    int diceValue;
    int player;
};

int roll_dice() {
    return rand() % 6 + 1;
}

void print_players_initial(struct dice array[]) {
    printf("Players:\n");
    for (int i = 0; i < 4; i++) {
        printf("Player %d   %d\n", array[i].player, array[i].diceValue);
    }
}

void print_players_final(struct dice array[]) {
    printf("Players:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d: Player %d   %d\n", i + 1, array[i].player, array[i].diceValue);
    }
}

void swap(struct dice* a, struct dice* b) {
    struct dice temp = *a;
    *a = *b;
    *b = temp;
}

int threeCheck(struct dice array[]) {
    for (int i = 0; i < 2; i++) {
        if (array[i].diceValue == array[i + 1].diceValue && array[i + 1].diceValue == array[i + 2].diceValue) {
            return 1;
        }
    }
    return 0;
}

int twoCheck(struct dice array[], int a, int b) {
    if (array[a].diceValue == array[b].diceValue)
        return 1;
    else
        return 0;
}

int twoCheckForThree(struct dice array[], int a, int b, int c) {
    if (array[a].diceValue == array[b].diceValue || array[b].diceValue == array[c].diceValue)
        return 1;
    else
        return 0;
}

int throwDice(int order[], int dice_val[]) {

    struct dice array[4];

    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        array[i].player = i + 1;
    }

    for (int i = 0; i < 4; i++) {
        array[i].diceValue = roll_dice();
    }

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (array[j].diceValue > array[i].diceValue) {
                swap(&array[i], &array[j]);
            }
        }
    }
    printf("Initial result:\n");
    print_players_initial(array);

    int sw = 0;
    int repeat = 1;

    // if 3 players have equal values
    for (int i = 0; i < 2; i++) {
        if (array[i].diceValue == array[i + 1].diceValue && array[i + 1].diceValue == array[i + 2].diceValue) {
            do {
                sw = 1;
                array[i].diceValue = roll_dice();
                array[i + 1].diceValue = roll_dice();
                array[i + 2].diceValue = roll_dice();

                if (array[i + 1].diceValue > array[i].diceValue)
                    swap(&array[i], &array[i + 1]);
                if (array[i + 2].diceValue > array[i + 1].diceValue)
                    swap(&array[i + 1], &array[i + 2]);
                if (array[i + 1].diceValue > array[i].diceValue)
                    swap(&array[i], &array[i + 1]);

                if (threeCheck(array) == 0 || twoCheckForThree(array, i, i + 1, i + 2) == 0)
                    repeat = 0;
            } while (repeat);
        }
    }

    // if 2 players have equal values
    int sw1 = 1;
    int sw2 = 1;
    int sw3 = 1;
    int flag1 = 1;
    int flag2 = 1;

    if (sw == 0) {

        if (array[0].diceValue == array[1].diceValue) {
            flag1 = 0;
            do {
                array[0].diceValue = roll_dice();
                array[1].diceValue = roll_dice();

                if (array[1].diceValue > array[0].diceValue)
                    swap(&array[0], &array[1]);

                if (twoCheck(array, 0, 1) == 0)
                    sw1 = 0;
            } while (sw1);
        }


        if (flag1) {

            if (array[1].diceValue == array[2].diceValue) {
                flag2 = 0;
                do {
                    array[1].diceValue = roll_dice();
                    array[2].diceValue = roll_dice();

                    if (array[2].diceValue > array[1].diceValue)
                        swap(&array[1], &array[2]);

                    if (twoCheck(array, 1, 2) == 0)
                        sw2 = 0;
                } while (sw2);
            }
        }

        if (flag2) {

            if (array[2].diceValue == array[3].diceValue) {
                do {
                    array[2].diceValue = roll_dice();
                    array[3].diceValue = roll_dice();

                    if (array[3].diceValue > array[2].diceValue)
                        swap(&array[2], &array[3]);

                    if (twoCheck(array, 2, 3) == 0)
                        sw3 = 0;
                } while (sw3);
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        order[i] = array[i].player - 1;
        dice_val[i] = array[i].diceValue;
    }
    return 0;
}