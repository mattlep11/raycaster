#pragma once

#ifndef RAYCAST_COMMON_RESOURCES_H
#define RAYCAST_COMMON_RESOURCES_H

#include <iostream>
#include "./raylib.h"

#define INFOLOG(m) std::cout << "[INFOLOG]: " << m
#define ERRLOG(e) std::cerr << "[ERR]: " << e

// window config
constexpr int TARGET_FPS{ 75 };
constexpr int WIN_HEIGHT{ 800 };
constexpr int WIN_WIDTH{ 1200 };

// scene config
constexpr int VIEW_START_X{ 25 };
constexpr int VIEW_START_Y{ VIEW_START_X };
constexpr int VIEW_WIDTH{ static_cast<int>(WIN_WIDTH * 0.75) - 2 * VIEW_START_X };
constexpr int VIEW_HEIGHT{ WIN_HEIGHT - 2 * VIEW_START_Y };
constexpr Rectangle VIEWPORT{ VIEW_START_X, VIEW_START_Y, VIEW_WIDTH, VIEW_HEIGHT };
constexpr int MENU_START_X{ VIEW_START_X * 2 + VIEW_WIDTH };


#endif