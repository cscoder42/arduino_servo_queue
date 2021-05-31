//
// Created by Steven on 5/18/2021.
//

#ifndef ARDUINO_QUEUE8BIT_H
#define ARDUINO_QUEUE8BIT_H

/* Finite-sized overriding queue */
class Queue8Bit {
private:
    int size;
    int capacity;
    int start, end;
    uint8_t* array;
    void incrementStart() {
        start = (start + 1) % size;
        capacity -= 1;
    }
    void incrementEnd() {
        end = (end + 1) % size;
        capacity += 1;
    }

public:
    Queue8Bit(int size) {
        this->size = size;
        capacity = 0;
        start = 0;
        end = 0;
        array = new uint8_t[size];
    }
    ~Queue8Bit() {
        delete array;
    }

    void add(uint8_t val) {
        if (capacity < size) {
            array[end] = val;
            incrementEnd();
        }
    }
    uint8_t next() {
        if (capacity == 0) { //empty
            Serial.println("Out of bounds!");
        }
        int temp = array[start];
        incrementStart();
        return temp;
    }
    void reset() {
        capacity = 0;
        start = 0;
        end = 0;
    }
    bool isEmpty() {
        return capacity == 0;
    }
};

#endif //ARDUINO_QUEUE8BIT_H
