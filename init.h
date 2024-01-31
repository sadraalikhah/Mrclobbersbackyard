#pragma once

///display
ALLEGRO_DISPLAY* display;
ALLEGRO_BITMAP* game_icon;

void display_init();
void display_deinit();

///main menu
ALLEGRO_BITMAP* main_menu_background;
ALLEGRO_BITMAP* big_pill[2];
void main_menu_init();
void main_menu_deinit();

///hud
ALLEGRO_BITMAP* HUD_BG;
ALLEGRO_BITMAP* HUD_logo;
ALLEGRO_BITMAP* short_pill;
ALLEGRO_BITMAP* pill[4]; //0:active, 1:active_cur, 2:freeze, 3:freeze_cur
ALLEGRO_BITMAP* dice_bitmap[6];
ALLEGRO_BITMAP* shield;
ALLEGRO_BITMAP* sword;
ALLEGRO_BITMAP* ice;
ALLEGRO_FONT* small_font;
ALLEGRO_FONT* medium_font;
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
ALLEGRO_BITMAP* _candy;
ALLEGRO_BITMAP* _fish;
void sprites_init();
void sprites_deinit();

///Pause Menu
ALLEGRO_BITMAP* pause_background;
ALLEGRO_BITMAP* guide;
ALLEGRO_BITMAP* confirmation;
void pause_init();
void pause_deinit();

///end_screen
ALLEGRO_BITMAP* game_over_screen;
ALLEGRO_BITMAP* cat_big[4];
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
    al_init_image_addon();
    must_init(al_init_ttf_addon(), "image addon");

    int display_width;
    int display_height;

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_set_new_display_flags(ALLEGRO_NOFRAME);
    ALLEGRO_MONITOR_INFO info;
    int i = 0;
    do {
        al_get_monitor_info(i++, &info);
    } while (!(info.x1 == 0 && info.y1 == 0));
    display_width = info.x2 - info.x1;
    display_height = info.y2 - info.y1;

    if (!(display = al_create_display(display_width, display_height))) {
        return false;
    }
    must_init(display, "display");
    game_icon = al_load_bitmap("GameIcon.png");
    must_init(game_icon, "Game Icon");

    al_set_display_icon(display, game_icon);
    al_set_window_title(display, "Mr Clobber's Backyard");
}
void display_deinit()
{
    al_destroy_display(display);
    al_destroy_bitmap(game_icon);
}

///main menu
void main_menu_init()
{
    main_menu_background = al_load_bitmap("MainMenuBackground.png");
    big_pill[0] = al_load_bitmap("BigPill.png");
    big_pill[1] = al_load_bitmap("BigPillCurrent.png");
    must_init(main_menu_background, "MainMenuBackground");
    must_init(big_pill[0], "BigPill");
    must_init(big_pill[1], "BigPillCurrent");
}

void main_menu_deinit()
{
    al_destroy_bitmap(main_menu_background);
    al_destroy_bitmap(big_pill[0]);
    al_destroy_bitmap(big_pill[1]);
}


/// hud
void hud_init()
{
    al_init_ttf_addon();

    must_init(al_init_ttf_addon(), "ttf addon");

    HUD_BG = al_load_bitmap("ScoreBoard.png");
    HUD_logo = al_load_bitmap("ProjectLogo.png");
    short_pill = al_load_bitmap("shortPill.png");
    pill[0] = al_load_bitmap("pill.png");
    pill[1] = al_load_bitmap("pill_cur.png");
    pill[2] = al_load_bitmap("pill_frozen.png");
    pill[3] = al_load_bitmap("pill_frozen_cur.png");
    dice_bitmap[0] = al_load_bitmap("dice1.png");
    dice_bitmap[1] = al_load_bitmap("dice2.png");
    dice_bitmap[2] = al_load_bitmap("dice3.png");
    dice_bitmap[3] = al_load_bitmap("dice4.png");
    dice_bitmap[4] = al_load_bitmap("dice5.png");
    dice_bitmap[5] = al_load_bitmap("dice6.png");
    shield = al_load_bitmap("shield.png");
    sword = al_load_bitmap("sword.png");
    ice = al_load_bitmap("ice.png");
    small_font = al_load_ttf_font("Inter-Bold.ttf", 30, 0);
    medium_font = al_load_ttf_font("Inter-Bold.ttf", 36, 0);
    big_font = al_load_ttf_font("Inter-Bold.ttf", 60, 0);


    must_init(HUD_logo, "HUD_BG");
    must_init(HUD_logo, "HUD_logo");
    must_init(short_pill, "Short Pill");
    must_init(pill[0], "Pill");
    must_init(pill[1], "Pill_cur");
    must_init(pill[2], "Pill_frozen");
    must_init(pill[3], "Pill_frozen_cur");
    must_init(dice_bitmap[0], "dice 1");
    must_init(dice_bitmap[1], "dice 2");
    must_init(dice_bitmap[2], "dice 3");
    must_init(dice_bitmap[3], "dice 4");
    must_init(dice_bitmap[4], "dice 5");
    must_init(dice_bitmap[5], "dice 6");
    must_init(small_font, "small font");
    must_init(medium_font, "medium font");
    must_init(big_font, "big font");

}
void hud_deinit()
{
    al_destroy_bitmap(HUD_BG);
    al_destroy_bitmap(HUD_logo);
    al_destroy_bitmap(short_pill);
    al_destroy_bitmap(pill[0]);
    al_destroy_bitmap(pill[1]);
    al_destroy_bitmap(pill[2]);
    al_destroy_bitmap(pill[3]);
    al_destroy_bitmap(dice_bitmap[0]);
    al_destroy_bitmap(dice_bitmap[1]);
    al_destroy_bitmap(dice_bitmap[2]);
    al_destroy_bitmap(dice_bitmap[3]);
    al_destroy_bitmap(dice_bitmap[4]);
    al_destroy_bitmap(dice_bitmap[5]);
    al_destroy_font(small_font);
    al_destroy_font(medium_font);
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
    _candy = al_load_bitmap("candy.png");
    must_init(_candy, "candy");
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
    al_destroy_bitmap(_candy);

}

void pause_init()
{
    pause_background = al_load_bitmap("PauseScreen.png");
    confirmation = al_load_bitmap("AreYouSure.png");
    guide = al_load_bitmap("GuideScreen.png");

    must_init(pause_background, "PauseScreen");
    must_init(guide, "AreYouSure");
    must_init(confirmation, "GuideScreen");
}

void pause_deinit()
{
    al_destroy_bitmap(pause_background);
    al_destroy_bitmap(guide);
    al_destroy_bitmap(confirmation);
}

void endscreen_init()
{
    game_over_screen = al_load_bitmap("GameOver.png");
    must_init(game_over_screen, "Game Over Screen");
    cat_big[0] = al_load_bitmap("cat1_big.png");
    cat_big[1] = al_load_bitmap("cat2_big.png");
    cat_big[2] = al_load_bitmap("cat3_big.png");
    cat_big[3] = al_load_bitmap("cat4_big.png");
    must_init(cat_big[0], "Cat 1 Big");
    must_init(cat_big[1], "Cat 2 Big");
    must_init(cat_big[2], "Cat 3 Big");
    must_init(cat_big[3], "Cat 4 Big");

}

void endscreen_deinit()
{
    al_destroy_bitmap(game_over_screen);
    al_destroy_bitmap(cat_big[0]);
    al_destroy_bitmap(cat_big[1]);
    al_destroy_bitmap(cat_big[2]);
    al_destroy_bitmap(cat_big[3]);
}
