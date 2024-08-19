#include "./headers/Scene.h"

// constants for rendering the scene elements:
constexpr int MENU_WIDTH{ WIN_WIDTH - 3 * VIEW_START_X - VIEW_WIDTH };
constexpr int MENU_HEIGHT{ VIEW_HEIGHT };
/* SWAP BUTTON */
constexpr int SWAP_BTN_WIDTH{ MENU_WIDTH };
constexpr int SWAP_BTN_HEIGHT{ 100 };
constexpr int SWAP_BTN_START_X{ MENU_START_X };
constexpr int SWAP_BTN_START_Y{ VIEW_END_Y - SWAP_BTN_HEIGHT };
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

    while (!WindowShouldClose())
    {
        PollUpdates();

        BeginDrawing();

        ClearBackground(BLACK);

        DrawMapLines();
        DrawMouseCell();
        DrawSceneDetails();

        EndDrawing();
    }
}

void Scene::PollUpdates()
{
    tileGrid.UpdateMouseCell();
    PollForClicks();
    PollForKeyEvents();
}

void Scene::DrawSceneDetails() const
{
    const int fpsSize{ MeasureText("XX FPS", 10) };
    DrawFPS(MENU_START_X + MENU_WIDTH - fpsSize - VIEW_START_X, VIEW_START_Y);

    DrawRectangleLinesEx(VIEWPORT, 2, WHITE);
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
}

void Scene::DrawTileSelector() const
{
    Color rectColour{ DARKBLUE };
    const Vector2 qLeftSize{ MeasureTextEx(GetFontDefault(), "< Q", 30, 1.0f) };
    const Vector2 eRightSize{ MeasureTextEx(GetFontDefault(), "E >", 30, 1.0f) };
    const int headerSize{ MeasureText("Selected Tile:", 30) };
    if (true) // TODO: switch this to a switch and go thru the enum of available tiles
        rectColour = rectColour;

    DrawRectangleRoundedLines(
        { SELECTOR_START_X, SELECTOR_START_Y, SELECTOR_EDGE, SELECTOR_EDGE },
        0.2f, 1, 2.75f, WHITE
    );
    DrawRectangle(
        SELECTOR_START_X + SELECTOR_EDGE / 4, SELECTOR_START_Y + SELECTOR_EDGE / 4,
        CELL_WIDTH, CELL_WIDTH,
        rectColour
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

void Scene::DrawMapLines() const
{
    // horizontals
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

void Scene::DrawMouseCell() const
{
    int mx{ tileGrid.GetMouseCell().GetX() };
    int my{ tileGrid.GetMouseCell().GetY() };

    // -1 indicates a mouse position outside the grid
    if (mx == -1 || my == -1)
        return;
    DrawRectangleLines(mx * CELL_WIDTH + VIEW_START_X, my * CELL_WIDTH + VIEW_START_Y, CELL_WIDTH, CELL_WIDTH, YELLOW);
}