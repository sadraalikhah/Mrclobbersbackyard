#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "GameOver.h"
#include "MainGame.h"
#include "MainMenu.h"



int start()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(1), "reserve samples");
    must_init(al_init_ttf_addon(), "ttf addon");
    must_init(al_init_ttf_addon(), "image addon");


    display_init();
    score_init();
    main_menu_init();
    hud_init();
    sprites_init();
    pause_init();
    endscreen_init();

    al_play_sample(Game_Score, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    start_menu();
    start_game();
    end_game();


    //destroy the created files
    display_deinit();
    score_deinit();
    main_menu_deinit();
    hud_deinit();
    sprites_deinit();
    pause_deinit();
    endscreen_deinit();


    return 0;
}

