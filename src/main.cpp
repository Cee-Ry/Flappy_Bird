#include <ctime>
#include <raylib.h>

int main() {
  // Source screen size and resize factor for a smaller desktop window.
  const int MAX_WIDTH {1600};
  const int MAX_HEIGHT {720};
  const float RESIZE {0.30f};
  const int screenWidth {MAX_WIDTH - (int)(MAX_WIDTH * RESIZE)};
  const int screenHeight {MAX_HEIGHT - (int)(MAX_HEIGHT * RESIZE)};

  InitWindow(screenWidth, screenHeight, "Flappy Bird");
  SetTargetFPS(60);
  SetExitKey(KEY_NULL);

  Texture2D bg_img {LoadTexture("assets/textures/backgrounds/bg.png")};
  Texture2D title {LoadTexture("assets/textures/title/title_board.png")};
  Texture2D bird {LoadTexture("assets/textures/player/bird.png")};
  Texture2D play_btn {LoadTexture("assets/textures/buttons/play.png")};
  Texture2D pipe {LoadTexture("assets/textures/obstacle/pipe.png")};

  enum GamePhase { MENU, PLAYING, GAME_OVER };
  GamePhase phase {MENU};

  const float birdX {screenWidth * 0.25f};
  float birdY {(screenHeight * 0.5f) - (bird.height * 0.5f)};
  float velocity {0.0f};

  const float GRAVITY {0.5f};
  const float FLY_UP {-10.0f};
  const float PIPE_SPEED {3.0f};
  const float PIPE_GAP {180.0f};
  const int GAP_MIN {80};
  const int GAP_MAX {screenHeight - 80 - (int)PIPE_GAP};

  float pipeX {(float)screenWidth};
  float pipeGapY {(float)GetRandomValue(GAP_MIN, GAP_MAX)};
  bool pipePassed {false};

  int score {0};
  int bestScore {0};

  SetRandomSeed((unsigned int)time(NULL));

  auto resetGame = [&]() {
    birdY = (screenHeight * 0.5f) - (bird.height * 0.5f);
    velocity = 0.0f;
    pipeX = (float)screenWidth;
    pipeGapY = (float)GetRandomValue(GAP_MIN, GAP_MAX);
    score = 0;
    pipePassed = false;
  };

  while (!WindowShouldClose()) {
    bool hasFlapped = IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (phase == PLAYING) {
      // Bird physics and controls.
      if (hasFlapped) {
        velocity = FLY_UP;
      }
      velocity += GRAVITY;
      birdY += velocity;

      // Pipe movement and recycling.
      pipeX -= PIPE_SPEED;
      if (pipeX + pipe.width < 0) {
        pipeX = (float)screenWidth;
        pipeGapY = (float)GetRandomValue(GAP_MIN, GAP_MAX);
        pipePassed = false;
      }

      // Score once when the bird passes the pipe.
      if (!pipePassed && pipeX + pipe.width < birdX) {
        score += 1;
        pipePassed = true;
      }

      // Collision detection.
      Rectangle birdRect {
        birdX + 10,
        birdY + 8,
        bird.width - 20,
        bird.height - 16
      };
      Rectangle topPipeRect {
        pipeX,
        0,
        (float)pipe.width,
        pipeGapY
      };
      Rectangle bottomPipeRect {
        pipeX,
        pipeGapY + PIPE_GAP,
        (float)pipe.width,
        (float)screenHeight - (pipeGapY + PIPE_GAP)
      };

      if (CheckCollisionRecs(birdRect, topPipeRect) ||
          CheckCollisionRecs(birdRect, bottomPipeRect) ||
          birdY <= 0 ||
          birdY + bird.height >= screenHeight) {
        phase = GAME_OVER;
        bestScore = (score > bestScore) ? score : bestScore;
      }
    }

    if (phase != PLAYING && hasFlapped) {
      // Start or restart the game from the menu/game-over screen.
      resetGame();
      phase = PLAYING;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexturePro(bg_img,
      (Rectangle){0, 0, (float)bg_img.width, (float)bg_img.height},
      (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
      (Vector2){0, 0},
      0.0f,
      WHITE);

    // Draw bottom pipe.
    DrawTexturePro(pipe,
      (Rectangle){0, 0, (float)pipe.width, (float)pipe.height},
      (Rectangle){pipeX, pipeGapY + PIPE_GAP, (float)pipe.width, (float)pipe.height},
      (Vector2){0, 0},
      0.0f,
      WHITE);

    // Draw top pipe flipped vertically.
    DrawTexturePro(pipe,
      (Rectangle){0, 0, (float)pipe.width, -(float)pipe.height},
      (Rectangle){pipeX, pipeGapY - pipe.height, (float)pipe.width, (float)pipe.height},
      (Vector2){0, 0},
      0.0f,
      WHITE);

    float birdRotation = velocity * 3.0f;
    if (birdRotation > 45.0f) birdRotation = 45.0f;
    if (birdRotation < -45.0f) birdRotation = -45.0f;

    DrawTexturePro(bird,
      (Rectangle){0, 0, (float)bird.width, (float)bird.height},
      (Rectangle){birdX, birdY, (float)bird.width, (float)bird.height},
      (Vector2){bird.width * 0.5f, bird.height * 0.5f},
      birdRotation,
      WHITE);

    if (phase == MENU) {
      // Title and play button in the main menu.
      DrawTexturePro(title,
        (Rectangle){0, 0, (float)title.width, (float)title.height},
        (Rectangle){(screenWidth / 2.0f) - (title.width / 2.0f), 20.0f, (float)title.width, (float)title.height},
        (Vector2){0, 0},
        0.0f,
        WHITE);

      float btnX = (screenWidth / 2.0f) - (play_btn.width / 2.0f);
      float btnY = screenHeight - (play_btn.height * 2.0f);
      Rectangle btnBounds {btnX, btnY, (float)play_btn.width, (float)play_btn.height};
      bool hover = CheckCollisionPointRec(GetMousePosition(), btnBounds);

      DrawTexturePro(play_btn,
        (Rectangle){0, 0, (float)play_btn.width, (float)play_btn.height},
        (Rectangle){btnX, btnY, (float)play_btn.width, (float)play_btn.height},
        (Vector2){0, 0},
        0.0f,
        hover ? GREEN : WHITE);

      DrawText("Press SPACE or click to start", 10, screenHeight - 40, 18, BLACK);
    }
    else if (phase == PLAYING) {
      DrawText(TextFormat("Score: %i", score), 10, 10, 24, BLACK);
      DrawText("Press SPACE or click to flap", 10, screenHeight - 30, 18, DARKGRAY);
    }
    else { // GAME_OVER
      DrawText("Game Over", screenWidth / 2 - 120, screenHeight / 2 - 80, 40, RED);
      DrawText(TextFormat("Score: %i", score), screenWidth / 2 - 80, screenHeight / 2 - 20, 24, BLACK);
      DrawText(TextFormat("Best: %i", bestScore), screenWidth / 2 - 80, screenHeight / 2 + 20, 24, BLACK);
      DrawText("Press SPACE or click to restart", screenWidth / 2 - 190, screenHeight / 2 + 70, 20, DARKGRAY);
    }

    EndDrawing();
  }

  UnloadTexture(pipe);
  UnloadTexture(play_btn);
  UnloadTexture(bird);
  UnloadTexture(title);
  UnloadTexture(bg_img);
  CloseWindow();

  return 0;
}
