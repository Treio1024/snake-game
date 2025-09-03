#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "../globals.h"
#include "cobra.h"
#include "raylib.h"

// initialize the snake and apple has globals
struct Cobra *cobra = NULL;
Vector2 *apple = NULL;

void reloadApplePos();

// load both has dynamic memory pointers
void loadCobra() {
  cobra = malloc(sizeof(*cobra));
  *cobra = (struct Cobra){{10 * TILESIZE, 7 * TILESIZE}, 0, 2, 0.15, 0};

  cobra->tails =
      malloc(sizeof(*cobra->tails) * (WIDTH / TILESIZE) * (HEIGHT / TILESIZE));

  // initialize applth a random position
  apple = malloc(sizeof *apple);
  *apple =
      (Vector2){GetRandomValue(0, (WIDTH - TILESIZE) / TILESIZE) * TILESIZE,
                GetRandomValue(0, (HEIGHT - TILESIZE) / TILESIZE) * TILESIZE};
}

void updateCobra(double dt) {

  if (cobra->died) {
    return;
  }

  // 0 = left, 1 = up, 2 = right, 3 = down
  if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) &&
      cobra->direction != 0) {
    cobra->direction = 2;
    cobra->timer = cobra->walkTime;

  } else if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) &&
             cobra->direction != 2) {
    cobra->direction = 0;
    cobra->timer = cobra->walkTime;

  } else if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) &&
             cobra->direction != 3) {
    cobra->direction = 1;
    cobra->timer = cobra->walkTime;

  } else if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) &&
             cobra->direction != 1) {
    cobra->direction = 3;
    cobra->timer = cobra->walkTime;
  }

  /*
   * movement switch
   * if the walktime has passed then, the snake moves 1 unit.
   */

  cobra->timer += dt;
  if (cobra->timer >= cobra->walkTime) {
    cobra->timer = 0;
    cobra->oldPos = cobra->pos;

    // moves the snake depending of the direction
    switch (cobra->direction) {
    case 0:
      cobra->pos.x -= TILESIZE;
      break;
    case 1:
      cobra->pos.y -= TILESIZE;
      break;
    case 2:
      cobra->pos.x += TILESIZE;
      break;
    case 3:
      cobra->pos.y += TILESIZE;
      break;
    }

    // manage the tail of the snake and if a apple has been eaten
    Vector2 oldPos = cobra->oldPos;
    Vector2 nextPos = cobra->oldPos;

    if (apple->x == cobra->pos.x && apple->y == cobra->pos.y) {
      reloadApplePos();

      cobra->tails[cobra->length].pos = nextPos;

      cobra->length++;

      uint8_t colorValue = 255;

      if (cobra->length) {
        colorValue = (uint8_t)255 / cobra->length;
      }
      for (int i = 0; i < cobra->length; i++) {
        if (colorValue * (i + 1) > 64) {
          cobra->tails[i].color = (Color){0, colorValue * (i + 1), 0, 255};
        } else {
          cobra->tails[i].color = (Color){0, 64, 0, 255};
        }
      }
    }

    for (int i = 0; i < cobra->length; i++) {
      oldPos = cobra->tails[i].pos;

      cobra->tails[i].pos = nextPos;

      nextPos = oldPos;
    }
  }

  // managing apple position
  for (int i = 0; i < cobra->length; i++) {
    Vector2 pos = cobra->tails[i].pos;

    if (apple->x == pos.x && apple->y == pos.y) {
      reloadApplePos();
    }

    if (cobra->pos.x == pos.x && cobra->pos.y == pos.y) {
      cobra->died = 1;
    }
  }

  // managing borders
  if (cobra->pos.x < 0) {
    cobra->pos.x = WIDTH - TILESIZE;
  } else if (cobra->pos.x > WIDTH - TILESIZE) {
    cobra->pos.x = 0;
  }

  if (cobra->pos.y < 0) {
    cobra->pos.y = HEIGHT - TILESIZE;
  } else if (cobra->pos.y > HEIGHT - TILESIZE) {
    cobra->pos.y = 0;
  }
}

void reloadApplePos() {
  apple->x = GetRandomValue(0, (WIDTH - TILESIZE) / TILESIZE) * TILESIZE;
  apple->y = GetRandomValue(0, (HEIGHT - TILESIZE) / TILESIZE) * TILESIZE;
}
