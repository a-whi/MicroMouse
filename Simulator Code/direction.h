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

// Function to move the mouse forward
void forward(int currentX, int currentY) {
    int deltaX = 0;
    int deltaY = 0;

    // Update the coordinates based on the current direction
    switch (currentDirection) {
        case north:
            deltaY = -1;
            break;
        case east:
            deltaX = 1;
            break;
        case south:
            deltaY = 1;
            break;
        case west:
            deltaX = -1;
            break;
    }

    // Update the mouse's position by adding the deltas to the current position
    int newX = currentX + deltaX;
    int newY = currentY + deltaY;

    // // Check if the new position is within bounds and there is no wall
    // if (newX >= 0 && newX < grid_size && newY >= 0 && newY < grid_size && !wall[newX][newY]) {
    //     currentX = newX;
    //     currentY = newY;
    // }
}