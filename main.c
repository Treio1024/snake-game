#include "globals.h"

#include "raylib.h"

#include "utils/utils.c"

#include "cobra/cobra.c"

Font defaultFont;
short int points = 0;

int main() {

  InitWindow(WIDTH, HEIGHT, "Snake Game");

  setSeed(time(NULL));

  defaultFont = LoadFont("assets/MedodicaRegular.otf");

  loadCobra();
  loadApple();

  char *pointsBuf = malloc(sizeof(char) * 8);

  while (!WindowShouldClose()) {
    double dt = GetFrameTime();

    updateCobra(dt);

    sprintf(pointsBuf, "%d", cobra->length);

    BeginDrawing();
    ClearBackground(BLACK);

    DrawRectangle(cobra->pos.x, cobra->pos.y, TILESIZE, TILESIZE, DARKGREEN);
    DrawRectangle(apple->x, apple->y, TILESIZE, TILESIZE, RED);

    for (int i = 0; i < cobra->length; i++) {
      DrawRectangle(cobra->tails[i].x, cobra->tails[i].y, TILESIZE, TILESIZE,
                    GREEN);
    }

    DrawTextEx(defaultFont, (const char *)pointsBuf,
               (Vector2){(float)WIDTH / 2 - 25, 0}, 100, 0, RAYWHITE);

    if (cobra->died) {
      DrawTextEx(defaultFont, "Died",
                 (Vector2){WIDTH / 2 - 50, HEIGHT / 2 - 50}, 100, 0, RAYWHITE);
    }

    EndDrawing();
  }

  free(pointsBuf);
  CloseWindow();

  return 0;
}
