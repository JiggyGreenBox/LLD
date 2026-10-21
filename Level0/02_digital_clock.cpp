/*
Problem Statement: 
Digital Clock System

Design and implement a clean, object-oriented Digital Clock 
in-memory. The system should manage time representation, handle 
regular time progression (ticking), allow manual time setting with 
validation, and output the time in a standard format.


Functional Requirements
    Time Representation:
    The clock must track time using Hours (0 to 23), Minutes (0 to 59), and Seconds (0 to 59).

    Tick Operation:
        Implement a method to advance the clock by 1 second

    Manual Time Setting:
        Allow setting the clock to a specific time

    Display Format:
        Provide a method to return the current time as a zero-padded string in the format
*/

/*
Entites
    clock
        displayTime
        tick
        setTime

Time
    - hours
    - minutes
    - seconds

    + tick
        boundary logic here

    + setTime
        validation here

    + print

*/

#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

class Time {
    private:
        int hours;
        int minutes;
        int seconds;
    public:
        bool setTime(int _hours, int _minutes, int _seconds) {

            if( _hours   < 0 || _hours   >= 24  ||
                _minutes < 0 || _minutes >= 60  || 
                _seconds < 0 || _seconds >= 60)
                return false;

            hours   = _hours;
            minutes = _minutes;
            seconds = _seconds;

            return true;
        }

        void tick() {

            seconds++;
            if(seconds != 60) 
                return;
            
            seconds = 0;
            minutes++;

            if(minutes != 60)
                return;

            minutes = 0;
            hours++;

            if(hours != 24)
                return;

            hours = 0;
        }


        string print() const { 
            std::ostringstream out; 
            out << std::setfill('0') 
                << std::setw(2) << hours << ':' 
                << std::setw(2) << minutes << ':' 
                << std::setw(2) << seconds; 
            return out.str(); 
    }
};

class Clock {
    private:
        Time time;

    public:
        Clock() {
            time.setTime(0, 0, 0);
        }
        Clock(int hours, int minutes, int seconds) {
            if(!time.setTime(hours, minutes, seconds))
                time.setTime(0, 0, 0);
        }

        bool setTime(int hours, int minutes, int seconds) {
            return time.setTime(hours, minutes, seconds);
        }

        void tick() {
            time.tick();
        }

        string getTimeString() {
            return time.print();
        }
};

int main() {

    Clock clock;
    clock.setTime(23, 59, 58);
    cout << clock.getTimeString() << endl;
    

    clock.tick();
    cout << clock.getTimeString() << endl;

    clock.tick();
    cout << clock.getTimeString() << endl;

    clock.setTime(00, 00, 00);
    clock.tick();
    cout << clock.getTimeString() << endl;
    clock.setTime(24, 00, 00);
    clock.setTime(12, 60, 00);
    clock.setTime(12, 60, 60);
    cout << clock.getTimeString() << endl;

    return 0;
}