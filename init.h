#pragma once
#include "allegro.h"

ALLEGRO_BITMAP* house;
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

void sprites_init()
{
    //house and cats init
    house = al_load_bitmap("house.png");
    must_init(house, "house");
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