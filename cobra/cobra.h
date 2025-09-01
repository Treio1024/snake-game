#include "raylib.h"
#include <stdint.h>

#ifndef COBRA_H
#define COBRA_H

struct Cobra {
  Vector2 pos;
  short int length;
  uint8_t direction;
  float walkTime;
  double timer;
  Vector2 *tails;
  Vector2 oldPos;
  uint8_t died;
};

extern struct Cobra *cobra;

extern void updateCobra(double dt);
extern void loadCobra(void);

#endif
