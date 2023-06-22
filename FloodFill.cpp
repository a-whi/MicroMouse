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


// Set all values in the grid to -1
void initializeGrid() {
    // Initialize the main grid and visited grid
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            visited[i][j] = false;
        }
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
        if (front == nullptr)
            return;

        // Store previous front and move front one node ahead
        Node* temp = front;

        front = front->next;

        // If front becomes NULL, then change rear also as NULL
        if (front == nullptr)
            end = nullptr;

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

        // if grid cood +-1 is in grid range && grid[currentcood[0]][(currentcood[1])+1] == blank or the value currently set is larger than the new value
        if (currentY + 1 < grid_size && !visited[currentX][currentY+1]){
            grid[currentX][currentY+1] = grid[currentX][currentY] + 1;
            // Add coord to the queue
            q.enqueue(currentX, currentY+1);

        }else if (currentY - 1 < grid_size && !visited[currentX][currentY-1]){
            grid[currentX][currentY-1] = grid[currentX][currentY] + 1;
            q.enqueue(currentX, currentY-1);

        }else if (currentX + 1 < grid_size && !visited[currentX+1][currentY]){
            grid[currentX+1][currentY] = grid[currentX][currentY] + 1;
            q.enqueue(currentX+1, currentY);

        }else if (currentX - 1 < grid_size && !visited[currentX-1][currentY+1]){
            grid[currentX-1][currentY] = grid[currentX][currentY] + 1;
            q.enqueue(currentX-1, currentY);
        }
        q.dequeue();   // Delete the front node from queue
    }
}


/*
Psudocode:
1. Set all cells except goal to 'Blank state'
2. Set goal cell(s) value to 0 and add to queue
3. While queue is not empty
    a. Take front cell in queue 'out of line' for consideration
    b. Set all blank and accessible neighbours to front cells value + 1
    c. Add cells we just processed to the queue
    d. Else, continue
*/ 


void printMaze() {
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int main(){

    // Set goal on grid to 0
    grid[goal[0]][goal[1]] = 0;

    // Set up visited as false grid
    initializeGrid();

    // Call flood fill to populate the maze with values
    floodFill(goal[0], goal[1]);

    printMaze();
    // Actually running through the maze with the 'Manhattan Distancse'

    return 0;
}



// When running
// Add if cell has been visited
// if it hits a wall, recalculate floodfill