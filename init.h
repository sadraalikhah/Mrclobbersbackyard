#pragma once


#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900


///display
ALLEGRO_DISPLAY* display;
void display_init();
void display_deinit();

///hud
ALLEGRO_BITMAP* HUD_logo;
ALLEGRO_BITMAP* dice_bitmap[6];
ALLEGRO_FONT* small_font;
ALLEGRO_FONT* big_font;
void hud_init();
void hud_deinit();

///sprites
ALLEGRO_BITMAP* house;
ALLEGRO_BITMAP* cat_bitmap[4];
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

///end_screen
ALLEGRO_FONT* end_screen_font;
ALLEGRO_BITMAP* game_over_logo;
void endscreen_init();
void endscreen_deinit();

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
    al_init_ttf_addon();
    al_init_image_addon();

    must_init(al_init_ttf_addon(), "ttf addon");
    must_init(al_init_ttf_addon(), "image addon");

    HUD_logo = al_load_bitmap("ProjectLogo.png");
    dice_bitmap[0] = al_load_bitmap("dice 1.png");
    dice_bitmap[1] = al_load_bitmap("dice 2.png");
    dice_bitmap[2] = al_load_bitmap("dice 3.png");
    dice_bitmap[3] = al_load_bitmap("dice 4.png");
    dice_bitmap[4] = al_load_bitmap("dice 5.png");
    dice_bitmap[5] = al_load_bitmap("dice 6.png");
    small_font = al_load_ttf_font("Inter-SemiBold.ttf", 16, 0);
    big_font = al_load_ttf_font("Inter-SemiBold.ttf", 20, 0);



    must_init(HUD_logo, "HUD_logo");
    must_init(dice_bitmap[0], "dice 1");
    must_init(dice_bitmap[1], "dice 2");
    must_init(dice_bitmap[2], "dice 3");
    must_init(dice_bitmap[3], "dice 4");
    must_init(dice_bitmap[4], "dice 5");
    must_init(dice_bitmap[5], "dice 6");
    must_init(small_font, "small font");
    must_init(big_font, "big font");

}
void hud_deinit()
{
    al_destroy_bitmap(HUD_logo);
    al_destroy_bitmap(dice_bitmap[0]);
    al_destroy_bitmap(dice_bitmap[1]);
    al_destroy_bitmap(dice_bitmap[2]);
    al_destroy_bitmap(dice_bitmap[3]);
    al_destroy_bitmap(dice_bitmap[4]);
    al_destroy_bitmap(dice_bitmap[5]);
    al_destroy_font(small_font);
    al_destroy_font(big_font);
}


/// sprites
void sprites_init()
{
    //house and cat_stat init
    house = al_load_bitmap("house.png");
    must_init(house, "house");
    cat_bitmap[0] = al_load_bitmap("cat1.png");
    must_init(cat_bitmap[0], "cat1");
    cat_bitmap[1] = al_load_bitmap("cat2.png");
    must_init(cat_bitmap[1], "cat2");
    cat_bitmap[2] = al_load_bitmap("cat3.png");
    must_init(cat_bitmap[2], "cat3");
    cat_bitmap[3] = al_load_bitmap("cat4.png");
    must_init(cat_bitmap[3], "cat4");
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
    al_destroy_bitmap(cat_bitmap[0]);
    al_destroy_bitmap(cat_bitmap[1]);
    al_destroy_bitmap(cat_bitmap[2]);
    al_destroy_bitmap(cat_bitmap[3]);
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

void endscreen_init()
{
    game_over_logo = al_load_bitmap("GameOver.png");
    end_screen_font = al_load_ttf_font("Inter-SemiBold.ttf", 36, 0);
    must_init(game_over_logo, "Game Over Logo");
    must_init(end_screen_font, "End Screen Font");

}

void endscreen_deinit()
{
    al_destroy_bitmap(game_over_logo);
    al_destroy_font(end_screen_font);
}
