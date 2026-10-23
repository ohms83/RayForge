#include <iostream>
#include "raylib.h"

int main() {
    InitWindow(800, 600, "RayForge");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}