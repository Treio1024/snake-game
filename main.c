#include <stdio.h>

#include "globals.h"
#include "raylib.h"

#include "cobra/cobra.c"
#include "utils/utils.c"

Font defaultFont;

int main() {

  InitWindow(WIDTH, HEIGHT, "Snake Game");

  setSeed(time(NULL));

  // sets the default font
  defaultFont = LoadFont("assets/MedodicaRegular.otf");

  loadCobra();

  /*
   * Set the key to leave the program.
   * It's already esc but I decided to keep it explicit.
   */
  SetExitKey(KEY_ESCAPE);

  // creates a string buffer for the points
  char *pointsBuf = malloc(sizeof(char) * 8);

  while (!WindowShouldClose()) {
    double dt = GetFrameTime(); // get the time between one frame and another

    updateCobra(dt);

    // update the buffer
    sprintf(pointsBuf, "%d", cobra->length);

    BeginDrawing();
    ClearBackground(BLACK);

    // draws the snake tail
    for (int i = 0; i < cobra->length; i++) {
      DrawRectangle(cobra->tails[i].pos.x, cobra->tails[i].pos.y, TILESIZE,
                    TILESIZE, cobra->tails[i].color);
    }

    // draws the snake and the apple
    DrawRectangle(cobra->pos.x, cobra->pos.y, TILESIZE, TILESIZE, DARKGREEN);
    DrawRectangle(apple->x, apple->y, TILESIZE, TILESIZE, RED);

    // draws the points
    DrawTextEx(defaultFont, (const char *)pointsBuf,
               (Vector2){(float)WIDTH / 2 - 25, 0}, 100, 0, RAYWHITE);

    // draws if the player died
    if (cobra->died) {
      DrawTextEx(defaultFont, "Died",
                 (Vector2){WIDTH / 2 - 50, HEIGHT / 2 - 50}, 100, 0, RAYWHITE);
    }

    EndDrawing();
  }

  free(pointsBuf);
  free(cobra);
  free(apple);
  CloseWindow();

  return 0;
}
