//
// Created by Steven on 5/18/2021.
//

#ifndef ARDUINO_SERVOQUEUE8BIT_H
#define ARDUINO_SERVOQUEUE8BIT_H

#include "Queue8Bit.h"
#include <math.h>

/* Stores a queue of information given inputs of destination and cycles allotted */
/* Compressed information to be stored within 8 bits */
class ServoQueue8Bit {
    const int min = 560;
    const int max = 1160;
    const int size = 200;
    static int roundFloat(float d)
    {
        return d < 0 ? (int)ceil(d - 0.5f) : (int)floor(d + 0.5f);
    }

    const float increment = ((float)(max) - (float)min) / 255; //2^8 - 1 to accommodate max
    Queue8Bit* queue;
    float lastPosition; //intermediate positions may be floats
    int lastPopped;
public:
    ServoQueue8Bit() {
        queue = new Queue8Bit(size);
        lastPosition = (float)min;
        lastPopped = (int)lastPosition;
    }
    ~ServoQueue8Bit() {
        delete queue;
    }

    void addInstruction(int dest, int cycles) {
        if (dest < min) {
            dest = min;
        }
        if (dest > max) {
            dest = max;
        }
        float rate = ((float)dest - lastPosition) / (float)cycles;
        for (int _ = 0; _ < cycles; _ += 1) {
            lastPosition += rate;
            queue->add(roundFloat((lastPosition - min) / increment));
        }
    }

    //Assumes dest and cycles are same size
    void addInstructions(int length, int* dest, int* cycles) {
        for (int i = 0; i < length; i += 1) {
            addInstruction(dest[i], cycles[i]);
        }
    }

    int nextInstruction() {
        lastPopped = queue->next() * increment + min;
        return lastPopped;
    }
    bool isEmpty() {
        return queue->isEmpty();
    }
    void reset() {
        queue->reset();
        lastPosition = (float)lastPopped;
    }
};

#endif //ARDUINO_SERVOQUEUE8BIT_H
