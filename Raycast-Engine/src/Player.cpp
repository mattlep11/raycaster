#include <set>
#include "./headers/Player.h"

void Player::Update(const Grid& grid, float vx, float vy, float av)
{
    UpdatePosition(vx, vy);
    UpdateRotation(av);

    // check collision with all tiles in chunks that the player may be in (+ - radius)
    float x{ pos.GetX() };
    float y{ pos.GetY() };

    // farthest extremes of the player that may be in different chunks
    float minX{ x - radius };
    float maxX{ x + radius };
    float minY{ y - radius };
    float maxY{ y + radius };

    // locations to check for
    std::vector<Vector2D> possibleChunks{};
    possibleChunks.push_back({ minX, y });
    possibleChunks.push_back({ maxX, y });
    possibleChunks.push_back({ x, maxY });
    possibleChunks.push_back({ x, minY });

    std::set<size_t> checked{};

    for (Vector2D loc : possibleChunks)
    {
        size_t chunk{ grid.VectorToChunk(loc) };

        // chunk doesn't exist
        if (chunk < 0 || chunk >= NB_CHUNKS)
            continue;

        // if the chunk is unchecked, add it to the checked list and check collision of every tile
        if (auto search{ checked.find(chunk) }; search == checked.end())
        {
            checked.insert(chunk);
            for (const Tile& tile : grid.GetChunks()[chunk])
            {
                Vector2D tileAsVector{ tile.ToVector() };
                if (CircToSquareIsColliding(pos, radius, tile.ToVector(), CELL_WIDTH))
                    ResolveCollision(tileAsVector);
            }
        }
    }
}

void Player::UpdateRotation(float av)
{
    dir = ApplyRotationMatrix(dir, av).ToNormalized();
}

void Player::UpdatePosition(float vx, float vy)
{
    pos.SetX(clamp<float>(pos.GetX() + vx, VIEW_START_X + radius, VIEW_END_X - radius));
    pos.SetY(clamp<float>(pos.GetY() + vy, VIEW_START_Y + radius, VIEW_END_Y - radius));
}

void Player::ResolveCollision(const Vector2D& wall)
{
    Vector2D closest{ CircToSquareClosestPoint(pos, wall, CELL_WIDTH) };
    float dist{ CircToSquareDist(pos, wall, CELL_WIDTH) };

    // normalize for the directions needed to offset
    float dx{ (pos.GetX() - closest.GetX()) / dist };
    float dy{ (pos.GetY() - closest.GetY()) / dist };

    float overlap{ radius - dist };

    pos.SetX(pos.GetX() + overlap * dx);
    pos.SetY(pos.GetY() + overlap * dy);
}