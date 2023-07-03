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

    // Initialise the queue
    Queue q;
    // Add goal to queue
    q.enqueue(x, y);

    while (q.front != nullptr){

        // Set currentCoord as the coords at the front of queue
        int currentX = q.front->data[0];
        int currentY = q.front->data[1];   

        // Mark coord as visited
        visited[currentX][currentY] = true;

        // loop here to go through each adjacent coord
        for (int i = -1; i <= 1; i++){
            for (int j = -1; j <= 1; j++){
                // Skips current coord and diagonal coords
                if ((i == j) || (i == -j)|| (-i == j)){
                    continue;
                }

                int adjacentX = currentX + i;
                int adjacentY = currentY + j;

                // Check if conditions are met
                if (adjacentX >= 0 && adjacentX < grid_size && adjacentY >= 0 && adjacentY < grid_size && !visited[adjacentX][adjacentY]){
                    if (j == 1 && wallGrid[currentX][currentY].north){
                        // Skip this adjacent cell if there is a wall in front
                        continue;
                    }
                    if (j == -1 && wallGrid[currentX][currentY].south){
                        // Skip this adjacent cell if there is a wall behind
                        continue;
                    }
                    // Perform additional wall checking based on the current and adjacent cells
                    if (i == 1 && wallGrid[currentX][currentY].east) {
                        // Skip this adjacent cell if there is a wall on the right
                        continue;
                    }
                    if (i == -1 && wallGrid[currentX][currentY].west) {
                        // Skip this adjacent cell if there is a wall on the left
                        continue;
                    }

                    grid[adjacentX][adjacentY] = grid[currentX][currentY] + 1;
                    // Add coord to the queue
                    q.enqueue(adjacentX, adjacentY);
                }
            }
        }

        q.dequeue();   // Delete the front node from queue
    }
}


void manhattanDistance(int currentX, int currentY){

    while (currentX != goal[0] && currentY != goal[1]){
        int currentDistance = grid[currentX][currentY];

        // Check for walls
        bool isWallFront = API::wallFront();
        bool isWallLeft = API::wallLeft();
        bool isWallRight = API::wallRight();

        updateWallGrid(isWallFront, isWallLeft, isWallRight, currentX, currentY);

        // loop here to go through each adjacent coord
        for (int i = -1; i <= 1; i++){
            for (int j = -1; j <= 1; j++){
                // Skips current coord and diagonal coords
                if ((i == j) || (i == -j)|| (-i == j)){
                    continue;
                }

                int neighbourX = currentX + i;
                int neighbourY = currentY + j;

// This part can be simplified as we are updating the cell wall info above 
                // Check if conditions are met
                if (neighbourX >= 0 && neighbourX < grid_size && neighbourY >= 0 && neighbourY < grid_size && grid[neighbourX][neighbourY] < grid[currentX][currentY]){
                    // if wall in front or left or right recalculate
                    if (i == 1 || i == -1){
                        if (isWallLeft || isWallRight){
                            log("Wall blocking shorest path, recalculating...");
                            // recalculate as shortest is going left of right
                            floodFill(currentX, currentY);
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
                            floodFill(currentX, currentY);
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

            }
        }
    }
    // We have found the goal, we can now go home
    goGoal = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
    log("Running...");

    // Set goal on grid to 0
    grid[goal[0]][goal[1]] = 0;
    log("Goal set");


    API::setColor(0, 0, 'G');
    API::setText(0, 0, "START");
    API::setColor(8, 7, 'R');
    API::setText(8, 7, "GOAL");

    // Actual maze solver //

    
/// fix this
    while (goGoal){

        // Set up visited as false grid
        initialiseGrid();

        // Call flood fill to populate the maze with values
        floodFill(goal[0], goal[1]);
        manhattanDistance(start[0], start[1]);


    }

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