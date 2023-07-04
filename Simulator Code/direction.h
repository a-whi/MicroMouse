/*
Created by: Alex Whitfield
Date: 2/07/23

Direction for the mouse orientation
*/

//////////////////////////////////////
// IDK if i need this like left is always left and front is always front 
//////////////////////////////////////

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
// void forward(int currentX, int currentY) {
//     int deltaX = 0;
//     int deltaY = 0;

//     // Update the coordinates based on the current direction
//     switch (currentDirection) {
//         case north:
//             deltaY = -1;
//             break;
//         case east:
//             deltaX = 1;
//             break;
//         case south:
//             deltaY = 1;
//             break;
//         case west:
//             deltaX = -1;
//             break;
//     }

//     // Update the mouse's position by adding the deltas to the current position
//     int newX = currentX + deltaX;
//     int newY = currentY + deltaY;

//     // // Check if the new position is within bounds and there is no wall
//     // if (newX >= 0 && newX < grid_size && newY >= 0 && newY < grid_size && !wall[newX][newY]) {
//     //     currentX = newX;
//     //     currentY = newY;
//     // }
// }

// I will make a grid where each cell has this struct, it will basically say where the walls are in each coorditate
struct wall_detection{
    bool north;
    bool east;
    bool south;
    bool west;
};


wall_detection wallGrid[grid_size][grid_size];  // Create the wall detection grid

// This is how each cell is updated based off the mouse direction
void updateWallGrid(bool isWallFront, bool isWallLeft, bool isWallRight, int currentX, int currentY) {

    // Update the wall positions based on the current direction
    switch (currentDirection) {
        case north:
            // Update the wallGrid based on the current direction
            wallGrid[currentX][currentY].north = isWallFront;
            wallGrid[currentX][currentY].west = isWallLeft;
            wallGrid[currentX][currentY].east = isWallRight;
            break;
        case east:
            wallGrid[currentX][currentY].north = isWallLeft;
            wallGrid[currentX][currentY].east = isWallFront;
            wallGrid[currentX][currentY].south = isWallRight;
            break;
        case south:
            wallGrid[currentX][currentY].east = isWallLeft;
            wallGrid[currentX][currentY].south = isWallFront;
            wallGrid[currentX][currentY].west = isWallRight;
            break;
        case west:
            wallGrid[currentX][currentY].north = isWallRight;
            wallGrid[currentX][currentY].south = isWallLeft;
            wallGrid[currentX][currentY].west = isWallFront;
            break;
    }
}
