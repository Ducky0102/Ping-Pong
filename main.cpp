#include <raylib.h>

int cpu = 0, player = 0;

struct Ball {
  float x, y;
  int speed_x, speed_y;
  float r;

  void Update() {
    x += speed_x;
    y += speed_y;

    if (x + r <= 0) {
      cpu++;
      Reset();
    }
    if (x + r >= GetScreenWidth()) {
      player++;
      Reset();
    }
    if (y + r >= GetScreenHeight() || y + r <= 0) {
      speed_y *= -1;
    }
  }
  void Reset() {
    x = (float)1500 / 2;
    y = (float)900 / 2;

    int Speed_choices[2] = {-1, 1};
    speed_x *= Speed_choices[GetRandomValue(0, 1)];
    speed_y *= Speed_choices[GetRandomValue(0, 1)];
  }
  void Draw() { DrawCircle(x, y, r, WHITE); }

} b;

struct Paddle {
  int x, y;
  int speed_y;
  void UpdateP() {
    if (IsKeyDown(KEY_S) && y + 150 <= GetScreenHeight()) {
      y += speed_y;
    }
    if (IsKeyDown(KEY_W) && y >= 0) {
      y -= speed_y;
    }
  }

  void Draw() { DrawRectangle(x, y, 30, 150, WHITE); }
} p, c;

void UpdateC(int ball_y, int ball_x, float app) {
  if (ball_x > 800) {
    if (c.y + app > ball_y && c.y >= 0) {
      c.y = c.y - c.speed_y;
    }
    if (c.y + app < ball_y && c.y + 150 <= GetScreenHeight()) {
      c.y = c.y + c.speed_y;
    }
  }
}

int main() {
  float Toff = 75;
  // int cx = 955, cy = 375;  // computers pad
  int sx = 1500, sy = 900; // screen res
  InitWindow(sx, sy, "Ping Pong");
  SetTargetFPS(60);

  Color bgcolour = {158, 0, 161, 255};
  Color circle = {251, 0, 255, 100};

  b.x = (float)sx / 2;
  b.y = (float)sy / 2;
  b.r = 20;
  b.speed_x = 8;
  b.speed_y = 9;

  p.y = GetScreenHeight() / 2 - (75);
  p.x = 15;
  p.speed_y = 8;

  c.y = GetScreenHeight() / 2 - (75);
  c.x = 1500 - 30 - 15;
  c.speed_y = 9;
  while (WindowShouldClose() == false) {

    if (CheckCollisionCircleRec(Vector2{b.x, b.y}, b.r,
                                Rectangle{(float)p.x, (float)p.y, 30, 150})) {
      b.speed_x *= -1;
      Toff = GetRandomValue(-55, 55);
    }
    if (CheckCollisionCircleRec(Vector2{b.x, b.y}, b.r,
                                Rectangle{(float)c.x, (float)c.y, 30, 150})) {
      b.speed_x *= -1;
    }

    b.Update();
    p.UpdateP();
    UpdateC(b.y, b.x, Toff);
    BeginDrawing();
    ClearBackground(bgcolour);
    p.Draw();
    c.Draw();
    DrawCircle(sx / 2, sy / 2, 200, circle);
    DrawLine(sx / 2, 0, sx / 2, sy, WHITE);
    b.Draw();
    DrawText(TextFormat("%d", cpu), 1500 - (1500 / 4), 30, 60, WHITE);
    DrawText(TextFormat("%d", player), 1500 / 4, 30, 60, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
