#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "types.h"

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900


void must_init(bool test, const char* description)
{
    if (test) return;

    fprintf(stderr, "couldn't initialize %s\n", description);
    exit(EXIT_FAILURE);
}

int start(int wall[][14], struct pos pos_cat[])
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_primitives_addon(), "primitives");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    must_init(display, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");
    //house and cats init
    ALLEGRO_BITMAP* house = al_load_bitmap("house.png");
    must_init(house, "house");
    //dogs init
    ALLEGRO_BITMAP* bulldog = al_load_bitmap("bulldog.png");
    must_init(bulldog, "bulldog");
    ALLEGRO_BITMAP* pitbull = al_load_bitmap("pitbull.png");
    must_init(pitbull, "pitbull");
    ALLEGRO_BITMAP* shepherd = al_load_bitmap("shepherd.png");
    must_init(shepherd, "shepherd");
    ALLEGRO_BITMAP* bulldog_jr = al_load_bitmap("bulldog_jr.png");
    must_init(bulldog_jr, "bulldog_jr");
    //mice init
    ALLEGRO_BITMAP* mouse_1 = al_load_bitmap("mouse1.png");
    must_init(mouse_1, "mouse1");
    ALLEGRO_BITMAP* mouse_2 = al_load_bitmap("mouse2.png");
    must_init(mouse_2, "mouse2");
    ALLEGRO_BITMAP* mouse_3 = al_load_bitmap("mouse3.png");
    must_init(mouse_3, "mouse3");
    //traps init
    ALLEGRO_BITMAP* _trap = al_load_bitmap("trap.png");
    must_init(_trap, "trap");
    //chocolates init
    ALLEGRO_BITMAP* _choco = al_load_bitmap("chocolate.png");
    must_init(_choco, "chocolate");
    //fish init
    ALLEGRO_BITMAP* _fish = al_load_bitmap("fish.png");
    must_init(_fish, "fish");

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
            turn++;
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            //*MAIN BOARD*//
            al_clear_to_color(al_map_rgb(255, 184, 60));

            // grid
            for (int i = 1; i < 15; i++)
            {
                al_draw_line(0, 60 * i, 900, 60 * i, al_map_rgb_f(0, 0, 0), 2);
                al_draw_line(60*i, 0, 60*i, 900, al_map_rgb_f(0, 0, 0), 2);
            }
            // walls
            for (int i = 1; i < 14; i++)
            {
                for (int j = 1; j < 14; j++)
                {
                    if (wall[i][j] == 1)
                    {
                        al_draw_line(60*i, 60*j, 60*i, 60*j + 60, al_map_rgb(107, 38, 22), 8);
                    }
                    else if (wall[i][j] == 2)
                    {
                        al_draw_line(60 * i, 60 * j, 60 * i + 60, 60 * j, al_map_rgb(107, 38, 22), 8);
                    }
                }
            }
            //starting house
            al_draw_bitmap(house, 60 * 7 + 5, 60 * 7 + 5, 0);

            // dogs
            al_draw_bitmap(bulldog, 60 * pos_dog[0].x + 5, 60 * pos_dog[0].y + 5, 0);
            al_draw_bitmap(pitbull, 60 * pos_dog[1].x + 5, 60 * pos_dog[1].y + 5, 0);
            al_draw_bitmap(shepherd, 60 * pos_dog[2].x + 5, 60 * pos_dog[2].y + 5, 0);
            al_draw_bitmap(bulldog_jr, 60 * pos_dog[3].x + 5, 60 * pos_dog[3].y + 5, 0);

            //mice
            for (int i = 0; i < 10; i++)
            {
                al_draw_bitmap(mouse_1, 60 * mouse1[i].x + 5, 60 * mouse1[i].y + 5, 0);
            }
            for (int i = 0; i < 6; i++)
            {
                al_draw_bitmap(mouse_2, 60 * mouse2[i].x + 5, 60 * mouse2[i].y + 5, 0);
            }
            for (int i = 0; i < 4; i++)
            {
                al_draw_bitmap(mouse_3, 60 * mouse3[i].x + 5, 60 * mouse3[i].y + 5, 0);
            }
            //traps
            for (int i = 0; i < 8; i++)
            {
                al_draw_bitmap(_trap, 60 * trap[i].x + 5, 60 * trap[i].y + 5, 0);
            }
            //chocolates
            for (int i = 0; i < 6; i++)
            {
                al_draw_bitmap(_choco, 60 * chocolate[i].x + 5, 60 * chocolate[i].y + 5, 0);
            }
            //fish
            for (int i = 0; i < 10; i++)
            {
                al_draw_bitmap(_fish, 60 * fish[i].x + 5, 60 * fish[i].y + 5, 0);
            }

            //*STATS BOARD*//
            al_draw_filled_rectangle(900, 0, 1600, 900, al_map_rgb(247, 52, 52));
            al_draw_text(font, al_map_rgb(0, 0, 0), 1000, 100, 0, "Mr. Clobber's backyard");
            al_draw_textf(font, al_map_rgb(0, 0, 0), 1100, 200, 0, "Turn: %d", turn);

            al_flip_display();

            redraw = false;
        }
    }

    //destroy the created files
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(house);
    al_destroy_bitmap(bulldog);
    al_destroy_bitmap(pitbull);
    al_destroy_bitmap(shepherd);
    al_destroy_bitmap(bulldog_jr);
    al_destroy_bitmap(mouse_1);
    al_destroy_bitmap(mouse_2);
    al_destroy_bitmap(mouse_3);
    al_destroy_bitmap(_trap);
    al_destroy_bitmap(_fish);
    al_destroy_bitmap(_choco);

    return 0;
}