#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "types.h"
#include "init.h"
#include "logics.h"


///draw
void draw_board();
void draw_scoreboard();

///keyboard


int start()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_primitives_addon(), "primitives");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    display_init();
    hud_init();

    must_init(al_init_image_addon(), "image addon");
    sprites_init();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);
        
        //logic definitions
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            // game logic goes here.
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            sprites_update(event);
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }
        if (done)
            break;


        if (redraw && al_is_event_queue_empty(queue))
        {
            if (_round < 16)
            {
                draw_board();
                draw_scoreboard();
            }
            else
            {
                al_clear_to_color(al_map_rgb_f(1, 1, 1));
                al_draw_text(big_font, al_map_rgb_f(0, 0, 0), 750, 450, 0, "GAME OVER");
            }

            al_flip_display();

               redraw = false;
        }
    }

    //destroy the created files
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    hud_deinit();
    display_deinit();
    sprites_deinit();


    return 0;
}

void draw_board()
{
    //*MAIN BOARD*//
    al_clear_to_color(al_map_rgb(255, 184, 60));

    // grid
    for (int i = 1; i < 15; i++)
    {
        al_draw_line(0, 60 * i, 900, 60 * i, al_map_rgb_f(0, 0, 0), 2);
        al_draw_line(60 * i, 0, 60 * i, 900, al_map_rgb_f(0, 0, 0), 2);
    }
    // walls
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {

            switch (wall[i][j])
            {
            case 'L':
                al_draw_line(60 * j, 60 * i, 60 * j, 60 * i + 60, al_map_rgb(107, 38, 22), 8);

                break;
            case 'U':
                al_draw_line(60 * j, 60 * i, 60 * j + 60, 60 * i, al_map_rgb(107, 38, 22), 8);


                break;
            }
        }
    }
    //starting house
    al_draw_bitmap(house, 60 * 7 + 5, 60 * 7 + 5, 0);

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
                            al_draw_bitmap(cat_bitmap[0], 60 * j + 5, 60 * i + 5, 0);
                            break;
                        case 1:
                            al_draw_bitmap(cat_bitmap[1], 60 * j + 5, 60 * i + 5, 0);
                            break;
                        case 2:
                            al_draw_bitmap(cat_bitmap[2], 60 * j + 5, 60 * i + 5, 0);
                            break;
                        case 3:
                            al_draw_bitmap(cat_bitmap[3], 60 * j + 5, 60 * i + 5, 0);
                            break;
                        }
                        break;
                    case 2:
                        switch (board[i][j][k] % 10)
                        {
                        case 0:
                            al_draw_bitmap(bulldog, 60 * j + 5, 60 * i + 5, 0);
                            break;
                        case 1:
                            al_draw_bitmap(pitbull, 60 * j + 5, 60 * i + 5, 0);
                            break;
                        case 2:
                            al_draw_bitmap(shepherd, 60 * j + 5, 60 * i + 5, 0);
                            break;
                        case 3:
                            al_draw_bitmap(bulldog_jr, 60 * j + 5, 60 * i + 5, 0);
                            break;
                        }
                        break;
                    case 3:
                        al_draw_bitmap(mouse_1, 60 * j + 5, 60 * i + 5, 0);
                        break;
                    case 4:
                        al_draw_bitmap(mouse_2, 60 * j + 5, 60 * i + 5, 0);
                        break;
                    case 5:
                        al_draw_bitmap(mouse_3, 60 * j + 5, 60 * i + 5, 0);
                        break;
                    case 6:
                        al_draw_bitmap(_choco, 60 * j + 5, 60 * i + 5, 0);
                        break;
                    case 8:
                        al_draw_bitmap(_fish, 60 * j + 5, 60 * i + 5, 0);
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
                            al_draw_scaled_bitmap(cat_bitmap[0], 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                            break;
                        case 1:
                            al_draw_scaled_bitmap(cat_bitmap[1], 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                            break;
                        case 2:
                            al_draw_scaled_bitmap(cat_bitmap[2], 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                            break;
                        case 3:
                            al_draw_scaled_bitmap(cat_bitmap[3], 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                            break;
                        }
                        break;
                    case 2:
                        switch (board[i][j][k] % 10)
                        {
                        case 0:
                            al_draw_scaled_bitmap(bulldog, 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                            break;
                        case 1:
                            al_draw_scaled_bitmap(pitbull, 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                            break;
                        case 2:
                            al_draw_scaled_bitmap(shepherd, 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                            break;
                        case 3:
                            al_draw_scaled_bitmap(bulldog_jr, 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                            break;
                        }
                        break;
                    case 3:
                        al_draw_scaled_bitmap(mouse_1, 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                        break;
                    case 4:
                        al_draw_scaled_bitmap(mouse_2, 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                        break;
                    case 5:
                        al_draw_scaled_bitmap(mouse_3, 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                        break;
                    case 6:
                        al_draw_scaled_bitmap(_choco, 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                        break;
                    case 8:
                        al_draw_scaled_bitmap(_fish, 0, 0, 50, 50, 60 * j + (k % 2) * 27 + 3, 60 * i + (k / 2) * 27 + 3, 25, 25, 0);
                        break;
                    }
                }
            }
            //traps
            if (trapBoard[i][j])
                if (trap_vis[(trapBoard[i][j]) % 10])
                    al_draw_tinted_bitmap(_trap, al_map_rgba_f(1, 1, 1, 0.5), 60 * j + 5, 60 * i + 5, 0);
        }
    }
}

/// <summary>
/// scoreboard
/// </summary>
void draw_scoreboard()
{

    ///color pallete
    ALLEGRO_COLOR activeC = al_map_rgb(255, 226, 152);
    ALLEGRO_COLOR inactiveC = al_map_rgb(204, 204, 204);
    ALLEGRO_COLOR currentC = al_map_rgb(255, 184, 0);
    ALLEGRO_COLOR currentInactiveC = al_map_rgb(255, 133, 133);
    ALLEGRO_COLOR scoreboardC = al_map_rgb(222, 38, 38);


    //*STATS BOARD*//
    al_draw_filled_rectangle(900, 0, 1600, 900, scoreboardC);
    al_draw_text(big_font, al_map_rgb(0, 0, 0), 1000, 100, 0, "Mr. Clobber's backyard");


    //cat colors
    ALLEGRO_COLOR cat_color[4];
    for (int i = 0; i < 4; i++)
    {
        if (cat_loss[i] == 0)
        {
            cat_color[i] = activeC;
            if (order[_turn - 1] == i) cat_color[i] = currentC;
        }
        else
        {
            cat_color[i] = inactiveC;
            if (order[_turn - 1] == i) cat_color[i] = currentInactiveC;
        }
    }

    //round
    al_draw_filled_circle(1000, 325, 25, activeC, 0);
    al_draw_filled_rectangle(1000, 300, 1100, 350, activeC, 0);
    al_draw_filled_circle(1100, 325, 25, activeC, 0);
    al_draw_textf(big_font, al_map_rgb(0, 0, 0), 1000, 312, 0, "round      %d", _round);

    //move
    al_draw_filled_circle(1300, 325, 25, activeC, 0);
    al_draw_filled_rectangle(1300, 300, 1400, 350, activeC, 0);
    al_draw_filled_circle(1400, 325, 25, activeC, 0);
    al_draw_textf(big_font, al_map_rgb(0, 0, 0), 1300, 312, 0, "move      %d", _move);


    //cat 1
    al_draw_filled_circle(1000, 425, 25, cat_color[order[0]], 0);
    al_draw_filled_rectangle(1000, 400, 1400, 450, cat_color[order[0]], 0);
    al_draw_filled_circle(1400, 425, 25, cat_color[order[0]], 0);
    al_draw_filled_circle(1400, 425, 19, scoreboardC, 0);

    al_draw_scaled_bitmap(cat_bitmap[order[0]], 0, 0, 50, 50, 990, 410, 30, 30, 0);

    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1050, 416, 0, "cat %d", order[0]+1);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1150, 416, 0, "Energy: %d", cat_stat[order[0]].defense);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1250, 416, 0, "Power: %d", cat_stat[order[0]].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1391, 416, 0, "%2d", cat_points[order[0]]);

    //cat 2
    al_draw_filled_circle(1000, 491, 25, cat_color[order[1]], 0);
    al_draw_filled_rectangle(1000, 466, 1400, 516, cat_color[order[1]], 0);
    al_draw_filled_circle(1400, 491, 25, cat_color[order[1]], 0);
    al_draw_filled_circle(1400, 491, 19, scoreboardC, 0);

    al_draw_scaled_bitmap(cat_bitmap[order[1]], 0, 0, 50, 50, 990, 476, 30, 30, 0);

    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1050, 482, 0, "cat %d", order[1]+1);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1150, 482, 0, "Energy: %d", cat_stat[order[1]].defense);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1250, 482, 0, "Power: %d", cat_stat[order[1]].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1391, 482, 0, "%2d", cat_points[order[1]]);
    //cat 3
    al_draw_filled_circle(1000, 557, 25, cat_color[order[2]], 0);
    al_draw_filled_rectangle(1000, 532, 1400, 582, cat_color[order[2]], 0);
    al_draw_filled_circle(1400, 557, 25, cat_color[order[2]], 0);
    al_draw_filled_circle(1400, 557, 19, scoreboardC, 0);

    al_draw_scaled_bitmap(cat_bitmap[order[2]], 0, 0, 50, 50, 990, 542, 30, 30, 0);

    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1050, 548, 0, "cat %d", order[2]+1);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1150, 548, 0, "Energy: %d", cat_stat[order[2]].defense);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1250, 548, 0, "Power: %d", cat_stat[order[2]].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1391, 548, 0, "%2d", cat_points[order[2]]);
    //cat 4
    al_draw_filled_circle(1000, 623, 25, cat_color[order[3]], 0);
    al_draw_filled_rectangle(1000, 598, 1400, 648, cat_color[order[3]], 0);
    al_draw_filled_circle(1400, 623, 25, cat_color[order[3]], 0);
    al_draw_filled_circle(1400, 623, 19, scoreboardC, 0);

    al_draw_scaled_bitmap(cat_bitmap[order[3]], 0, 0, 50, 50, 990, 608, 30, 30, 0);

    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1050, 614, 0, "cat %d", order[3]+1);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1150, 614, 0, "Energy: %d", cat_stat[order[3]].defense);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1250, 614, 0, "Power: %d", cat_stat[order[3]].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1391, 614, 0, "%2d", cat_points[order[3]]);
}
