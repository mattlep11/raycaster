#include <algorithm>
#include "./headers/Grid.h"

Grid::Grid(Player& player)
    :
    player(player)
{
    int totalCells{ NB_COLS * NB_ROWS };
    int cellsPerChunk{ totalCells / NB_CHUNKS };

    chunkWidth = (size_t)sqrt(cellsPerChunk);
    chunkHeight = (size_t)sqrt(cellsPerChunk);

    while (chunkWidth * chunkHeight * NB_CHUNKS < totalCells)
    {
        chunkWidth++;
        chunkHeight++;
    }

    chunksPerRow = NB_COLS / chunkWidth;
}

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

void Grid::PlaceTile(TileType type)
{
    size_t chunk{ CellToChunk(mouseCell) };

    for (const Tile& tile : chunks[chunk])
        if (mouseCell == tile)
            return;

    if (!CircToSquareIsColliding(player.GetPos(), player.GetRadius(), mouseCell.ToVector(), CELL_WIDTH))
    {
        chunks[chunk].push_back({ mouseCell, type }); // append a copy of the tile to the chunk's list
        INFOLOG("New tile built at: C" << chunk << "[" << mouseCell.GetX() << ", " << mouseCell.GetY() << "]");
    }
}

void Grid::RemoveTile()
{
    size_t chunk{ CellToChunk(mouseCell) };
    for (const Tile& tile : chunks[chunk])
        if (mouseCell == tile)
        {
            // swap the tile to delete to the back of the vector to pop it
            std::vector<Tile>& tileList{ chunks[chunk] };
            auto iter{ std::find(tileList.begin(), tileList.end(), tile) };
            std::iter_swap(iter, tileList.end() - 1);
            tileList.pop_back();

            INFOLOG("Destroyed tile at: C" << chunk << "[" << mouseCell.GetX() << ", " << mouseCell.GetY() << "]");
            break;
        }
};

size_t Grid::CellToChunk(const Tile& coord) const
{
    return coord.GetX() / chunkWidth + coord.GetY() / chunkHeight * chunksPerRow;
}

size_t Grid::VectorToChunk(const Vector2D& vec) const
{
    return static_cast<int>((vec.GetX() - VIEW_START_X) / CELL_WIDTH) / chunkWidth
        + static_cast<int>((vec.GetY() - VIEW_START_Y) / CELL_WIDTH) / chunkHeight * chunksPerRow;
}