#pragma once
#include <raylib.h>

class Game {
Private:
  bool over {false};

Public:
  int bird_X {GetScreenWidth() / 2};
  int bird_Y {GetScreenHeight() / 2};

};
