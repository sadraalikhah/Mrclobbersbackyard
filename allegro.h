#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
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
                al_draw_text(font, al_map_rgb_f(0, 0, 0), 750, 450, 0, "GAME OVER");
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
            for (int k = 0; k < 4; k++)
            {
                switch (board[i][j][k] / 100)
                {
                case 1:
                    switch (board[i][j][k] % 10)
                    {
                    case 0:
                        al_draw_bitmap(cat1, 60 * j + 5, 60 * i + 5, 0);
                        break;
                    case 1:
                        al_draw_bitmap(cat2, 60 * j + 5, 60 * i + 5, 0);
                        break;
                    case 2:
                        al_draw_bitmap(cat3, 60 * j + 5, 60 * i + 5, 0);
                        break;
                    case 3:
                        al_draw_bitmap(cat4, 60 * j + 5, 60 * i + 5, 0);
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
                case 7:
                    al_draw_bitmap(_trap, 60 * j + 5, 60 * i + 5, 0);
                    break;
                case 8:
                    al_draw_bitmap(_fish, 60 * j + 5, 60 * i + 5, 0);
                    break;
                }
            }
        }
    }
}

/// <summary>
/// scoreboard
/// </summary>
void draw_scoreboard()
{
    //*STATS BOARD*//
    al_draw_filled_rectangle(900, 0, 1600, 900, al_map_rgb(247, 52, 52));
    al_draw_text(big_font, al_map_rgb(0, 0, 0), 1000, 100, 0, "Mr. Clobber's backyard");

    //color pallete
    ALLEGRO_COLOR active = al_map_rgb(255, 226, 152);
    ALLEGRO_COLOR inactive = al_map_rgb(255, 226, 152);
    ALLEGRO_COLOR current = al_map_rgb(255, 226, 152);


    //round
    al_draw_filled_circle(1000, 325, 25, active, 0);
    al_draw_filled_rectangle(1000, 300, 1100, 350, active, 0);
    al_draw_filled_circle(1100, 325, 25, active, 0);
    al_draw_textf(big_font, al_map_rgb(0, 0, 0), 1000, 312, 0, "round      %d", _round);

    //move
    al_draw_filled_circle(1300, 325, 25, active, 0);
    al_draw_filled_rectangle(1300, 300, 1400, 350, active, 0);
    al_draw_filled_circle(1400, 325, 25, active, 0);
    al_draw_textf(big_font, al_map_rgb(0, 0, 0), 1300, 312, 0, "move      %d", _move);


    //cat 1
    al_draw_filled_circle(1000, 425, 25, active, 0);
    al_draw_filled_rectangle(1000, 400, 1400, 450, active, 0);
    al_draw_filled_circle(1400, 425, 25, active, 0);
    al_draw_filled_circle(1400, 425, 19, al_map_rgb(255, 0, 0), 0);

    al_draw_scaled_bitmap(cat1, 0, 0, 50, 50, 990, 410, 30, 30, 0);

    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1050, 416, 0, "cat 1");
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1150, 416, 0, "Energy: %d", cat_stats[0].defense);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1250, 416, 0, "Power: %d", cat_stats[0].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1395, 416, 0, "%d", cat_point[0]);

    //cat 2
    al_draw_filled_circle(1000, 491, 25, active, 0);
    al_draw_filled_rectangle(1000, 466, 1400, 516, active, 0);
    al_draw_filled_circle(1400, 491, 25, active, 0);
    al_draw_filled_circle(1400, 491, 19, al_map_rgb(255, 0, 0), 0);

    al_draw_scaled_bitmap(cat2, 0, 0, 50, 50, 990, 476, 30, 30, 0);

    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1050, 482, 0, "cat 2");
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1150, 482, 0, "Energy: %d", cat_stats[1].defense);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1250, 482, 0, "Power: %d", cat_stats[1].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1395, 482, 0, "%d", cat_point[1]);
    //cat 3
    al_draw_filled_circle(1000, 557, 25, active, 0);
    al_draw_filled_rectangle(1000, 532, 1400, 582, active, 0);
    al_draw_filled_circle(1400, 557, 25, active, 0);
    al_draw_filled_circle(1400, 557, 19, al_map_rgb(255, 0, 0), 0);

    al_draw_scaled_bitmap(cat3, 0, 0, 50, 50, 990, 542, 30, 30, 0);

    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1050, 548, 0, "cat 3");
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1150, 548, 0, "Energy: %d", cat_stats[2].defense);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1250, 548, 0, "Power: %d", cat_stats[2].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1395, 548, 0, "%d", cat_point[2]);
    //cat 4
    al_draw_filled_circle(1000, 621, 25, active, 0);
    al_draw_filled_rectangle(1000, 596, 1400, 646, active, 0);
    al_draw_filled_circle(1400, 621, 25, active, 0);
    al_draw_filled_circle(1400, 621, 19, al_map_rgb(255, 0, 0), 0);

    al_draw_scaled_bitmap(cat4, 0, 0, 50, 50, 990, 608, 30, 30, 0);

    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1050, 612, 0, "cat 4");
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1150, 612, 0, "Energy: %d", cat_stats[3].defense);
    al_draw_textf(small_font, al_map_rgb(0, 0, 0), 1250, 612, 0, "Power: %d", cat_stats[3].attack);
    al_draw_textf(small_font, al_map_rgb(255, 255, 255), 1395, 612, 0, "%d", cat_point[3]);
}
