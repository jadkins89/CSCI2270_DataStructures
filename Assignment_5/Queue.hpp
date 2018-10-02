//
//  Queue.hpp
//  CircularQueue
//
//  Created by Sunil on 2/25/17.
//  Copyright © 2017 Sunil. All rights reserved.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

class Queue
{
public:
    Queue(int);
    ~Queue();
    //circular queue methods
    void enqueue(std::string);
    void dequeue();
    void printQueue();
    void enqueueSentence(std::string);
    bool queueIsFull(); //check when full
    bool queueIsEmpty(); //check when empty
    
protected:
private:
    int queueSize;
    int queueHead;
    int queueTail;
    int queueCount;
    std::string *arrayQueue;
};

#endif // QUEUE_H