/*
Created by: Alex Whitfield
Date: 28/06/23

This is my mouse code for the simulator to test my code. I'm using an API, so functions will have different names
This is not the actual mouse file
*/

#include "API.h"
#include "Global.h"
// #include "Floodfill.h"
#include "direction.h"

#include <iostream>
#include <string>


void log(const std::string& text) {
    std::cerr << text << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A linked list node
struct Node {
    int data[2];
    Node* next;
}; 

// The queue, front stores the front node of the linked list and rear stores the last node of the linked list
struct Queue {
    Node *front, *end; 
    Queue() {front = end = nullptr;} // For empty queue

    // I will initialise the enQueue and deQueue funtions here within the struct so it is self-contained

    // The function to add a data to queue
    void enqueue(int x, int y) {
        // Create a new node
        Node* newNode = new Node();
        newNode->data[0] = x;
        newNode->data[1] = y;
        newNode->next = nullptr;

        // If queue is empty, then new node is front and rear both
        if (end == nullptr) {
            front = end = newNode;
            return;
        }
        // Add the new node at the end of queue and change rear
        end->next = newNode;
        end = newNode;
    }

    // Function to remove a data from given queue q
    void dequeue() {
        // If queue is empty, return NULL.
        if (front == nullptr){
            end = nullptr;
            return;
        }

        // Store previous front and move front one node ahead
        Node* temp = front;

        front = front->next;

        // If front becomes NULL, then change rear also as NULL
        if (front == nullptr){
            end = nullptr;
        }

        delete (temp);
    }
};


void floodFill(int x, int y){
////
    log("FLOODFILL");
    // Initialise the queue
    Queue q;
    // Add goal to queue
    q.enqueue(x, y);

    while (q.front != nullptr){

        // Set currentCoord as the coords at the front of queue
        int x = q.front->data[0];
        int y = q.front->data[1];   

        // Mark coord as visited
        visited[x][y] = true;

        // loop here to go through each adjacent coord
        for (int i = -1; i <= 1; i++){
            for (int j = -1; j <= 1; j++){
                // Skips current coord and diagonal coords
                if ((i != 0 && j != 0) || (i == 0 && j == 0)) {
                    continue;
                }

                int adjacentX = x + i;
                int adjacentY = y + j;

                // Check if conditions are met
                if (adjacentX >= 0 && adjacentX < grid_size && adjacentY >= 0 && adjacentY < grid_size && !visited[adjacentX][adjacentY]){
                    
                    if (j == 1 && wallGrid[x][y].north){
                        // Skip this adjacent cell if there is a wall in front
                        log("Floodfill North: " + std::to_string(wallGrid[x][y].north));
                        log("");
                        break;
                    }else if (j == -1 && wallGrid[x][y].south){
                        // Skip this adjacent cell if there is a wall behind
                        log("Floodfill South: " + std::to_string(wallGrid[x][y].south));
                        log("");
                        break;
                    }else if (i == 1 && wallGrid[x][y].east) {
                        // Perform additional wall checking based on the current and adjacent cells
                        // Skip this adjacent cell if there is a wall on the right
                        log("Floodfill East: " + std::to_string(wallGrid[x][y].east));
                        log("");
                        break;
                    }else if (i == -1 && wallGrid[x][y].west) {
                        // Skip this adjacent cell if there is a wall on the left
                        log("Floodfill West: " + std::to_string(wallGrid[x][y].west));
                        log("");
                        break;
                    }

                    grid[adjacentX][adjacentY] = grid[x][y] + 1;
                    // Add coord to the queue
                    q.enqueue(adjacentX, adjacentY);
                }
            }
        }

        q.dequeue();   // Delete the front node from queue
    }
}


void manhattanDistance(int currentX, int currentY){

    // while (currentX != goal[0] || currentY != goal[1]){
    while (goGoal){

        if (currentX == goal[0] && currentY == goal[1]){
            // We have found the goal, we can now go home
            goGoal = false;
        }
        // loop here to go through each adjacent coord
        for (int i = -1; i <= 1; i++){
            for (int j = -1; j <= 1; j++){

                int currentDistance = grid[currentX][currentY];

                // Check for walls
                bool isWallFront = API::wallFront();
                bool isWallLeft = API::wallLeft();
                bool isWallRight = API::wallRight();

                updateWallGrid(isWallFront, isWallLeft, isWallRight, currentX, currentY);

        ////
                log("Wall values at coordinate (" + std::to_string(currentX) + ", " + std::to_string(currentY) + "):");
                log("north: " + std::to_string(wallGrid[currentX][currentY].north));
                log("east: " + std::to_string(wallGrid[currentX][currentY].east));
                log("south: " + std::to_string(wallGrid[currentX][currentY].south));
                log("west: " + std::to_string(wallGrid[currentX][currentY].west));
        ////

                // Skips current coord and diagonal coords
                log("I Value: " + std::to_string(i));
                log("J Value: " + std::to_string(j));
                if ((i != 0 && j != 0) || (i == 0 && j == 0)) {
                    log("Continue");
                    log("");
                    continue;
                }

                int neighbourX = currentX + i;
                int neighbourY = currentY + j;

// This part can be simplified as we are updating the cell wall info above 
                // Check if conditions are met
                if (neighbourX >= 0 && neighbourX < grid_size && neighbourY >= 0 && neighbourY < grid_size && grid[neighbourX][neighbourY] < grid[currentX][currentY]){
                    // if i and j equal 1 or -1 it will mean its a direction
                    if (i == 1){
                        // First check if there is a wall in the way
                        if (wallGrid[currentX][currentY].east){
                            log("Recalculate, best option was EAST");
                            initialiseGrid();
                            floodFill(goal[0], goal[1]);
                            break;

                        }else{ // We can turn and move
                            log("Right");           // Console confirm
                            orientation_movement(i, j, currentX, currentY);
//                             right();                // Update the move orientation
// ///// not sure if we have to move forward by 1 or if turning right moves up forward 1
//                             forward(currentX, currentY);
                            break;
                        }
                    }else if (i == -1){
                        if (wallGrid[currentX][currentY].west){
                            log("Recalculate, best option was WEST");
                            initialiseGrid();
                            floodFill(goal[0], goal[1]);
                            break;

                        }else{
                            log("Left");
                            orientation_movement(i, j, currentX, currentY);
                            // left();
                            // forward(currentX, currentY);
                            break;
                        }
                    }else if (j == 1){
                        if (wallGrid[currentX][currentY].north){
                            log("Recalculate, best option was NORTH");
                            initialiseGrid();
                            floodFill(goal[0], goal[1]);
                            break;

                        }else{
                            log("Forward, north");
                            orientation_movement(i, j, currentX, currentY);
                            // if (currentDirection == east){
                            //     left();
                            // }else if (currentDirection == west){
                            //     right();
                            // }
                            // forward(currentX, currentY);
                            break;
                        }
                    }else{
                        if (wallGrid[currentX][currentY].south){
                            log("Recalculate, best option was SOUTH");
                            initialiseGrid();
                            floodFill(goal[0], goal[1]);
                            break;

                        }else{
                            log("Forward, south");
                            orientation_movement(i, j, currentX, currentY);
                            // if (currentDirection == west){
                            //     left();
                            // }else if (currentDirection == east){
                            //     right();
                            // }
                            // forward(currentX, currentY);
                            break;
                        }
                    }
                }else{
                    log("not value or not short");
                    log("");
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
    log("Running...");

    // Set goal on grid to 0
    grid[goal[0]][goal[1]] = 0;
    // log("Goal set");


    API::setColor(0, 0, 'G');
    API::setText(0, 0, "START");
    API::setColor(8, 7, 'R');
    API::setText(8, 7, "GOAL");

    // Actual maze solver //

    
/// fix this

    // Set up visited as false grid
    initialiseGrid();        // Call flood fill to populate the maze with values
    // log("Grid made");
    floodFill(goal[0], goal[1]);
    manhattanDistance(start[0], start[1]);

    // while (true) {
    //     if (!API::wallLeft()) {
    //         API::turnLeft();
    //     }
    //     while (API::wallFront()) {
    //         API::turnRight();
    //     }
    //     API::moveForward();
    // }
}