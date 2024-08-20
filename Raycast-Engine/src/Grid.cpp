#include "./headers/Grid.h"

void Grid::UpdateMouseCell()
{
    int mx{ GetMouseX() };
    int my{ GetMouseY() };

    if (clamp<int>(mx, VIEW_START_X, VIEW_END_X - 1) != mx || clamp<int>(my, VIEW_START_Y, VIEW_END_Y - 1) != my)
    {
        mouseCell.SetX(-1);
        mouseCell.SetY(-1);
    }
    else
    {
        mouseCell.SetX((mx - VIEW_START_X) / CELL_WIDTH);
        mouseCell.SetY((my - VIEW_START_Y) / CELL_WIDTH);
    }
}