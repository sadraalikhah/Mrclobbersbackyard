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
	//color pallete
	ALLEGRO_COLOR bgc = al_map_rgb(151, 38, 38);
	ALLEGRO_COLOR gold = al_map_rgb(255, 184, 0);
	ALLEGRO_COLOR silver = al_map_rgb(202, 202, 202);
	ALLEGRO_COLOR bronze = al_map_rgb(237, 118, 51);

	al_draw_filled_rectangle(0, 0, 1600, 900, bgc);
	al_draw_bitmap(game_over_logo, 116, -44, 0);

	//first place
	al_draw_filled_circle(300, 478, 58, gold);
	al_draw_filled_rectangle(300, 420, 1240, 536, gold);
	al_draw_filled_circle(1240, 478, 58, gold);

	al_draw_scaled_bitmap(cat_bitmap[order[3]], 0, 0, 50, 50, 290, 445, 70, 70, 0);
	al_draw_textf(big_font, al_map_rgb_f(1,1,1), 1100, 455,0, "%3d points", cat_points[order[3]]);
	al_draw_textf(big_font, al_map_rgb_f(1, 1, 1), 400, 455, 0, "cat %d", order[3]+1);

	//second
	al_draw_filled_circle(300, 628, 58, silver);
	al_draw_filled_rectangle(300, 570, 1240, 686, silver);
	al_draw_filled_circle(1240, 628, 58, silver);

	al_draw_scaled_bitmap(cat_bitmap[order[2]], 0, 0, 50, 50, 290, 595, 70, 70, 0);
	al_draw_textf(big_font, al_map_rgb_f(1, 1, 1), 1100, 605, 0, "%3d points", cat_points[order[2]]);
	al_draw_textf(big_font, al_map_rgb_f(1, 1, 1), 400, 605, 0, "cat %d", order[2] + 1);

	//third
	al_draw_filled_circle(300, 778, 58, bronze);
	al_draw_filled_rectangle(300, 720, 1240, 836, bronze);
	al_draw_filled_circle(1240, 778, 58, bronze);

	al_draw_scaled_bitmap(cat_bitmap[order[1]], 0, 0, 50, 50, 290, 745, 70, 70, 0);
	al_draw_textf(big_font, al_map_rgb_f(1, 1, 1), 1100, 755, 0, "%3d points", cat_points[order[1]]);
	al_draw_textf(big_font, al_map_rgb_f(1, 1, 1), 400, 755, 0, "cat %d", order[1] + 1);

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
	fprintf(resultFile, "   1  |");
	fprintf(resultFile, "  cat %d  |", order[3] + 1);
	fprintf(resultFile, "  %3d   |", cat_stat[order[3]].defense);
	fprintf(resultFile, " %3d   |", cat_stat[order[3]].attack);
	fprintf(resultFile, " %3d   |", cat_points[order[3]]);
	draw_line(resultFile);
	fprintf(resultFile, "   2  |");
	fprintf(resultFile, "  cat %d  |", order[2] + 1);
	fprintf(resultFile, "  %3d   |", cat_stat[order[2]].defense);
	fprintf(resultFile, " %3d   |", cat_stat[order[2]].attack);
	fprintf(resultFile, " %3d   |", cat_points[order[2]]);
	draw_line(resultFile);
	fprintf(resultFile, "   3  |");
	fprintf(resultFile, "  cat %d  |", order[1] + 1);
	fprintf(resultFile, "  %3d   |", cat_stat[order[1]].defense);
	fprintf(resultFile, " %3d   |", cat_stat[order[1]].attack);
	fprintf(resultFile, " %3d   |", cat_points[order[1]]);
	draw_line(resultFile);
	fprintf(resultFile, "   3  |");
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