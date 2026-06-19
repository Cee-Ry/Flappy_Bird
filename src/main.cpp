#include <raylib.h>

int main() {
  // my phone total pixel size (infinix)
  const int MAX_WIDTH {1600};
  const int MAX_HEIGHT {720};

  InitWindow(MAX_WIDTH / 2, MAX_HEIGHT / 2, "Flappy Bird");
  SetTargetFPS(40);
  SetExitKey(KEY_NULL); 

  Texture2D bg_img {LoadTexture("assets/textures/backgrounds/bg.png")};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(bg_img, 
      (Rectangle) {0, 0, (float)bg_img.width, (float)bg_img.height},
      (Rectangle) {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
      (Vector2) {0, 0},
      0.0f,
      WHITE
    );
    EndDrawing();
  }

  UnloadTexture(bg_img);
  CloseWindow();

  return 0;
}
