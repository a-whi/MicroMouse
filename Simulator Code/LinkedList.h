/*
Created by: Alex Whitfield
Date: 28/06/23

Create a queue using linked list
Add to the back take from the front deleting the head and changing the head
*/

#pragma once
#include <iostream>

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