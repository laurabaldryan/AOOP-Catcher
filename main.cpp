#include "raylib.h"
#include "body.h"
#include <cmath>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "OOCatcher - Final Version");
    SetTargetFPS(60);

    body character(360, 440, 50);

    enum class BallState { Falling, Caught };
    BallState state = BallState::Falling;
    bool isPaused = false;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) isPaused = !isPaused;
        if (IsKeyPressed(KEY_ESCAPE)) break;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawLine(0, screenHeight - 50, screenWidth, screenHeight - 50, DARKGRAY);

        if (!isPaused && state == BallState::Falling) {
            character.animate_throw();
            if (character.can_grab(character.ball, 6.0)) {
                state = BallState::Caught;
            }
        }

        if (state == BallState::Caught) {
            character.animate_catch();
        }

        for (const auto& limb : character.get_limbs()) {
            DrawLine(
                static_cast<int>(limb->get_x()), screenHeight - static_cast<int>(limb->get_y()),
                static_cast<int>(limb->end_x()), screenHeight - static_cast<int>(limb->end_y()),
                BLACK
            );
        }

        for (const auto& finger : character.get_fingers()) {
            DrawLine(
                static_cast<int>(finger->get_x()), screenHeight - static_cast<int>(finger->get_y()),
                static_cast<int>(finger->end_x()), screenHeight - static_cast<int>(finger->end_y()),
                BLUE
            );
        }

        for (const auto& toe : character.get_toes()) {
            DrawLine(
                static_cast<int>(toe->get_x()), screenHeight - static_cast<int>(toe->get_y()),
                static_cast<int>(toe->end_x()), screenHeight - static_cast<int>(toe->end_y()),
                BROWN
            );
        }

        DrawCircle(
            static_cast<int>(character.get_head_center().get_x()),
            screenHeight - static_cast<int>(character.get_head_center().get_y()),
            8, DARKBLUE
        );

        DrawCircle(
            static_cast<int>(character.ball.get_x()),
            screenHeight - static_cast<int>(character.ball.get_y()),
            5, RED
        );

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
