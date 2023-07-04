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
