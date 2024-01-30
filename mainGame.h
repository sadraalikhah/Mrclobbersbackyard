#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "types.h"
#include "init.h"
#include "logics.h"
#include "SaveGame.h"


///draw
void draw_board();
void draw_scoreboard();
int Pill(int cat);

void start_game()
{


    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* mainQueue = al_create_event_queue();
    must_init(mainQueue, "mainQueue");



    al_register_event_source(mainQueue, al_get_keyboard_event_source());
    al_register_event_source(mainQueue, al_get_display_event_source(display));
    al_register_event_source(mainQueue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    save_game();
    al_start_timer(timer);
    while (_round < 16 && !done)
    {
        al_wait_for_event(mainQueue, &event);

        //logic definitions
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            // game logic goes here.
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            done = sprites_update(event);
            save_game();
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }
        if (done)
            break;


        if (redraw && al_is_event_queue_empty(mainQueue))
        {

            draw_board();
            draw_scoreboard();

            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_timer(timer);
    al_destroy_event_queue(mainQueue);

    ///Game Over
    end_game();
}

void draw_board()
{
    //*MAIN BOARD*//
    al_clear_to_color(al_map_rgb(255, 184, 60));

    // grid
    for (int i = 1; i < 15; i++)
    {
        al_draw_line(0, 72 * i, 1080, 72 * i, al_map_rgb_f(0, 0, 0), 2);
        al_draw_line(72 * i, 0, 72 * i, 1080, al_map_rgb_f(0, 0, 0), 2);
    }
    // walls
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {

            switch (wall[i][j])
            {
            case 'L':
                al_draw_line(72 * j, 72 * i, 72 * j, 72 * i + 72, al_map_rgb(107, 38, 22), 8);

                break;
            case 'U':
                al_draw_line(72 * j, 72 * i, 72 * j + 72, 72 * i, al_map_rgb(107, 38, 22), 8);


                break;
            }
        }
    }
    //starting house
    al_draw_bitmap(house, 72 * 7 + 5, 72 * 7 + 5, 0);

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            //objects
            for (int k = 0; k < 4; k++)
            {
                if (sw[i][j] == 1)
                {
                    switch (board[i][j][k] / 100)
                    {
                    case 1:
                        switch (board[i][j][k] % 10)
                        {
                        case 0:
                            al_draw_bitmap(cat_bitmap[0], 72 * j + 6, 72 * i + 6, 0);
                            break;
                        case 1:
                            al_draw_bitmap(cat_bitmap[1], 72 * j + 6, 72 * i + 6, 0);
                            break;
                        case 2:
                            al_draw_bitmap(cat_bitmap[2], 72 * j + 6, 72 * i + 6, 0);
                            break;
                        case 3:
                            al_draw_bitmap(cat_bitmap[3], 72 * j + 6, 72 * i + 6, 0);
                            break;
                        }
                        break;
                    case 2:
                        switch (board[i][j][k] % 10)
                        {
                        case 0:
                            al_draw_bitmap(bulldog, 72 * j + 6, 72 * i + 6, 0);
                            break;
                        case 1:
                            al_draw_bitmap(pitbull, 72 * j + 6, 72 * i + 6, 0);
                            break;
                        case 2:
                            al_draw_bitmap(shepherd, 72 * j + 6, 72 * i + 6, 0);
                            break;
                        case 3:
                            al_draw_bitmap(bulldog_jr, 72 * j + 6, 72 * i + 6, 0);
                            break;
                        }
                        break;
                    case 3:
                        al_draw_bitmap(mouse_1, 72 * j + 6, 72 * i + 6, 0);
                        break;
                    case 4:
                        al_draw_bitmap(mouse_2, 72 * j + 6, 72 * i + 6, 0);
                        break;
                    case 5:
                        al_draw_bitmap(mouse_3, 72 * j + 6, 72 * i + 6, 0);
                        break;
                    case 6:
                        al_draw_bitmap(_candy, 72 * j + 6, 72 * i + 6, 0);
                        break;
                    case 8:
                        al_draw_bitmap(_fish, 72 * j + 6, 72 * i + 6, 0);
                        break;
                    }
                }
                else if (sw[i][j] > 1)
                {
                    switch (board[i][j][k] / 100)
                    {
                    case 1:
                        switch (board[i][j][k] % 10)
                        {
                        case 0:
                            al_draw_scaled_bitmap(cat_bitmap[0], 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                            break;
                        case 1:
                            al_draw_scaled_bitmap(cat_bitmap[1], 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                            break;
                        case 2:
                            al_draw_scaled_bitmap(cat_bitmap[2], 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                            break;
                        case 3:
                            al_draw_scaled_bitmap(cat_bitmap[3], 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                            break;
                        }
                        break;
                    case 2:
                        switch (board[i][j][k] % 10)
                        {
                        case 0:
                            al_draw_scaled_bitmap(bulldog, 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                            break;
                        case 1:
                            al_draw_scaled_bitmap(pitbull, 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                            break;
                        case 2:
                            al_draw_scaled_bitmap(shepherd, 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                            break;
                        case 3:
                            al_draw_scaled_bitmap(bulldog_jr, 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                            break;
                        }
                        break;
                    case 3:
                        al_draw_scaled_bitmap(mouse_1, 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                        break;
                    case 4:
                        al_draw_scaled_bitmap(mouse_2, 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                        break;
                    case 5:
                        al_draw_scaled_bitmap(mouse_3, 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                        break;
                    case 6:
                        al_draw_scaled_bitmap(_candy, 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                        break;
                    case 8:
                        al_draw_scaled_bitmap(_fish, 0, 0, 60, 60, 72 * j + (k % 2) * 30 + 4, 72 * i + (k / 2) * 30 + 4, 34, 34, 0);
                        break;
                    }
                }
            }
            //traps
            if (trapBoard[i][j])
                if (trap_vis[(trapBoard[i][j]) % 10])
                    al_draw_tinted_bitmap(_trap, al_map_rgba_f(1, 1, 1, 0.5), 72 * j + 12, 72 * i + 12, 0);
        }
    }
}

/// <summary>
/// scoreboard
/// </summary>
void draw_scoreboard()
{

    ///color pallete
    ALLEGRO_COLOR activeC = al_map_rgb(192, 0, 6);
    ALLEGRO_COLOR inactiveC = al_map_rgb(0, 87, 184);
    ALLEGRO_COLOR currentC = al_map_rgb(255, 72, 204);


    //*STATS BOARD*//
    al_draw_bitmap(HUD_BG, 1080, 0, 0);


    ///logo
    al_draw_bitmap(HUD_logo, 1137, 73, 0);



    //cat colors
    ALLEGRO_COLOR cat_color[4];
    for (int i = 0; i < 4; i++)
    {
        if (cat_stun[i] == 0)
        {
            cat_color[i] = activeC;
            if (order[_turn - 1] == i) cat_color[i] = currentC;
        }
        else cat_color[i] = inactiveC;
    }

    //round
    al_draw_bitmap(short_pill, 1221, 386, 0);
    al_draw_textf(medium_font, activeC, 1273, 427, 0, "round   %2d", _round);

    //move
    al_draw_bitmap(short_pill, 1588, 386, 0);
    al_draw_textf(medium_font, activeC, 1646, 427, 0, "move    %d", _move);

    //description
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1250, 516, 0, "cat %d's move", order[_turn - 1] + 1);


    //row 1
    al_draw_bitmap(pill[Pill(order[0])], 1214, 540, 0);
    al_draw_filled_circle(1782, 608, 36, cat_color[order[0]]);

    al_draw_scaled_bitmap(cat_bitmap[order[0]], 0, 0, 60, 60, 1250, 574, 64, 64, 0);
    al_draw_bitmap(dice_bitmap[dice_val[0] - 1], 1125, 572, 0);
    al_draw_bitmap(shield, 1475, 587, 0);
    al_draw_bitmap(sword, 1565, 587, 0);



    al_draw_textf(small_font, cat_color[order[0]], 1351, 589, 0, "cat %d", order[0] + 1);
    al_draw_textf(small_font, cat_color[order[0]], 1518, 589, 0, "%2d", cat_stat[order[0]].defense);
    al_draw_textf(small_font, cat_color[order[0]], 1611, 589, 0, "%2d", cat_stat[order[0]].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1764, 589, 0, "%2d", cat_points[order[0]]);

    //if stunned
    if (cat_stun[order[0]] > 0)
    {
        al_draw_bitmap(ice, 1667, 576, 0);
        al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1690, 589, 0, "%d", cat_stun[order[0]] - 1);
    }

    //row 2
    al_draw_bitmap(pill[Pill(order[1])], 1214, 660, 0);
    al_draw_filled_circle(1782, 728, 36, cat_color[order[1]]);

    al_draw_scaled_bitmap(cat_bitmap[order[1]], 0, 0, 60, 60, 1250, 694, 64, 64, 0);
    al_draw_bitmap(dice_bitmap[dice_val[1] - 1], 1125, 692, 0);
    al_draw_bitmap(shield, 1475, 707, 0);
    al_draw_bitmap(sword, 1565, 707, 0);



    al_draw_textf(small_font, cat_color[order[1]], 1351, 709, 0, "cat %d", order[1] + 1);
    al_draw_textf(small_font, cat_color[order[1]], 1518, 709, 0, "%2d", cat_stat[order[1]].defense);
    al_draw_textf(small_font, cat_color[order[1]], 1611, 709, 0, "%2d", cat_stat[order[1]].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1764, 709, 0, "%2d", cat_points[order[1]]);

    //if stunned
    if (cat_stun[order[1]] > 0)
    {
        al_draw_bitmap(ice, 1667, 696, 0);
        al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1690, 709, 0, "%d", cat_stun[order[1]] - 1);
    }

    //row 3
    al_draw_bitmap(pill[Pill(order[2])], 1214, 780, 0);
    al_draw_filled_circle(1782, 848, 36, cat_color[order[2]]);

    al_draw_scaled_bitmap(cat_bitmap[order[2]], 0, 0, 60, 60, 1250, 814, 64, 64, 0);
    al_draw_bitmap(dice_bitmap[dice_val[2] - 1], 1125, 812, 0);
    al_draw_bitmap(shield, 1475, 827, 0);
    al_draw_bitmap(sword, 1565, 827, 0);



    al_draw_textf(small_font, cat_color[order[2]], 1351, 829, 0, "cat %d", order[2] + 1);
    al_draw_textf(small_font, cat_color[order[2]], 1518, 829, 0, "%2d", cat_stat[order[2]].defense);
    al_draw_textf(small_font, cat_color[order[2]], 1611, 829, 0, "%2d", cat_stat[order[2]].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1764, 829, 0, "%2d", cat_points[order[2]]);

    //if stunned
    if (cat_stun[order[2]] > 0)
    {
        al_draw_bitmap(ice, 1667, 816, 0);
        al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1690, 829, 0, "%d", cat_stun[order[2]] - 1);
    }
    //row 4
    al_draw_bitmap(pill[Pill(order[3])], 1214, 900, 0);
    al_draw_filled_circle(1782, 968, 36, cat_color[order[3]]);

    al_draw_scaled_bitmap(cat_bitmap[order[3]], 0, 0, 60, 60, 1250, 934, 64, 64, 0);
    al_draw_bitmap(dice_bitmap[dice_val[3] - 1], 1125, 932, 0);
    al_draw_bitmap(shield, 1475, 947, 0);
    al_draw_bitmap(sword, 1565, 947, 0);



    al_draw_textf(small_font, cat_color[order[3]], 1351, 949, 0, "cat %d", order[3] + 1);
    al_draw_textf(small_font, cat_color[order[3]], 1518, 949, 0, "%2d", cat_stat[order[3]].defense);
    al_draw_textf(small_font, cat_color[order[3]], 1611, 949, 0, "%2d", cat_stat[order[3]].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1764, 949, 0, "%2d", cat_points[order[3]]);

    //if stunned
    if (cat_stun[order[3]] > 0)
    {
        al_draw_bitmap(ice, 1667, 936, 0);
        al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1690, 949, 0, "%d", cat_stun[order[3]] - 1);
    }
}

int Pill(int cat)
{
    if (order[_turn - 1] == cat && cat_stun[cat] > 0) return 3;
    if (cat_stun[cat] > 0) return 2;
    if (order[_turn - 1] == cat) return 1;
    return 0;
}