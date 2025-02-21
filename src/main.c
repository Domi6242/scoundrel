#include "math.h"
#include "raylib.h"
#include "globals.h"
#include "draw.h"
#include "game.h"

/**
 * tileset:
 *      by IvoryRed on itch.io
 *      https://ivoryred.itch.io/pixel-poker-cards
 */

int main() {
    // init
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GAME_SCREEN_W, GAME_SCREEN_H, "scoundrel");
    SetTargetFPS(60);
    draw_init();

    RenderTexture2D canvas = LoadRenderTexture(GAME_SCREEN_W, GAME_SCREEN_H);

    init_game();

    while (!WindowShouldClose()) {
        // Fullscreen logic
        if (IsKeyPressed(KEY_F11)) {
            if (IsWindowFullscreen()) {
                ToggleFullscreen();
                SetWindowSize(GAME_SCREEN_W, GAME_SCREEN_H);
            } else {
                SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                ToggleFullscreen();
            }
        }

        /***************************************************************************************************************
         *
         * Logic
         *
         **************************************************************************************************************/

        if(IsKeyPressed(KEY_SPACE)) {
            // deck_shuffle();
            room_run();
            room_draw();
        }

        /***************************************************************************************************************
         *
         * Drawing
         *
         **************************************************************************************************************/
        BeginDrawing();
        BeginTextureMode(canvas);

        draw_frame();

        EndTextureMode();

        /***************************************************************************************************************
         *
         * Letterbox
         *
         **************************************************************************************************************/
        ClearBackground(BLACK);
        float render_scale =
            fmin(GetScreenHeight() / (float)canvas.texture.height, GetScreenWidth() / (float)canvas.texture.width);
        Rectangle render_rect;
        render_rect.width = canvas.texture.width * render_scale;
        render_rect.height = canvas.texture.height * render_scale;
        render_rect.x = (GetScreenWidth() - render_rect.width) / 2.0f;
        render_rect.y = (GetScreenHeight() - render_rect.height) / 2.0f;
        DrawTexturePro(canvas.texture, (Rectangle){0, 0, (float)canvas.texture.width, (float)-canvas.texture.height},
                       render_rect, (Vector2){0, 0}, 0, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}