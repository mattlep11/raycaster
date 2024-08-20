#pragma once

#ifndef RAYCAST_CONTROLLER_H
#define RAYCAST_CONTROLLER_H

#include "./Shared.h"
#include "./Grid.h"

class Controller
{

public:
    // listens for clicks and delegates the click event to the relevant component
    void PollForClicks();
    // listens for key presses and delegates the key event to the relevant component
    void PollForKeyEvents();
};

#endif