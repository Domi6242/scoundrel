#ifndef SCOUNDREL_DRAW_H
#define SCOUNDREL_DRAW_H

#include "raylib.h"
#include "globals.h"

void draw_init();
void draw_card(Vector2 pos, Card card);
void draw_frame();

void draw_deinit();

#endif