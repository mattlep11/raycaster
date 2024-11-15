#pragma once

#ifndef RAYCAST_COMMON_RESOURCES_H
#define RAYCAST_COMMON_RESOURCES_H

#include <iostream>
#include "./raylib.h"
#include "./Geometry.h"

#define INFOLOG(m) std::cout << "[INFOLOG]: " << m << '\n'
#define ERRLOG(e) std::cerr << "[ERR]: " << e << '\n'

/*
* NOTE: Changing the specifications will alter how the whole app looks as most of the calculations are done using these
* constants. Everything (in theory) branches off from the windows specs and the viewport's starting X value. Modifying
* anything else may result in skewing. Ideally, the grid should remain square, the chunks don't adapt to wrapping or
* gaps.
*
* For the map configuration, the cell-width must be chosen based on the desired number of cells that can fit equally
* within the grid's area. With the default specifications, some options include 25, 34, 50, and 85.
*/

// window specs
constexpr int TARGET_FPS{ 75 };
constexpr int WIN_HEIGHT{ 900 };
constexpr int WIN_WIDTH{ 1200 };

// scene specs
constexpr int VIEW_START_X{ 25 };
constexpr int VIEW_START_Y{ VIEW_START_X };
constexpr int VIEW_WIDTH{ (int)(WIN_WIDTH * 0.75) - 2 * VIEW_START_X };
constexpr int VIEW_HEIGHT{ VIEW_WIDTH };
constexpr int VIEW_END_X{ VIEW_WIDTH + VIEW_START_X };
constexpr int VIEW_END_Y{ VIEW_HEIGHT + VIEW_START_Y };

constexpr Rectangle VIEWPORT{ VIEW_START_X - 4, VIEW_START_Y - 4, VIEW_WIDTH + 8, VIEW_HEIGHT + 8 };
constexpr int MENU_START_X{ VIEW_START_X * 2 + VIEW_WIDTH };

// map config
constexpr int CELL_WIDTH{ 34 };
constexpr int CELL_WIDTH_IN_GRID{ CELL_WIDTH - 1 };
constexpr int NB_ROWS{ VIEW_HEIGHT / CELL_WIDTH };
constexpr int NB_COLS{ VIEW_WIDTH / CELL_WIDTH };

// ui config
constexpr int MENU_WIDTH{ WIN_WIDTH - 3 * VIEW_START_X - VIEW_WIDTH };
constexpr int MENU_HEIGHT{ VIEW_HEIGHT };
constexpr int SWAP_BTN_WIDTH{ MENU_WIDTH };
constexpr int SWAP_BTN_HEIGHT{ 100 };
constexpr int SWAP_BTN_START_X{ MENU_START_X };
constexpr int SWAP_BTN_START_Y{ VIEW_END_Y - SWAP_BTN_HEIGHT };

// player config
constexpr float PLR_SPEED{ 3.5f };
constexpr float PLR_R_SPEED{ 0.07f };
constexpr size_t NB_RAYS{ VIEW_WIDTH }; // MINIMUM = 2
constexpr float DIR_VEC_LENGTH{ 50.0f };
constexpr float VIEW_VEC_LENGTH{ DIR_VEC_LENGTH };


// helper functions
template <typename T>
inline T clamp(T val, T min, T max)
{
    if (val < min) return min;
    else if (val > max) return max;
    else return val;
}

#endif