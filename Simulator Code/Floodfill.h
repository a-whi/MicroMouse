/*
Created by: Alex Whitfield
Date: 28/06/23

Linked list + Floodfill and Manhattan distance algorithms
Good practise to put these in its own file as they are called a lot and will also declutter the main file
*/

#pragma once
#include <iostream>
#include "Global.h"

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

    while (currentX != goal[0] || currentY != goal[1]){

        int currentDistance = grid[currentX][currentY];

// Unsure if this is really needed
        // We have found the goal, we can now go home
        if (currentX == goal[0] && currentY == goal[1]){
            goGoal = false;
        }
/////////

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