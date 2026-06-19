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
  Texture2D play_btn {LoadTexture("assets/textures/buttons/play.png")};

  bool inGame {false};
  float x = (GetScreenWidth() / 2) - (bird.width / 2);
  float y = (GetScreenHeight() / 2) - (bird.height / 2);
  float velocity {0};
  const float GRAVITY {1.0};
  const float FLY_UP {-15.0};

  // Start of the whole game
  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(bg_img,  // background image
      (Rectangle) {0, 0, (float)bg_img.width, (float)bg_img.height},
      (Rectangle) {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
      (Vector2) {0, 0},
      0.0f, WHITE
    );

    float rotation = (velocity / 30.0f) * 90.0f; // Scale velocity to rotation (max 90 degrees)
    rotation = (rotation > 90.0f) ? 90.0f : (rotation < -90.0f) ? -90.0f : rotation; // Clamp rotation

    DrawTexturePro(bird, // bird character or the menu mascot
      (Rectangle) {0, 0, (float)bird.width, (float)bird.height},
      (Rectangle) {x, y, (float)bird.width, (float)bird.height},
      (Vector2) {(float)bird.width / 2, (float)bird.height / 2}, // Rotate around center
      rotation,
      WHITE
    );

    if (!inGame) { // Display Flappy bird home screen
      DrawTexturePro(title, // title with board
        (Rectangle) {0, 0, (float)title.width, (float)title.height},
        (Rectangle) {(float)(GetScreenWidth() / 2) - (title.width / 2), 0, (float)title.width, (float)title.height},
        (Vector2) {0, 0},
        0.0f,
        WHITE
      );


      float x = (GetScreenWidth() / 2) - (play_btn.width / 2); 
      float y = GetScreenHeight() - (play_btn.height * 2);

      // interactions with the mouse
      Rectangle bounds = {x, y, (float)play_btn.width, (float)play_btn.height};
      bool hover = CheckCollisionPointRec(GetMousePosition(), bounds);
      bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

      DrawTexturePro(play_btn, // Play button
        (Rectangle) {0, 0, (float)play_btn.width, (float)play_btn.height},
        (Rectangle) {(float)x, (float)y, (float)play_btn.width, (float)play_btn.height},
        (Vector2) {0, 0},
        0.0f,
        (hover ? GREEN : (IsKeyPressed(KEY_SPACE) ? GREEN : WHITE))
      );

      if (clicked || IsKeyPressed(KEY_SPACE)) inGame = true; 
    } else { // when playing or inGame is true
      if (IsKeyPressed(KEY_SPACE)) {
        velocity = FLY_UP;
      } else {
      }

      velocity += GRAVITY;
      y += velocity;
      
      if (y > GetScreenHeight() - bird.height) {
        y = GetScreenHeight() - bird.height;
      } else if (y <= 0) {
        y = 0;
      }
    }

    EndDrawing();
  }

  UnloadTexture(play_btn);
  UnloadTexture(bird);
  UnloadTexture(title);
  UnloadTexture(bg_img);
  CloseWindow();

  return 0;
}
