#include "./headers/Grid.h"

Grid::Grid(Player& player)
    :
    player(player)
{
    for (int i{}; i < NB_ROWS; i++)
        for (int j{}; j < NB_COLS; j++)
            grid[i][j] = -1;
}

int Grid::Get(int row, int col) const
{
    if (row != clamp<int>(row, 0, NB_ROWS - 1) || col != clamp<int>(col, 0, NB_COLS - 1))
        return -1;

    return grid[row][col];
}

void Grid::UpdateMouseCell()
{
    int mx{ GetMouseX() };
    int my{ GetMouseY() };

    if (clamp<int>(mx, VIEW_START_X, VIEW_END_X - 1) != mx || clamp<int>(my, VIEW_START_Y, VIEW_END_Y - 1) != my)
    {
        mouseCell.SetRow(-1);
        mouseCell.SetCol(-1);
    }
    else
    {
        mouseCell.SetRow((mx - VIEW_START_X) / CELL_WIDTH);
        mouseCell.SetCol((my - VIEW_START_Y) / CELL_WIDTH);
    }
}

void Grid::PlaceTile(int type)
{
    int& cell{ grid[mouseCell.GetRow()][mouseCell.GetCol()] };

    // short circuit to swap out the colour if a wall it already built to avoid the collision calculation
    if (cell != -1)
    {
        cell = type;
        return;
    }

    if (!CircToSquareIsColliding(player.GetPos(), player.GetRadius(), mouseCell.ToVector(), CELL_WIDTH))
    {
        cell = type;
        INFOLOG("New tile built at: [" << mouseCell.GetRow() << ", " << mouseCell.GetCol() << "]");
    }
}

void Grid::RemoveTile()
{
    int& cell{ grid[mouseCell.GetRow()][mouseCell.GetCol()] };

    if (cell != -1)
    {
        cell = -1;
        INFOLOG("Destroyed tile at: [" << mouseCell.GetRow() << ", " << mouseCell.GetCol() << "]");
    }
};

GridCoord Grid::VectorToCoord(const Vector2D& v) const
{
    return {
        (static_cast<int>(v.GetX()) - VIEW_START_X) / CELL_WIDTH,
        (static_cast<int>(v.GetY()) - VIEW_START_Y) / CELL_WIDTH
    };
}
