/*
Created by: Alex Whitfield
Date: 28/06/23

Global variable file
All these values are know before the competition, its good practise to put these in its own file to declutter the main file
*/

#pragma once
#include <iostream>

// Creates a blank grid
const int grid_size = 16;
int grid[grid_size][grid_size];
bool visited[grid_size][grid_size]; // Set a true or false grid to track visited nodes

int goal[2] = {8,7};
int start[2]= {0,0};

//////
bool goGoal = true;         // If false it means its reached the goal
//////

// This is only used at the start to floodfill the maze
// Set all values in the grid to -1
void initialiseGrid() {
    // Initialize the main grid and visited grid
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            visited[i][j] = false;
            grid[i][j] = -1;
        }
    }
}
////////////////////////////////

// Is change this grid to hold horizontal and vertical walls in 2 different grids

// Then in floodfill and manhattan when there is a wall, we need to update the 2 grids

// Then when we floodfill we should use info from the 2 grids + a new grid that hold the values we have used so far, so 
//this function should only be called once at the start.


/*
// This part can be simplified as we are updating the cell wall info above 
                // Check if conditions are met
                if (neighbourX >= 0 && neighbourX < grid_size && neighbourY >= 0 && neighbourY < grid_size && grid[neighbourX][neighbourY] < grid[currentX][currentY]){
                    // if wall in front or left or right recalculate
                    if (i == 1 || i == -1){
                        if (isWallLeft || isWallRight){
                            log("Wall blocking shorest path, recalculating...");
                            initialiseGrid();
                            // recalculate as shortest is going left of right
                            //floodFill(currentX, currentY); // old version
                            floodFill(goal[0], goal[1]);
                        }else{
                            if (i == 1){
                                log("Right");
                                right(); // update the robot direction
                                API::turnRight(); // Robot turns right
                            }else{
                                log("Left");
                                left(); // update the robot direction
                                API::turnLeft(); // Robot turns left
                            }
                            currentX = neighbourX;
                            currentY = neighbourY;
                        }
                    }else{
                        if (isWallFront){
                            // recalculate
                            log("Wall in front, recalculating...");
                            initialiseGrid();
                            floodFill(goal[0], goal[1]);
                        }else{
                            if (j == 1){
                                log("Forward");
                                API::moveForward(); // Robot moves forward
                            }
                            currentX = neighbourX;
                            currentY = neighbourY;
                        }
                    }
                    break;
                }
*/