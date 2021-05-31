# Arduino Servo Queue
A compressed, stochastic extension of the arduino servo library which defines a servo process.

## Description
A servo process is defined by a set of (destination, cycle) pairs which commands a servo to arrive at a particular destination in the corresponding number of cycles using linear interpolation.
### Example
> destination = [10, 50, 0]  
> cycles = [10, 4, 10]  
> The servo would take 10 cycles going at 1 unit/cycle, take 4 cycles going at 10 units/cycle, and take 10 cycles going at -5 units/cycle.

## Assumptions
A servo process generally consists of immutable destination and cycle arrays, so these are assumed to be stored and accessed via flash memory to conserve local variable space.

## Usage (ServoProcess)
### Define arrays
> #define length_1 2  
> const int destination_1[length_1] PROGMEM = {0, 10};  
> const int cycles_1[length_1] PROGMEM = {1, 2};
### Create objects
> #define num_servos 1  
> ServoProcess** process_1 = new ServoProcess*[num_servos];  
> process_1 = new ServoProcess(length_1, destination_1, cycles_1);  
> #define num_processes 1  
> ServoProcess*** bag_contents = new ServoProcess**[num_processes];  
> ServoProcessBag* bag = new ServoProcessBag(num_processes, num_servos, bag_contents);
### Query
> ServoProcess** sample = bag->sample();  
>> sample[0]->destinations = {0, 10};  
>> sample[0]->cycles = {1, 2};  

## Usage (ServoQueue)
> ServoQueue* queue = new ServoQueue();  
> queue.addInstruction(0, 10);  
> queue.addInstruction(1, 2);  
> queue.nextInstruction(); 0  
> queue.nextInstruction(); 5  
> queue.nextInstruction(); 10
