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
int button_state_pause[3] = { 1,0,0 };
int current_button_pause = 0;
int navigation_pause(ALLEGRO_EVENT key);

int button_state_confirmation[2] = { 1,0 };
int current_button_confirmation = 0;
int navigation_confirmation(ALLEGRO_EVENT key);


///menu
void guide_menu(ALLEGRO_EVENT_QUEUE* mainQueue, ALLEGRO_TIMER* timer);
void confirmation_menu(ALLEGRO_EVENT_QUEUE* mainQueue, ALLEGRO_TIMER* timer);


///draw
void draw_pause_menu();
void draw_guide();
void draw_confirmation();

int pause_game(ALLEGRO_EVENT_QUEUE* mainQueue, ALLEGRO_TIMER* timer)
{

    al_register_event_source(mainQueue, al_get_keyboard_event_source());
    al_register_event_source(mainQueue, al_get_display_event_source(display));
    al_register_event_source(mainQueue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;
    while (1)
    {
        ///change the screen depen
        al_wait_for_event(mainQueue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            //already defined in MainMenu.h
            if (navigation_pause(event))
            {
                switch (current_button_pause)
                {
                case 0:
                    return 0;
                case 1:
                    guide_menu(mainQueue, timer);
                    break;
                case 2:
                    confirmation_menu(mainQueue, timer);
                    break;
                }
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            exit(0);
        }
        if (done)
            break;


        if (redraw && al_is_event_queue_empty(mainQueue))
        {

            draw_pause_menu();
            al_flip_display();
            redraw = false;
        }
    }
}


void guide_menu(ALLEGRO_EVENT_QUEUE* mainQueue, ALLEGRO_TIMER* timer)
{
    al_register_event_source(mainQueue, al_get_keyboard_event_source());
    al_register_event_source(mainQueue, al_get_display_event_source(display));
    al_register_event_source(mainQueue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;
    while (1)
    {
        ///change the screen depen
        al_wait_for_event(mainQueue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            done = true;
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            exit(0);
        }
        if (done)
            break;


        if (redraw && al_is_event_queue_empty(mainQueue))
        {

            draw_guide();
            al_flip_display();
            redraw = false;
        }
    }
}


void confirmation_menu(ALLEGRO_EVENT_QUEUE* mainQueue, ALLEGRO_TIMER* timer)
{
    al_register_event_source(mainQueue, al_get_keyboard_event_source());
    al_register_event_source(mainQueue, al_get_display_event_source(display));
    al_register_event_source(mainQueue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;
    while (1)
    {
        ///change the screen depen
        al_wait_for_event(mainQueue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            if (navigation_confirmation(event))
            {
                switch (current_button_confirmation)
                {
                case 0:
                    return;
                case 1:
                    exit(0);
                }
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            exit(0);
        }
        if (done)
            break;


        if (redraw && al_is_event_queue_empty(mainQueue))
        {

            draw_confirmation();
            al_flip_display();
            redraw = false;
        }
    }
}


///draw
void draw_pause_menu()
{

    ///color pallete
    ALLEGRO_COLOR text_color[2];
    text_color[0] = al_map_rgb(192, 0, 6);
    text_color[1] = al_map_rgb(255, 72, 204);

    al_draw_bitmap(pause_background, 0, 0, 0);
    for (int i = 0; i < 3; i++)
    {
        al_draw_bitmap(big_pill[button_state_pause[i]], 559, 427 + (i * 185), 0);
    }
    al_draw_text(big_font, text_color[button_state_pause[0]], 950, 467, ALLEGRO_ALIGN_CENTER, "Continue");
    al_draw_text(big_font, text_color[button_state_pause[1]], 950, 652, ALLEGRO_ALIGN_CENTER, "Guide");
    al_draw_text(big_font, text_color[button_state_pause[2]], 950, 837, ALLEGRO_ALIGN_CENTER, "Quit");
}


void draw_guide()
{
    al_draw_bitmap(guide, 0, 0, 0);

}

void draw_confirmation()
{
    ///color pallete
    ALLEGRO_COLOR text_color[2];
    text_color[0] = al_map_rgb(192, 0, 6);
    text_color[1] = al_map_rgb(255, 72, 204);

    al_draw_bitmap(confirmation, 0, 0, 0);
    for (int i = 0; i < 2; i++)
    {
        al_draw_bitmap(big_pill[button_state_confirmation[i]], 559, 477 + (i * 185), 0);
    }
    al_draw_text(big_font, text_color[button_state_confirmation[0]], 950, 517, ALLEGRO_ALIGN_CENTER, "No");
    al_draw_text(big_font, text_color[button_state_confirmation[1]], 950, 702, ALLEGRO_ALIGN_CENTER, "Yes");
}

int navigation_pause(ALLEGRO_EVENT key)
{
    switch (key.keyboard.keycode)
    {
    case (ALLEGRO_KEY_W):
    case (ALLEGRO_KEY_UP):
        button_state_pause[current_button_pause] = 0;
        current_button_pause = (current_button_pause == 0) ? 2 : current_button_pause - 1;
        button_state_pause[current_button_pause] = 1;
        break;
    case (ALLEGRO_KEY_S):
    case (ALLEGRO_KEY_DOWN):
        button_state_pause[current_button_pause] = 0;
        current_button_pause = (current_button_pause == 2) ? 0 : current_button_pause + 1;
        button_state_pause[current_button_pause] = 1;
        break;
    case (ALLEGRO_KEY_ENTER):
    case (ALLEGRO_KEY_SPACE):
        return 1;
        break;
    case (ALLEGRO_KEY_ESCAPE):
        current_button_confirmation = 0;
        return 1;
        break;
    }
    return 0;
}

int navigation_confirmation(ALLEGRO_EVENT key)
{
    switch (key.keyboard.keycode)
    {
    case (ALLEGRO_KEY_W):
    case (ALLEGRO_KEY_UP):
        button_state_confirmation[current_button_confirmation] = 0;
        current_button_confirmation = (current_button_confirmation == 0) ? 1 : current_button_confirmation - 1;
        button_state_confirmation[current_button_confirmation] = 1;
        break;
    case (ALLEGRO_KEY_S):
    case (ALLEGRO_KEY_DOWN):
        button_state_confirmation[current_button_confirmation] = 0;
        current_button_confirmation = (current_button_confirmation == 1) ? 0 : current_button_confirmation + 1;
        button_state_confirmation[current_button_confirmation] = 1;
        break;
    case (ALLEGRO_KEY_ENTER):
    case (ALLEGRO_KEY_SPACE):
        return 1;
        break;
    case (ALLEGRO_KEY_ESCAPE):
        current_button_confirmation = 0;
        return 1;
        break;
    }
    return 0;
}