/*
Created by: Alex Whitfield
Date: 2/07/23

Direction for the mouse orientation
*/

#pragma once
#include <iostream>
#include "Global.h"

enum direction{
    north,
    east,
    south,
    west
};

// Change this so that currentdirection can be changed in Global.h.
direction currentDirection = north; //Set the current direction for the start of the maze

// Function to turn the mouse left
void left() {
    // Update the current direction based on the current direction
    switch (currentDirection) {
        case north:
            currentDirection = west;
            break;
        case east:
            currentDirection = north;
            break;
        case south:
            currentDirection = east;
            break;
        case west:
            currentDirection = south;
            break;
    }
}

// Function to turn the mouse right
void right() {
    // Update the current direction based on the current direction
    switch (currentDirection) {
        case north:
            currentDirection = east;
            break;
        case east:
            currentDirection = south;
            break;
        case south:
            currentDirection = west;
            break;
        case west:
            currentDirection = north;
            break;
    }
}