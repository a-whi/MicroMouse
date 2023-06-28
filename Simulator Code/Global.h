/*
Created by: Alex Whitfield
Date: 28/06/23

Global variable file
All these values are know before the competition, its good practise to put these in its own file to declutter the main file
*/

#pragma once
#include <iostream>

// Creates a blank grid
const int grid_size = 8;
int grid[grid_size][grid_size];
bool visited[grid_size][grid_size]; // Set a true or false grid to track visited nodes

int goal[2] = {5,5};
int start[2]= {0,0};
//////
bool goGoal = true;         // If false it means its reached the goal
//////

/////////////////////// Dont think this is needed as API uses different functios
// Set all values in the grid to -1
void initialiseGrid() {
    // Initialize the main grid and visited grid
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            visited[i][j] = false;
        }
    }
}
////////////////////////////////

void printMaze() {
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}