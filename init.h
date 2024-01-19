#pragma once


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


///must init
void must_init(bool test, const char* description)
{
    if (test) return;

    fprintf(stderr, "couldn't initialize %s\n", description);
    exit(EXIT_FAILURE);
}

/// <summary>
/// display
/// </summary>
void display_init() {
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    must_init(display, "display");
}
void display_deinit()
{
    al_destroy_display(display);

}

/// hud
void hud_init()
{
    font = al_create_builtin_font();
    must_init(font, "font");
}
void hud_deinit()
{
    al_destroy_font(font);
}


/// sprites
void sprites_init()
{
    //house and cat_stat init
    house = al_load_bitmap("house.png");
    must_init(house, "house");
    cat1 = al_load_bitmap("cat1.png");
    must_init(cat1, "cat1");
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