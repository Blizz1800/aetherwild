#include "Vector2.hpp"

Game::Vector2 Game::Vector2::operator+(Vector2 v)
{
    Vector2 r = Vector2(x, y);
    r.x += v.x;
    r.y += v.y;
    return r;
}

Game::Vector2 Game::Vector2::operator-(Vector2 v)
{
    Vector2 r = Vector2(x, y);
    r.x -= v.x;
    r.y -= v.y;
    return r;
}
