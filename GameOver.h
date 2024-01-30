#pragma once
#pragma warning(disable : 4996).
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "types.h"
#include "init.h"
#include "logics.h"

void draw_end_screen();
void sort_cats();
void save_file();
void draw_line(FILE* resultFile);

bool end_game()
{
	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE* endQueue = al_create_event_queue();
	must_init(endQueue, "endQueue");

	al_register_event_source(endQueue, al_get_keyboard_event_source());
	al_register_event_source(endQueue, al_get_display_event_source(display));

	sort_cats();
	save_file();

	endscreen_init;
		while (1)
		{
			draw_end_screen();
			al_wait_for_event(endQueue, &event);
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.type == ALLEGRO_EVENT_KEY_DOWN)
				break;
		}
		return true;
}

void draw_end_screen()
{
	///color pallete
	ALLEGRO_COLOR PrimaryC = al_map_rgb(192, 0, 6);

	al_draw_bitmap(game_over_screen, 0, 0, 0);
	al_draw_bitmap(cat_big[order[3]], 650, 430, 0);
	al_draw_bitmap(cat_big[order[2]], 650, 625, 0);
	al_draw_bitmap(cat_big[order[1]], 650, 820, 0);
	
	al_draw_textf(big_font, PrimaryC, 800, 450, 0, "cat %d", order[3] + 1);
	al_draw_textf(big_font, PrimaryC, 800, 645, 0, "cat %d", order[2] + 1);
	al_draw_textf(big_font, PrimaryC, 800, 840, 0,"cat %d", order[1] +1);

	al_draw_textf(big_font, PrimaryC, 1300, 450, 0, "%2d", cat_points[order[3]]);
	al_draw_textf(big_font, PrimaryC, 1300, 645, 0, "%2d", cat_points[order[2]]);
	al_draw_textf(big_font, PrimaryC, 1300, 840, 0, "%2d", cat_points[order[1]]);


	al_flip_display();
 }

void sort_cats()
{
	int i, j;
	for (i = 1; i < 4; i++) {
		int tmp = order[i];
		int tmp_points = cat_points[order[i]];
		j = i - 1;

		while (j >= 0 && cat_points[order[j]] > tmp_points) {
			order[j + 1] = order[j];
			j = j - 1;
		}
		order[j + 1] = tmp;
	}
}

void save_file()
{
	FILE* resultFile;
	resultFile = fopen("result.txt", "w");
	if (resultFile == NULL)
	{
		printf("can't open RESULT123.txt\n");
		exit(0);
	}

	//first row
	fprintf(resultFile, " rank |");
	fprintf(resultFile, " players |");
	fprintf(resultFile, " energy |");
	fprintf(resultFile, " power |");
	fprintf(resultFile, " score |");
	draw_line(resultFile);
	fprintf(resultFile, "  #1  |");
	fprintf(resultFile, "  cat %d  |", order[3] + 1);
	fprintf(resultFile, "  %3d   |", cat_stat[order[3]].defense);
	fprintf(resultFile, " %3d   |", cat_stat[order[3]].attack);
	fprintf(resultFile, " %3d   |", cat_points[order[3]]);
	draw_line(resultFile);
	fprintf(resultFile, "  #2  |");
	fprintf(resultFile, "  cat %d  |", order[2] + 1);
	fprintf(resultFile, "  %3d   |", cat_stat[order[2]].defense);
	fprintf(resultFile, " %3d   |", cat_stat[order[2]].attack);
	fprintf(resultFile, " %3d   |", cat_points[order[2]]);
	draw_line(resultFile);
	fprintf(resultFile, "  #3  |");
	fprintf(resultFile, "  cat %d  |", order[1] + 1);
	fprintf(resultFile, "  %3d   |", cat_stat[order[1]].defense);
	fprintf(resultFile, " %3d   |", cat_stat[order[1]].attack);
	fprintf(resultFile, " %3d   |", cat_points[order[1]]);
	draw_line(resultFile);
	fprintf(resultFile, "  #4  |");
	fprintf(resultFile, "  cat %d  |", order[0] + 1);
	fprintf(resultFile, "  %3d   |", cat_stat[order[0]].defense);
	fprintf(resultFile, " %3d   |", cat_stat[order[0]].attack);
	fprintf(resultFile, " %3d   |", cat_points[order[0]]);
	draw_line(resultFile);
	fclose(resultFile);
}

void draw_line(FILE* resultFile)
{
	fprintf(resultFile, "\n");
	for (int i = 0; i < 42; i++)
		fprintf(resultFile,"_");
	fprintf(resultFile, "\n");
}