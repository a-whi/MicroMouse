/*
Created by: Alex Whitfield
Date: 28/06/23

This is my mouse code for the simulator to test my code. I'm using an API, so functions will have different names
This is not the actual mouse file
*/

#include "API.h"
#include "Global.h"
#include "Floodfill.h"

#include <iostream>
#include <string>


void log(const std::string& text) {
    std::cerr << text << std::endl;
}

int main(int argc, char* argv[]) {
    log("Running...");

// API uses different function do think this is needed.
///
    // Set up visited as false grid
    initialiseGrid();
///
    // Set goal on grid to 0
    grid[goal[0]][goal[1]] = 0;
    log("Grid made, goal set");

    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");
    while (true) {
        if (!API::wallLeft()) {
            API::turnLeft();
        }
        while (API::wallFront()) {
            API::turnRight();
        }
        API::moveForward();
    }
}