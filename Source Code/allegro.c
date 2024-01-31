
#include "allegro.h"
#include <allegro5/allegro_font.h>
#include <cstdio>

void must_init(bool test, const char* description) {
    if (test) return;

    fprintf(stderr, "Failed to initialize %s\n", description);
    exit(EXIT_FAILURE);
}

void initialize_allegro(ALLEGRO_FONT** font, ALLEGRO_DISPLAY** display, ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** queue, ALLEGRO_BITMAP* bitmaps[], int num_bitmaps) {
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_primitives_addon(), "primitives");

    *timer = al_create_timer(1.0 / 30.0);
    must_init(*timer, "timer");

    *queue = al_create_event_queue();
    must_init(*queue, "queue");

    *display = al_create_display(1500, 900);
    must_init(*display, "display");

    // Initialize the font addon
    must_init(al_init_font_addon(), "font addon");
    must_init(al_init_ttf_addon(), "ttf addon");

    // Load a basic font (you can replace this with your own font loading logic)
    *font = al_create_builtin_font();
    must_init(*font, "font");

    must_init(al_init_image_addon(), "image addon");

    // Load bitmaps
    const char* filenames[] = { "house.png", "bulldog.png", "pitbull.png", "shepherd.png", "bulldog_jr.png", "mouse1.png", "mouse2.png", "mouse3.png", "trap.png", "chocolate.png", "fish.png" };
    load_bitmaps(bitmaps, filenames, num_bitmaps);

    for (int i = 0; i < num_bitmaps; i++) {
        must_init(bitmaps[i], filenames[i]);
    }

    al_register_event_source(*queue, al_get_keyboard_event_source());
    al_register_event_source(*queue, al_get_display_event_source(*display));
    al_register_event_source(*queue, al_get_timer_event_source(*timer));
}


void load_bitmaps(ALLEGRO_BITMAP* bitmaps[], const char* filenames[], int num_bitmaps) {
    for (int i = 0; i < num_bitmaps; i++) {
        bitmaps[i] = al_load_bitmap(filenames[i]);
    }
}

void draw_game_board(int wall[][14], struct pos pos_cat[], struct pos pos_dog[], struct pos mouse1[], struct pos mouse2[], struct pos mouse3[], struct pos chocolate[], struct pos trap[], struct pos fish[]) {
    // Clear the screen
    al_clear_to_color(al_map_rgb(255, 184, 60));

    // Draw grid lines
    for (int i = 1; i < 15; i++) {
        al_draw_line(0, 60 * i, 900, 60 * i, al_map_rgb_f(0, 0, 0), 2);
        al_draw_line(60 * i, 0, 60 * i, 900, al_map_rgb_f(0, 0, 0), 2);
    }

    // Draw walls
    for (int i = 1; i < 14; i++) {
        for (int j = 1; j < 14; j++) {
            if (wall[i][j] == 1) {
                al_draw_line(60 * i, 60 * j, 60 * i, 60 * j + 60, al_map_rgb(107, 38, 22), 8);
            }
            else if (wall[i][j] == 2) {
                al_draw_line(60 * i, 60 * j, 60 * i + 60, 60 * j, al_map_rgb(107, 38, 22), 8);
            }
        }
    }

    // Draw starting house
    al_draw_bitmap(house, 60 * 7 + 5, 60 * 7 + 5, 0);

    // Draw dogs
    for (int i = 0; i < 4; i++) {
        int dog_type = pos_dog[i].type - 200;
        al_draw_bitmap(dog_bitmaps[dog_type], 60 * pos_dog[i].x + 5, 60 * pos_dog[i].y + 5, 0);
    }

    // Draw mice
    draw_entities(mouse1, 10, mouse1_bitmap);
    draw_entities(mouse2, 6, mouse2_bitmap);
    draw_entities(mouse3, 4, mouse3_bitmap);

    // Draw traps
    draw_entities(trap, 8, trap_bitmap);

    // Draw chocolates
    draw_entities(chocolate, 6, chocolate_bitmap);

    // Draw fish
    draw_entities(fish, 10, fish_bitmap);

    // Flip the display to make changes visible
    al_flip_display();
}

// Helper function to draw an array of entities
void draw_entities(struct pos entities[], int num_entities, ALLEGRO_BITMAP* entity_bitmap) {
    for (int i = 0; i < num_entities; i++) {
        al_draw_bitmap(entity_bitmap, 60 * entities[i].x + 5, 60 * entities[i].y + 5, 0);
    }
}

bool handle_events(ALLEGRO_EVENT_QUEUE* queue) {
    ALLEGRO_EVENT event;
    bool done = false;

    while (al_get_next_event(queue, &event)) {
        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            // Update game logic here based on the timer event
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            // Handle key presses
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                done = true; // Exit the game when the ESC key is pressed
                break;
                // Handle other key presses as needed
            }
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true; // Exit the game when the window is closed
            break;

            // Handle other events as needed

        default:
            break;
        }
    }

    return done;
    return false; // Modify as needed
}

void cleanup_resources(ALLEGRO_FONT* font, ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_BITMAP* bitmaps[], int num_bitmaps) {
    for (int i = 0; i < num_bitmaps; i++) {
        al_destroy_bitmap(bitmaps[i]);
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

int start(int wall[][14], struct pos pos_cat[], struct pos pos_dog[], struct pos mouse1[], struct pos mouse2[], struct pos mouse3[], struct pos chocolate[], struct pos trap[], struct pos fish[]) {
    // Variables for Allegro components
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_FONT* font = NULL;

    // Array of bitmaps for different entities
    ALLEGRO_BITMAP* bitmaps[11];

    // Initialize Allegro components
    initialize_allegro(&font, &display, &timer, &event_queue, bitmaps, 11);

    // Game state variables (replace with your actual game state)
    int wall[14][14] = { 0 };
    struct pos pos_cat[4];
    struct pos pos_dog[4];
    struct pos mouse1[10];
    struct pos mouse2[6];
    struct pos mouse3[4];
    struct pos chocolate[6];
    struct pos trap[8];
    struct pos fish[10];

    // Main game loop
    bool done = false;
    bool redraw = true;

    al_start_timer(timer);

    while (!done) {
        redraw = !handle_events(event_queue);

        if (redraw && al_is_event_queue_empty(event_queue)) {
            // Update game logic

            // Draw the game board
            draw_game_board(wall, pos_cat, pos_dog, mouse1, mouse2, mouse3, chocolate, trap, fish);
        }
    }

    // Cleanup resources
    cleanup_resources(font, display, timer, event_queue, bitmaps, 11);

    return 0;
}
