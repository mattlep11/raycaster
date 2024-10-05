#include <vector>
#include "./headers/Player.h"

Player::Player()
{
    // create all ray objects with null values
    for (size_t i{}; i < NB_RAYS; i++)
        rays[i] = { {0.0f, 0.0f}, {0.0f, 0.0f} };
}

void Player::Update(const Grid& grid, float vx, float vy, float av)
{
    UpdatePosition(vx, vy);
    UpdateRotation(av);
    UpdateRayOrientations();
    CheckCollisionStatus(grid);
}

void Player::UpdateRotation(float av)
{
    dir = ApplyRotationMatrix(dir, av).ToNormalized();

    // rotate the view point's frame of reference.
    viewPointL.SetX(pos.GetX() - viewLength * 0.5f * dir.GetX());
    viewPointL.SetY(pos.GetY() - viewLength * 0.5f * dir.GetY());

    dirPoint.SetX(pos.GetX() + dirLength * dir.GetX());
    dirPoint.SetY(pos.GetY() + dirLength * dir.GetY());

    // rotate the direction vector by 90 degrees to get the perpindicular camera plane
    Vector2D planeDir{ dir.ToPerpindicular() };
    float dx{ viewLength * planeDir.GetX() };
    float dy{ viewLength * planeDir.GetY() };
    float dirX{ dirPoint.GetX() };
    float dirY{ dirPoint.GetY() };

    viewPointL = { dirX + dx, dirY + dy };
    viewPointR = { dirX - dx, dirY - dy };
}

void Player::UpdatePosition(float vx, float vy)
{
    pos.SetX(clamp<float>(pos.GetX() + vx, VIEW_START_X + radius, VIEW_END_X - radius));
    pos.SetY(clamp<float>(pos.GetY() + vy, VIEW_START_Y + radius, VIEW_END_Y - radius));
}

void Player::CheckCollisionStatus(const Grid& grid)
{
    // check collision with all tiles in chunks that the player may be in (+ - radius)
    float x{ pos.GetX() };
    float y{ pos.GetY() };

    // farthest extremes of the player that may be in different chunks
    float minX{ x - radius };
    float maxX{ x + radius };
    float minY{ y - radius };
    float maxY{ y + radius };

    // locations to check for
    std::vector<Vector2D> possibleLocs{
        {minX, minY}, {minX, y}, {minX, maxY}, {maxX, minY},
        {maxX, y}, {maxX, maxY}, {x, minY}, {x, maxY}
    };

    for (Vector2D loc : possibleLocs)
    {
        GridCoord coord{ grid.VectorToCoord(loc) };
        if (grid.Get(coord.GetRow(), coord.GetCol()) != -1)
        {
            Vector2D tileAsVector{ coord.ToVector() };
            if (CircToSquareIsColliding(pos, radius, coord.ToVector(), CELL_WIDTH))
                ResolveCollision(tileAsVector);
        }
    }
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

void Player::UpdateRayOrientations()
{
    float da{ fov / (NB_RAYS - 1) };
    Vector2D start{ viewPointR - pos };
    for (size_t i{}; i < NB_RAYS; i++)
    {
        Vector2D rayDir{ ApplyRotationMatrix(start, i * da).ToNormalized() };
        rays[i].SetDir(rayDir);

        // summing 100.0f as a flat rate as a temporary placeholder before the DDA calculated the full length
        // TODO: remove 100.0f increment after DDA has been implemented
        rays[i].SetEndPos({ pos.GetX() + 100.0f * rayDir.GetX(), pos.GetY() + 100.0f * rayDir.GetY() });
    }
}