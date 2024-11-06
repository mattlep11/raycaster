#include <vector>
#include "./headers/Player.h"

Player::Player()
{
    // create all ray objects with null values
    for (size_t i{}; i < NB_RAYS; i++)
        rays[i] = { {0.0f, 0.0f}, {0.0f, 0.0f} };
}

void Player::Update(const Grid& grid, float v, float vAlt, float av, bool in3D)
{
    UpdatePosition(v, vAlt, in3D);
    UpdateRotation(av);
    UpdateRayOrientations();
    CheckCollisionStatus(grid);

    for (Ray2D& ray : rays)
        Raycast(grid, ray, in3D);
}

void Player::UpdateRotation(float av)
{
    dir = ApplyRotationMatrix(dir, av).ToNormalized();
}

void Player::UpdatePosition(float v, float vAlt, bool strafe)
{
    float vx{};
    float vy{};

    // strafe movement for 3D
    if (strafe)
    {
        Vector2D perpDir{ dir.ToPerpindicular() };
        vx = v * dir.GetX() + vAlt * perpDir.GetX();
        vy = v * dir.GetY() + vAlt * perpDir.GetY();
    }
    // cardinal movement for 2D
    else
    {
        vx = vAlt;
        vy = v;
    }

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
    Vector2D perp{ dir.ToPerpindicular() };
    float perpX{ perp.GetX() };
    float perpY{ perp.GetY() };
    for (size_t i{}; i < NB_RAYS; i++)
    {
        // interpolates the angle across the x axis
        float camX{ 2 * i / static_cast<float>(VIEW_WIDTH) - 1 };
        float dirX{ dir.GetX() + perpX * camX };
        float dirY{ dir.GetY() + perpY * camX };

        rays[i].SetDir(Vector2D(dirX, dirY).ToNormalized());
    }
}

void Player::Raycast(const Grid& grid, Ray2D& ray, bool in3D)
{
    // origin & direction variables normalized to the grid coordinates (removes the grid padding)
    float px{ pos.GetX() - VIEW_START_X };
    float py{ pos.GetY() - VIEW_START_Y };
    float dirX{ ray.GetDir().GetX() };
    float dirY{ ray.GetDir().GetY() };

    // scaling factor used to represent the scale of exactly one step in the x or y direction
    float dx{ sqrt(1 + (dirY * dirY) / (dirX * dirX)) * CELL_WIDTH };
    float dy{ sqrt(1 + (dirX * dirX) / (dirY * dirY)) * CELL_WIDTH };

    // the current cell coordinates of the ray over the course of the algorithm
    int cellX{ static_cast<int>(px / CELL_WIDTH) };
    int cellY{ static_cast<int>(py / CELL_WIDTH) };

    // the step factor used to adjust the cell count after each iteration
    int stepX{ (dirX < 0) ? -1 : 1 };
    int stepY{ (dirY < 0) ? -1 : 1 };

    // the cumulative distance of the ray on the x and y axes, set to the initial distance to the nearest gridline
    float lengthX{ (dirX < 0)
        ? px - static_cast<float>(cellX * CELL_WIDTH)
        : static_cast<float>((cellX + 1) * CELL_WIDTH) - px
    };
    lengthX /= fabs(dirX);
    float lengthY{ (dirY < 0)
        ? py - static_cast<float>(cellY * CELL_WIDTH)
        : static_cast<float>((cellY + 1) * CELL_WIDTH) - py
    };
    lengthY /= fabs(dirY);

    bool collided{ false };
    bool collidedNS{ false };
    while (!collided)
    {
        if (lengthX < lengthY)
        {
            cellX += stepX;
            collidedNS = false;

            // check that bounds have not been exceeded or tiles have not been collided with
            if (cellX != clamp(cellX, 0, NB_ROWS - 1) || grid.Get(cellX, cellY) != -1)
                collided = true;

            lengthX += dx;
        }
        else
        {
            cellY += stepY;
            collidedNS = true;

            // check that bounds have not been exceeded or tiles have not been collided with
            if (cellY != clamp(cellY, 0, NB_COLS - 1) || grid.Get(cellX, cellY) != -1)
                collided = true;

            lengthY += dy;
        }
    }

    // step back in one direction (since DDA goes one step passed collision)
    float shortestLength{ (collidedNS) ? lengthY - dy : lengthX - dx };

    if (in3D)
    {
        // multiple by the difference in player to ray angle to correct the fisheye effect
        shortestLength *= cos((dir - ray.GetDir()).Magnitude());
        int lineHeight{ static_cast<int>(CELL_WIDTH / 2 * VIEW_WIDTH / shortestLength) };

        int wallStart{ VIEW_HEIGHT / 2 - lineHeight / 2 };
        if (wallStart < 0)
            wallStart = 0;
        int wallEnd{ VIEW_HEIGHT / 2 + lineHeight / 2 };
        if (wallEnd >= VIEW_HEIGHT)
            wallEnd = VIEW_HEIGHT;

        // offsetting both values by the grid padding to make it fill the full screen
        ray.SetWallStart3D(wallStart + VIEW_START_Y);
        ray.SetWallEnd3D(wallEnd + VIEW_START_Y);
        ray.SetCollidedNS(collidedNS);
        ray.SetCollidedWallType(grid.Get(cellX, cellY));
    }
    else
    {
        float endX = px + shortestLength * dirX + VIEW_START_X;
        float endY = py + shortestLength * dirY + VIEW_START_Y;
        ray.SetEndPos({ endX, endY });
    }

}