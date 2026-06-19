#include <raylib.h>

int main() {
  const int MAX_WIDTH {1600};
  const int MAX_HEIGHT {720};

  InitWindow(MAX_WIDTH / 2, MAX_HEIGHT / 2, "Flappy Bird");
  SetTargetFPS(40);
  SetExitKey(KEY_NULL);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
