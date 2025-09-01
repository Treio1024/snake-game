#include "../globals.h"
#include "raylib.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utils/utils.h"
#include "apple.h"
#include "cobra.h"

struct Cobra *cobra = NULL;
Vector2 *apple = NULL;

void loadCobra() {
  cobra = malloc(sizeof(*cobra));
  *cobra = (struct Cobra){{10 * TILESIZE, 7 * TILESIZE}, 0, 2, 0.20, 0};

  cobra->tails = malloc(sizeof(*cobra->tails) * WIDTH / TILESIZE);
}

void loadApple() {
  apple = malloc(sizeof *apple);
  *apple = (Vector2){randomNumber(0, WIDTH / TILESIZE) * TILESIZE,
                     randomNumber(0, HEIGHT / TILESIZE) * TILESIZE};
}

void updateCobra(double dt) {

  if (cobra->died) {
    return;
  }

  // 0 = left, 1 = up, 2 = right, 3 = down
  if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) &&
      cobra->direction != 0) {
    cobra->direction = 2;

  } else if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) &&
             cobra->direction != 2) {
    cobra->direction = 0;

  } else if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) &&
             cobra->direction != 3) {
    cobra->direction = 1;

  } else if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) &&
             cobra->direction != 1) {
    cobra->direction = 3;
  }

  // movement switch
  cobra->timer += dt;
  if (cobra->timer >= cobra->walkTime) {
    cobra->timer = 0;
    cobra->oldPos = cobra->pos;

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

    Vector2 oldPos = cobra->oldPos;
    Vector2 nextPos = cobra->oldPos;

    if (apple->x == cobra->pos.x && apple->y == cobra->pos.y) {
      *apple = (Vector2){randomNumber(0, WIDTH / TILESIZE) * TILESIZE,
                         randomNumber(0, HEIGHT / TILESIZE) * TILESIZE};

      cobra->tails[cobra->length] = nextPos;

      cobra->length++;
    }

    for (int i = 0; i < cobra->length; i++) {
      oldPos = cobra->tails[i];

      cobra->tails[i] = nextPos;

      nextPos = oldPos;
    }
  }

  // managing apple pos
  for (int i = 0; i < cobra->length; i++) {
    Vector2 pos = cobra->tails[i];

    if (apple->x == pos.x && apple->y == pos.y) {
      *apple = (Vector2){randomNumber(0, WIDTH / TILESIZE) * TILESIZE,
                         randomNumber(0, HEIGHT / TILESIZE) * TILESIZE};
    }

    if (cobra->pos.x == pos.x && cobra->pos.y == pos.y) {
      cobra->died = 1;
    }
  }

  if (apple->x == cobra->pos.x && apple->y == cobra->pos.y) {
    *apple = (Vector2){randomNumber(0, WIDTH / TILESIZE) * TILESIZE,
                       randomNumber(0, HEIGHT / TILESIZE) * TILESIZE};
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
