#pragma once

#ifndef RAYCAST_COMMON_RESOURCES_H
#define RAYCAST_COMMON_RESOURCES_H

#include <iostream>
#include "./raylib.h"

#define INFOLOG(m) std::cout << "[INFOLOG]: " << m << '\n'
#define ERRLOG(e) std::cerr << "[ERR]: " << e << '\n'

// window config
constexpr int TARGET_FPS{ 75 };
constexpr int WIN_HEIGHT{ 800 };
constexpr int WIN_WIDTH{ 1200 };

// scene config
constexpr int VIEW_START_X{ 25 };
constexpr int VIEW_START_Y{ VIEW_START_X };
constexpr int VIEW_WIDTH{ static_cast<int>(WIN_WIDTH * 0.75) - 2 * VIEW_START_X };
constexpr int VIEW_HEIGHT{ WIN_HEIGHT - 2 * VIEW_START_Y };
constexpr int VIEW_END_X{ VIEW_WIDTH + VIEW_START_X };
constexpr int VIEW_END_Y{ VIEW_HEIGHT + VIEW_START_Y };

constexpr Rectangle VIEWPORT{ VIEW_START_X, VIEW_START_Y, VIEW_WIDTH, VIEW_HEIGHT };
constexpr int MENU_START_X{ VIEW_START_X * 2 + VIEW_WIDTH };

// map config
constexpr int CELL_WIDTH{ 50 };
constexpr int NB_ROWS{ VIEW_HEIGHT / CELL_WIDTH };
constexpr int NB_COLS{ VIEW_WIDTH / CELL_WIDTH };

// helper functions
template <typename T>
inline T clamp(T val, T min, T max)
{
    if (val < min) return min;
    else if (val > max) return max;
    else return val;
}

#endif