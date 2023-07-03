/*
Created by: Alex Whitfield
Date: 21/06/23

This is my Flood fill algorithm. It's written in C++ as that is what Arduino reads. 
This is my first C++ code, hence why it has so many comments.
*/


#include <iostream>


// Global variables:
// All these values are know before the competition

// Creates a blank grid
const int grid_size = 8;
int grid[grid_size][grid_size];
bool visited[grid_size][grid_size]; // Set a true or false grid to track visited nodes

int goal[2] = {5,5};
int start[2]= {0,0};
//////
bool goGoal = true;         // If false it means its reached the goal
//////

/////////////////////////////
// Class for holding the data of where walls are in each cell
class GridCell {
public:
    bool northWall;
    bool eastWall;
    bool southWall;
    bool westWall;

    GridCell() {
        northWall = false;
        eastWall = false;
        southWall = false;
        westWall = false;
    }
};
/////////////////////////////

// Set all values in the grid to -1
void initialiseGrid() {
    // Initialize the main grid and visited grid
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            visited[i][j] = false;
        }
    }
}

void printMaze() {
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Create a queue using linked list
// Add to the back take from the front deleting the head and changing the head

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

        // loop here to go through each adjacent coord
        for (int i = -1; i <= 1; i++){
            for (int j = -1; j <= 1; j++){
                // Skips current coord and diagonal coords
                if ((i == j) || (i == -j)|| (-i == j)){
                    continue;
                }

                int neighbourX = currentX + i;
                int neighbourY = currentY + j;

// If wall detected && neighbours are larger than current, recalculate (flood again)
// Remeber it should check its neighbours first to make sure there is no shorter path, if not then recalculate

                // Check if conditions are met
                if (neighbourX >= 0 && neighbourX < grid_size && neighbourY >= 0 && neighbourY < grid_size && grid[neighbourX][neighbourY] < grid[currentX][currentY]){
                    currentX = neighbourX;
                    currentY = neighbourY;
                    break;
                }

            }
        }
    }


}

int main(){

    // Set up visited as false grid
    initialiseGrid();

    // Set goal on grid to 0
    grid[goal[0]][goal[1]] = 0;

    // Call flood fill to populate the maze with values
    floodFill(goal[0], goal[1]);

    manhattanDistance(start[0], start[1]);


//Testing
    printMaze();
    // Actually running through the maze with the 'Manhattan Distancse'

    return 0;
}



// When running
// Add if cell has been visited
// if it hits a wall, recalculate floodfill

/*Psuedocode:
1. Initialize the maze grid with initial Manhattan distance values and perform the flood-fill algorithm to populate the grid.

2. Start the micromouse at the start position.

3. While the micromouse has not reached the goal position:
    a. Check if there is a wall in the direction the micromouse intends to move.
    b. If there is a wall:
        i. Stop the micromouse.
        ii. Re-initialize the grid and perform the flood-fill algorithm again to update the Manhattan distance values based on the newly discovered walls.
    c. If there is no wall:
        i. Move the micromouse to the next position along the shortest path based on the current Manhattan distance values.
        ii. Update the micromouse's current position.

4. Repeat steps 3 until the micromouse reaches the goal.
*/