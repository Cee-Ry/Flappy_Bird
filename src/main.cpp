#include <raylib.h>

int main() {
  // my phone total pixel size (infinix)
  const int MAX_WIDTH {1600};
  const int MAX_HEIGHT {720};
  const float RESIZE {0.30}; // reducing window size by 30% percent, to fit it in my 1366x768 monitor

  InitWindow(MAX_WIDTH - (MAX_WIDTH * RESIZE), MAX_HEIGHT - (MAX_HEIGHT * RESIZE), "Flappy Bird");
  SetTargetFPS(40);
  SetExitKey(KEY_NULL); 

  Texture2D bg_img {LoadTexture("assets/textures/backgrounds/bg.png")};
  Texture2D title {LoadTexture("assets/textures/title/title_board.png")};
  Texture2D bird {LoadTexture("assets/textures/player/bird.png")};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(bg_img,  // background image
      (Rectangle) {0, 0, (float)bg_img.width, (float)bg_img.height},
      (Rectangle) {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
      (Vector2) {0, 0},
      0.0f,
      WHITE
    );

    DrawTexturePro(title, // title with board
      (Rectangle) {0, 0, (float)title.width, (float)title.height},
      (Rectangle) {(float)(GetScreenWidth() / 2) - (title.width / 2), 0, (float)title.width, (float)title.height},
      (Vector2) {0, 0},
      0.0f,
      WHITE
    );

    DrawTexturePro(bird, // bird character or the menu mascot
      (Rectangle) {0, 0, (float)bird.width, (float)bird.height},
      (Rectangle) {(float)(GetScreenWidth() / 2) - (bird.width / 2), (float)(GetScreenHeight() / 2) - (bird.height / 2), (float)bird.width, (float)bird.height},
      (Vector2) {0, 0},
      20.0f,
      WHITE
    );

    EndDrawing();
  }

  UnloadTexture(bird);
  UnloadTexture(title);
  UnloadTexture(bg_img);
  CloseWindow();

  return 0;
}
