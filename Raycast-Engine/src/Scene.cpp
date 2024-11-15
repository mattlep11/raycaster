#include "./headers/Scene.h"

// helper function to make quick convertions into raylib vectors for drawing functions
static inline Vector2 AsRaylibVector(const Vector2D& v)
{
    return { v.GetX(), v.GetY() };
}

// constants for rendering the scene elements:
/* SWAP BUTTON */
constexpr int SWAP_BTN_MID_X{ SWAP_BTN_START_X + SWAP_BTN_WIDTH / 2 };
constexpr int SWAP_BTN_MID_Y{ SWAP_BTN_START_Y + SWAP_BTN_HEIGHT / 2 };
/* TILE SELECTOR */
constexpr int SELECTOR_EDGE{ 100 };
constexpr int SELECTOR_START_X{ MENU_START_X + (MENU_WIDTH - SELECTOR_EDGE) / 2 };
constexpr int SELECTOR_START_Y{ VIEW_START_Y + (MENU_HEIGHT - SELECTOR_EDGE) / 2 };

void Scene::Run()
{
    SetTargetFPS(TARGET_FPS);
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "RAYCASTER ENGINE o7");
    Player& plr{ tileGrid.GetPlayer() };

    while (!WindowShouldClose())
    {
        PollUpdates();

        BeginDrawing();

        ClearBackground(BLACK);

        if (!app.ShouldRender3D())
        {
            DrawGridLines();
            DrawPlayerViewRays(plr);
            DrawGridTiles();
            DrawMouseCell();
            DrawPlayer(plr);
        }
        else
            Draw3DWalls(plr);

        DrawSceneDetails();

        EndDrawing();
    }
}

void Scene::PollUpdates()
{
    app.HandleClickEvents(tileGrid);

    if (!app.ShouldRender3D())
    {
        tileGrid.UpdateMouseCell();
        app.HandleKeyEvents();
    }

    app.HandleMovementEvents(tileGrid, tileGrid.GetPlayer());

}

void Scene::DrawSceneDetails() const
{
    const int fpsSize{ MeasureText("XX FPS", 10) };
    DrawFPS(MENU_START_X + MENU_WIDTH - fpsSize - VIEW_START_X, VIEW_START_Y);

    (app.ShouldRender3D())
        ? DrawText("[CONTROLS] - WS: move | AD: strafe | L/R arrow keys: rotate | SWAP: Switch to 2D POV",
            VIEW_START_X, VIEW_START_Y / 3, 10, LIGHTGRAY)
        : DrawText("[CONTROLS] - WASD: move | L/R arrow keys: rotate | Q/E: cycle through tile types | M1/M2: place or remove tiles | SWAP: Switch to 3D POV",
            VIEW_START_X, VIEW_START_Y / 3, 10, LIGHTGRAY);

    DrawRectangleLinesEx(VIEWPORT, 4, WHITE);
    DrawSwapButton();
    DrawTileSelector();
}

void Scene::DrawSwapButton() const
{
    const Vector2 swapTxtSize{ MeasureTextEx(GetFontDefault(), "S W A P", 30.0f, 2.0f) };

    DrawRectangleRounded({ SWAP_BTN_START_X, SWAP_BTN_START_Y, SWAP_BTN_WIDTH, SWAP_BTN_HEIGHT }, 0.2f, 1, GREEN);
    DrawRectangleRoundedLines(
        { SWAP_BTN_START_X + 5, SWAP_BTN_START_Y + 5, SWAP_BTN_WIDTH - 10, SWAP_BTN_HEIGHT - 10 },
        0.2f, 1, 2.75f, WHITE
    );
    DrawText("S W A P",
        SWAP_BTN_MID_X - (int)(swapTxtSize.x * 0.5f),
        SWAP_BTN_MID_Y - (int)(swapTxtSize.y * 0.5f),
        30, WHITE
    );

    // swap the cursor for feedback
    int mx{ GetMouseX() };
    int my{ GetMouseY() };
    if (clamp<int>(mx, SWAP_BTN_START_X, SWAP_BTN_START_X + SWAP_BTN_WIDTH) == mx
        && clamp<int>(my, SWAP_BTN_START_Y, SWAP_BTN_START_Y + SWAP_BTN_HEIGHT) == my)
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void Scene::DrawTileSelector() const
{
    const Vector2 qLeftSize{ MeasureTextEx(GetFontDefault(), "< Q", 30, 1.0f) };
    const Vector2 eRightSize{ MeasureTextEx(GetFontDefault(), "E >", 30, 1.0f) };
    const int headerSize{ MeasureText("Selected Tile:", 30) };

    DrawRectangleRoundedLines(
        { SELECTOR_START_X, SELECTOR_START_Y, SELECTOR_EDGE, SELECTOR_EDGE },
        0.2f, 1, 2.75f, WHITE
    );
    DrawRectangle(
        SELECTOR_START_X + SELECTOR_EDGE / 4, SELECTOR_START_Y + SELECTOR_EDGE / 4,
        50, 50,
        app.ShouldRender3D() ? app.GetColour(-1, false) : app.GetColour(app.GetSelectedTile(), false)
    );
    DrawText("Selected Tile:", SELECTOR_START_X + (SELECTOR_EDGE - headerSize) / 2, SELECTOR_START_Y - 50, 30, WHITE);
    DrawText("< Q",
        SELECTOR_START_X - 2 * (int)qLeftSize.x, SELECTOR_START_Y + (int)(SELECTOR_EDGE - qLeftSize.y) / 2,
        30, WHITE
    );
    DrawText("E >",
        SELECTOR_START_X + SELECTOR_EDGE + (int)eRightSize.x, SELECTOR_START_Y + (int)(SELECTOR_EDGE - eRightSize.y) / 2,
        30, WHITE
    );
}

void Scene::DrawGridLines() const
{
    const int endX{ VIEW_START_X + VIEW_WIDTH };
    for (int i{ 1 }; i < NB_ROWS; i++)
    {
        int horizontal{ VIEW_START_Y + i * CELL_WIDTH };
        DrawLine(VIEW_START_X, horizontal, endX, horizontal, DARKGRAY);
    }

    // verticals
    const int endY{ VIEW_START_Y + VIEW_HEIGHT };
    for (int i{ 1 }; i < NB_COLS; i++)
    {
        int vertical{ VIEW_START_X + i * CELL_WIDTH };
        DrawLine(vertical, VIEW_START_Y, vertical, endY, DARKGRAY);
    }
}

void Scene::DrawGridTiles() const
{
    for (int i{}; i < NB_ROWS; i++)
        for (int j{}; j < NB_COLS; j++)
            if (tileGrid.Get(i, j) != -1)
                DrawRectangle(
                    VIEW_START_X + i * CELL_WIDTH, VIEW_START_Y + j * CELL_WIDTH,
                    CELL_WIDTH_IN_GRID, CELL_WIDTH_IN_GRID, app.GetColour(tileGrid.Get(i, j), false)
                );
}

void Scene::DrawPlayer(const Player& player) const
{
    DrawCircleV(AsRaylibVector(player.GetPos()), player.GetRadius(), GREEN);
}

void Scene::DrawPlayerViewRays(const Player& player) const
{
    Vector2 start{ AsRaylibVector(player.GetPos()) };
    const Ray2D* rays{ player.GetRays() };
    for (size_t i{}; i < NB_RAYS; i++)
        DrawLineEx(start, AsRaylibVector(rays[i].GetEndPos()), 2.0f, RED);
}

void Scene::Draw3DWalls(const Player& player) const
{
    const Ray2D* rays{ player.GetRays() };
    int pixel{ VIEW_START_X };
    Ray2D currentRay{};
    for (int i{}; i < VIEW_WIDTH; i++)
    {
        pixel++;
        currentRay = rays[i];

        DrawLine(pixel, currentRay.GetWallStart3D(), pixel, currentRay.GetWallEnd3D(),
            app.GetColour(currentRay.GetCollidedWallType(), currentRay.HasCollidedNS()));
    }
}

void Scene::DrawMouseCell() const
{
    int mx{ tileGrid.GetMouseCell().GetRow() };
    int my{ tileGrid.GetMouseCell().GetCol() };

    // -1 indicates a mouse position outside the grid
    if (mx == -1 || my == -1)
        return;
    DrawRectangleLines(mx * CELL_WIDTH + VIEW_START_X, my * CELL_WIDTH + VIEW_START_Y, CELL_WIDTH, CELL_WIDTH, YELLOW);
}