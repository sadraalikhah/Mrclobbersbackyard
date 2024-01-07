#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "types.h"
#include "logics.h"

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900

///display
ALLEGRO_DISPLAY* display;
void display_init();
void display_deinit();

///hud
ALLEGRO_FONT* font;
void hud_init();
void hud_deinit();

///sprites
ALLEGRO_BITMAP* house;
ALLEGRO_BITMAP* cat1;
ALLEGRO_BITMAP* cat2;
ALLEGRO_BITMAP* cat3;
ALLEGRO_BITMAP* cat4;
ALLEGRO_BITMAP* bulldog;
ALLEGRO_BITMAP* pitbull;
ALLEGRO_BITMAP* shepherd;
ALLEGRO_BITMAP* bulldog_jr;
ALLEGRO_BITMAP* mouse_1;
ALLEGRO_BITMAP* mouse_2;
ALLEGRO_BITMAP* mouse_3;
ALLEGRO_BITMAP* _trap;
ALLEGRO_BITMAP* _choco;
ALLEGRO_BITMAP* _fish;
void sprites_init();
void sprites_deinit();


///draw
void draw_board();
void draw_scoreboard();

///keyboard

///logistics
void cat_update(ALLEGRO_EVENT event);

void must_init(bool test, const char* description)
{
    if (test) return;

    fprintf(stderr, "couldn't initialize %s\n", description);
    exit(EXIT_FAILURE);
}

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
            cat_update(event);
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
    for (int i = 1; i < 14; i++)
    {
        for (int j = 1; j < 14; j++)
        {
            switch (wall[i][j])
            {
            case 'D':
                al_draw_line(60 * i, 60 * j, 60 * i, 60 * j + 60, al_map_rgb(107, 38, 22), 8);
                break;
            case 'R':
                al_draw_line(60 * i, 60 * j, 60 * i + 60, 60 * j, al_map_rgb(107, 38, 22), 8);
                break;
            }
        }
    }
    //starting house
    al_draw_bitmap(house, 60 * 7 + 5, 60 * 7 + 5, 0);

    //cats
    al_draw_bitmap(cat1, 60 * pos_cat[0].x + 5, 60 * pos_cat[0].y + 5, 0);
    al_draw_bitmap(cat2, 60 * pos_cat[1].x + 5, 60 * pos_cat[1].y + 5, 0);
    al_draw_bitmap(cat3, 60 * pos_cat[2].x + 5, 60 * pos_cat[2].y + 5, 0);
    al_draw_bitmap(cat4, 60 * pos_cat[3].x + 5, 60 * pos_cat[3].y + 5, 0);


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
}

void draw_scoreboard()
{
    //*STATS BOARD*//
    al_draw_filled_rectangle(900, 0, 1600, 900, al_map_rgb(247, 52, 52));
    al_draw_text(font, al_map_rgb(0, 0, 0), 1000, 100, 0, "Mr. Clobber's backyard");
    al_draw_textf(font, al_map_rgb(0, 0, 0), 1100, 200, 0, "_round: %d", _round);
}

void display_init() {
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    must_init(display, "display");
}
void display_deinit()
{
    al_destroy_display(display);

}

void hud_init()
{
    font = al_create_builtin_font();
    must_init(font, "font");
}
void hud_deinit()
{
    al_destroy_font(font);
}


void sprites_init()
{
    //house and cats init
    house = al_load_bitmap("house.png");
    must_init(house, "house");
    cat1 = al_load_bitmap("cat1.png");
    must_init(cat1, "house");
    cat2 = al_load_bitmap("cat2.png");
    must_init(cat2, "cat2");
    cat3 = al_load_bitmap("cat3.png");
    must_init(cat3, "cat3");
    cat4 = al_load_bitmap("cat4.png");
    must_init(cat4, "cat4");
    //dogs init
    bulldog = al_load_bitmap("bulldog.png");
    must_init(bulldog, "bulldog");
    pitbull = al_load_bitmap("pitbull.png");
    must_init(pitbull, "pitbull");
    shepherd = al_load_bitmap("shepherd.png");
    must_init(shepherd, "shepherd");
    bulldog_jr = al_load_bitmap("bulldog_jr.png");
    must_init(bulldog_jr, "bulldog_jr");
    //mice init
    mouse_1 = al_load_bitmap("mouse1.png");
    must_init(mouse_1, "mouse1");
    mouse_2 = al_load_bitmap("mouse2.png");
    must_init(mouse_2, "mouse2");
    mouse_3 = al_load_bitmap("mouse3.png");
    must_init(mouse_3, "mouse3");
    //traps init
    _trap = al_load_bitmap("trap.png");
    must_init(_trap, "trap");
    //chocolates init
    _choco = al_load_bitmap("chocolate.png");
    must_init(_choco, "chocolate");
    //fish init
    _fish = al_load_bitmap("fish.png");
    must_init(_fish, "fish");
}

void sprites_deinit()
{
    al_destroy_bitmap(house);
    al_destroy_bitmap(cat1);
    al_destroy_bitmap(cat2);
    al_destroy_bitmap(cat3);
    al_destroy_bitmap(cat4);
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
}


///logics
void cat_update(ALLEGRO_EVENT event)
{
            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
            {
                if (isLegal(pos_cat[1].y - 1, pos_cat[1].x, 1))
                {
                    pos_cat[1].y--;
                }
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
                if (isLegal(pos_cat[1].y + 1, pos_cat[1].x, 3))
                {
                    pos_cat[1].y++;

                }
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
            {
                if (isLegal(pos_cat[1].y, pos_cat[1].x - 1, 2))
                {
                    pos_cat[1].x--;
                }
            }  
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
            {
                if (isLegal(pos_cat[1].y, pos_cat[1].x + 1, 4))
                {
                    pos_cat[1].x++;
                }
            }
}