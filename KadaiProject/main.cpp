#include "include/raylib/raylib.h"
#include <math.h>

typedef struct {
    Vector2 position;
    float radius;
    bool active;
    float respawnTimer;
} Enemy;

Enemy enemy = { { 0, 0 }, 25.0f, true, 0.0f };
Vector2 aimPos;

int main(void) {
    int monitor = GetCurrentMonitor();
    int sw = GetMonitorWidth(monitor);
    int sh = GetMonitorHeight(monitor);

    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(sw, sh, "Aimbot Sandbox");

    SetWindowPosition(0, 0);
    ClearWindowState(FLAG_WINDOW_TOPMOST);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    DisableCursor();

    aimPos.x = (float)screenWidth / 2;
    aimPos.y = (float)screenHeight / 2;

    float moveTimer = 0;
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        Vector2 mouseDelta = GetMouseDelta();
        aimPos.x += mouseDelta.x;
        aimPos.y += mouseDelta.y;

        if (enemy.active) {
            moveTimer += deltaTime;
            enemy.position.x = (screenWidth / 2) + cosf(moveTimer) * 300;
            enemy.position.y = (screenHeight / 2) + sinf(moveTimer) * 200;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointCircle(aimPos, enemy.position, enemy.radius)) {
                    enemy.active = false;
                    enemy.respawnTimer = 1.0f;
                }
            }
        }
        else {
            enemy.respawnTimer -= deltaTime;
            if (enemy.respawnTimer <= 0) {
                enemy.active = true;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (enemy.active) {
            DrawCircleV(enemy.position, enemy.radius, RED);
            DrawCircleLines(enemy.position.x, enemy.position.y, enemy.radius, MAROON);
        }
        else {
            DrawText("Eliminated", screenWidth / 2 - 100, screenHeight / 2, 20, YELLOW);
        }

        Color crosshairColor = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? WHITE : GREEN;
        DrawLine(aimPos.x - 12, aimPos.y, aimPos.x + 12, aimPos.y, crosshairColor);
        DrawLine(aimPos.x, aimPos.y - 12, aimPos.x, aimPos.y + 12, crosshairColor);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}