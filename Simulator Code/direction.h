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
#include "API.h"



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
            API::turnLeft();
            break;
        case east:
            currentDirection = north;
            API::turnLeft();
            break;
        case south:
            currentDirection = east;
            API::turnLeft();
            break;
        case west:
            currentDirection = south;
            API::turnLeft();
            break;
    }
}

// Function to turn the mouse right
void right() {
    // Update the current direction based on the current direction
    switch (currentDirection) {
        case north:
            currentDirection = east;
            API::turnRight();
            break;
        case east:
            currentDirection = south;
            API::turnRight();
            break;
        case south:
            currentDirection = west;
            API::turnRight();
            break;
        case west:
            currentDirection = north;
            API::turnRight();
            break;
    }
}

//Function to move the mouse forward
void forward(int& x, int& y) {
    switch(currentDirection){
        case north:
            API::moveForward();
            y++;
            break;
        case east:
            API::moveForward();
            x++;
            break;
        case south:
            API::moveForward();
            y--;
            break;
        case west:
            API::moveForward();
            x--;
            break;
    }

}
// void orientation(int i, int j){
//     if (i == 1){
//         switch(currentDirection){
//             case north:
//                 right();
//             case east:

//             case south:
//             case west:
//         }
//     }
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
