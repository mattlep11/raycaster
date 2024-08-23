#include "./headers/Player.h"

void Player::Update(float vx, float vy, float av)
{
    UpdatePosition(vx, vy);
    UpdateRotation(av);
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