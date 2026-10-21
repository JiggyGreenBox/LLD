/*
Problem Statement: Simple Counter / Tally Marker

Design and implement a clean, object-oriented Simple Counter (or 
Tally Marker) in-memory. The system should track a numerical count, 
support safe incrementing and decrementing within optional minimum 
and maximum bounds, and provide reset and retrieval capabilities.



Functional Requirements

1. Counter Initialization:
    *   Each counter can be initialized with a starting value (default to 
    0), and optional Minimum and Maximum bounds (e.g., preventing the 
    count from dropping below 0 or exceeding 100).


2. Increment Operation:
    * Increase the count by 1 (or a specified step value).
    * If a maximum bound is set, ensure the count does not exceed it 
    (either cap it at the maximum or reject the increment).


3. Decrement Operation:
    * Decrease the count by 1 (or a specified step value).
    * If a minimum bound is set, ensure the count does not drop below it 
    (either floor it at the minimum or reject the decrement).


4. Reset Operation:
    * Reset the counter back to its initial starting value.


5. Retrieval:
    * Provide a method to view the current count value.
*/

#include <stdexcept>
#include <iostream>
using namespace std;

class Counter {
    int min_val;
    int max_val;
    int val;
    int init_val;

    public:
        Counter(int val, int min_val=0, int max_val = 100) : val(val), init_val(val), min_val(min_val), max_val(max_val) {
            if(val < min_val || val > max_val)
                throw invalid_argument("values are set correctly");

            if (min_val > max_val)
                throw invalid_argument("min_val cannot exceed max_val");
        }

        void increment(int by=1) {
            val += by;
            if(val > max_val)
                val = max_val;
        }

        void decrement(int by=1) {
            val -= by;
            if(val < min_val)
                val = min_val;
        }

        void reset() {
            val = init_val;
        }

        int getVal() const {
            return val;
        }
};



int main() {
    Counter count(7,5,10);

    for(int i=0; i<8; i++) {
        count.increment();   
    }

    cout << count.getVal() << endl;

    for(int i=0; i<8; i++) {
        count.decrement();   
    }

    cout << count.getVal() << endl;

    return 0;
}