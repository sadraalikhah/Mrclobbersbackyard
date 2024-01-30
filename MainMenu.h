#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "init.h"
#include "LoadGame.h"




///buttons
int button_state[3] = { 1,0,0 };
int current_button = 0;
void draw_menu();
int navigation(ALLEGRO_EVENT key);


int start_menu()
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
    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(mainQueue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:          
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            if (navigation(event))
            {
                switch (current_button)
                {
                case 0:
                    load_game();
                    return;
                case 1:
                    return;
                case 2:
                    exit(0);
                    break;
                }
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }
        if (done)
            break;


        if (redraw && al_is_event_queue_empty(mainQueue))
        {

            draw_menu();
            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(mainQueue);
}

void draw_menu()
{

    ///color pallete
    ALLEGRO_COLOR text_color[2];
    text_color[0] = al_map_rgb(192, 0, 6);
    text_color[1] = al_map_rgb(255, 72, 204);

    al_draw_bitmap(main_menu_background, 0, 0, 0);
    for (int i = 0; i < 3; i++)
    {
        al_draw_bitmap(big_pill[button_state[i]], 558, 519 + (i*161), 0);
    }
    al_draw_text(big_font, text_color[button_state[0]], 950, 560, ALLEGRO_ALIGN_CENTER, "Continue");
    al_draw_text(big_font, text_color[button_state[1]], 950, 721, ALLEGRO_ALIGN_CENTER, "New Game");
    al_draw_text(big_font, text_color[button_state[2]], 950, 882, ALLEGRO_ALIGN_CENTER, "Quit");
}

int navigation (ALLEGRO_EVENT key)
{
    switch (key.keyboard.keycode)
    {
    case (ALLEGRO_KEY_W):
    case (ALLEGRO_KEY_UP):
        button_state[current_button] = 0;
        current_button = (current_button == 0) ? 2 : current_button - 1;
        button_state[current_button] = 1;
        break;
    case (ALLEGRO_KEY_S):
    case (ALLEGRO_KEY_DOWN):
        button_state[current_button] = 0;
        current_button = (current_button == 2) ? 0 : current_button + 1;
        button_state[current_button] = 1;
        break;
    case (ALLEGRO_KEY_ENTER):
    case (ALLEGRO_KEY_SPACE):
        return 1;
        break;
    }
    return 0;
}

