#pragma once

#include <raylib.h>
#include "constants.h"

void DrawOkDialogButton(Font* font) {
  Vector2 size = MeasureTextEx(*font, "OK", 40, 0);
  int btn_x = (WIDTH-size.x)/2, btn_y = HEIGHT-100;
  DrawRectangle(btn_x, btn_y, size.x+40, 60+20, WHITE);
  DrawTextEx(*font, "OK", (Vector2){btn_x+20, btn_y+20}, 40, 0, BLACK);
}

int IsOkDialogButtonClicked() {
  Vector2 size = MeasureTextEx(GetFontDefault(), "OK", 40, 0);
  Vector2 mouse_pos = GetMousePosition();
  int btn_x = (WIDTH-size.x)/2, btn_y = HEIGHT-100;
  int width = size.x+40, height = 60+20;
  if((mouse_pos.x >= btn_x && mouse_pos.x < (btn_x + width)) && (mouse_pos.y >= btn_y && mouse_pos.y < (btn_y + height))) {
    return 1;
  }
  
  return 0;
}
