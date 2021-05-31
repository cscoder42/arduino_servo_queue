//
// Created by Steven on 5/16/2021.
//

#ifndef ARDUINO_SERVOPROCESSBAG_H
#define ARDUINO_SERVOPROCESSBAG_H

#include "ServoProcess.h"

/* Stochastically sampled group of processes */
class ServoProcessBag {
    public:
        int num_processes;
        int servos;
        ServoProcess*** processes;

        //Shape: (processes * servos) and non-empty
        ServoProcessBag(int num_processes, int servos, ServoProcess*** processes) {
            this->num_processes = num_processes;
            this->servos = servos;
            this->processes = processes;
        }

        //Shape: (servos)
        ServoProcess** sample() const {
            return processes[random(num_processes)];
        }
};
#endif //ARDUINO_SERVOPROCESSBAG_H
