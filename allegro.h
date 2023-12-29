#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "types.h"

void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int start(int wall[][14], struct pos pos_dog[])
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_primitives_addon(), "primitives");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* display = al_create_display(1500, 900);
    must_init(display, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

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

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            // game logic goes here.
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(255, 184, 60));
            al_draw_filled_rectangle(900, 0, 1600, 900, al_map_rgb_f(0, 1, 0));
            al_draw_text(font, al_map_rgb(0, 0, 0), 1000, 100, 0, "Mr. Clobber's backyard");
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
                        al_draw_line(60*i, 60*j, 60*i, 60*j + 60, al_map_rgb_f(0, 1, 0), 6);
                    }
                    else if (wall[i][j] == 2)
                    {
                        al_draw_line(60 * i, 60 * j, 60 * i + 60, 60 * j, al_map_rgb_f(0, 1, 0), 6);
                    }
                }
            }
            // dogs
            char name[20];
            for (int i = 0; i < 4; i++)
            {
                al_draw_text(font, al_map_rgb(0, 0, 0), 60*pos_dog[i].x + 15, 60 *pos_dog[i].y + 15, 0, "dog");

            }


            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}