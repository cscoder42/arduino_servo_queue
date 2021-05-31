//
// Created by Steven on 5/16/2021.
//

#ifndef ARDUINO_SERVOPROCESS_H
#define ARDUINO_SERVOPROCESS_H


/* An immutable list of destination-cycle pairs */
class ServoProcess {
    const int* destinations;
    const int* cycles;

    public:
        int len;
        //Constructor directly shallow copies arrays (can be changed)
        //Assumes: destinations.length == cycles.length
        ServoProcess(int len, const int destinations[], const int cycles[]) {
            this->len = len;
            this->destinations = destinations;
            this->cycles = cycles;
        }

        int getDestinations(int8_t index) {
            int dest =  pgm_read_word(&(destinations[index]));
            return dest;
        }
        int getCycles(int index) {
            int cyc = pgm_read_word(&(cycles[index]));
            return cyc;
        }
};
#endif //ARDUINO_SERVOPROCESS_H
