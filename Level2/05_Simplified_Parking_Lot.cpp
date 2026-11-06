/*
Level 1 — Problem 05: Simplified Parking Lot
    SDE1 foundation
    OOD / LLD
    C++

Problem statement
Design and implement a simplified Parking Lot system in C++.

The parking lot contains a fixed number of parking spots. Vehicles 
can enter, occupy a compatible available spot, and leave. The system 
must track availability and issue a ticket when a vehicle parks.

Requirements
    1. Vehicle: Each vehicle has a unique registration number and a 
    vehicle type.
    2. ParkingSpot: Each spot has a unique spot ID, a supported vehicle 
    type, and an occupancy status.
    3. ParkingLot: Manages all parking spots and coordinates parking and 
    unparking.
    4. Park a vehicle: Find an available spot compatible with the vehicle 
    and park it.
    5. Ticket: When a vehicle parks successfully, issue a ticket 
    containing the ticket ID, vehicle registration number, and spot ID.
    6. Reject invalid parking: Reject a vehicle if no compatible spot is 
    available. Do not change the lot's state.
    7. Unpark a vehicle: Given a valid ticket ID, release the associated 
    spot.
    8. Reject invalid tickets: An unknown or already-used ticket must not 
    change the lot's state.
    9. Track availability: Report how many spots are available.
    10. Prevent duplicate parking: A vehicle already parked in the lot 
    cannot park again.


Scope and assumptions
To keep this exercise focused on object-oriented design:
- Support two vehicle types: Bike and Car.
- A bike spot accepts only bikes; a car spot accepts only cars.
- The lot has a fixed set of spots created at initialization.
- Use the first compatible available spot.
- No pricing, payments, reservations, multiple floors, or concurrent 
access yet.
*/

#include <vector>
#include <optional>
#include <iostream>
using namespace std;

enum class VehicleType {
    BIKE,
    CAR
};
    

class Vehicle {
    private:
        VehicleType type;
        int id;
        string plate;
    public:
        Vehicle(
            VehicleType type,
            int id,
            string plate
        ) : 
            type(type),
            id(id),
            plate(plate) {}

        int getId() const {
            return id;
        }

        VehicleType getType() const {
            return type;
        }

        string getPlate() const {
            return plate;
        }
};
    

class ParkingSpot {
    private:
        int id;
        VehicleType type;
        bool occupied;
    public:
        ParkingSpot (
            int id,
            VehicleType type,
            bool occupied
        ) : 
            id(id), 
            type(type), 
            occupied(occupied) {}

        void setOccupied(bool b) {
            occupied = b;
        }

        int getId() const {
            return id;
        }

        bool isOccupied() const {
            return occupied;
        }

        VehicleType getType() const {
            return type;
        }
};

class Ticket {
    private:
        int ticket_id;
        int spot_id;
        int vehicle_id;
        int time_issued;
    public:
        Ticket(
            int ticket_id,
            int spot_id,
            int vehicle_id,
            int time_issued
        ) : 
            ticket_id(ticket_id), 
            spot_id(spot_id), 
            vehicle_id(vehicle_id), 
            time_issued(time_issued) {}

        int id() const {
            return ticket_id;
        }

        int getVehicleId() const {
            return vehicle_id;
        }

        int getSpotId() const {
            return spot_id;
        }

        int getTime() const {
            return time_issued;
        }
};

class ParkingLot {
    private:
        vector<ParkingSpot> &spots;
        vector<Ticket> tickets;

        ParkingSpot* findSpot(int spot_id) {
            for(auto &spot : spots) {
                if(spot.getId() == spot_id)
                    return &spot;
            }
            return nullptr;
        }

        Ticket* findTicket(int ticket_id) {
            for(auto &ticket : tickets) {
                if(ticket.id() == ticket_id)
                    return &ticket;
            }
            return nullptr;
        }

        int curr_ticket_no;
        int fare_per_hr;

    public:
        ParkingLot(vector<ParkingSpot> &spots) : spots(spots), curr_ticket_no(0), fare_per_hr(50) {

        }

        optional<int> getVacantSpot(VehicleType type) {
            for(auto spot : spots) {
                if(!spot.isOccupied() && spot.getType() == type)
                    return spot.getId();
            }
            return nullopt;
        }

        optional<int> park(int vehicle_id, int spot_id, int time) {

            ParkingSpot* spot = findSpot(spot_id);
            if(spot == nullptr || spot->isOccupied())
                return nullopt;

            Ticket ticket(++curr_ticket_no, spot_id, vehicle_id, time);
            spot->setOccupied(true);
            tickets.push_back(ticket);

            return curr_ticket_no; // ticket_id;
        }
            

        optional<int> unpark(int ticket_id, int curr_time) {
            Ticket* ticket = findTicket(ticket_id);
            if(ticket == nullptr)
                return nullopt;

            // validate spot
            int spot_id = ticket->getSpotId();
            ParkingSpot* spot = findSpot(spot_id);
            if(spot == nullptr || !spot->isOccupied())
                return nullopt;
            
            // free spot
            spot->setOccupied(false);
            // need to erase ticket here?
            
            int fare = (curr_time - ticket->getTime()) * fare_per_hr;

            return fare;
        }
};

int main() {


    vector<ParkingSpot> spots;
    int spot_id = 0;
    for(int i=0; i<2; i++) {
        ParkingSpot spot(spot_id++, VehicleType::BIKE, false);
        spots.push_back(spot);
    }
    for(int i=0; i<2; i++) {
        ParkingSpot spot(spot_id++, VehicleType::CAR, false);
        spots.push_back(spot);
    }

    ParkingLot lot(spots);

    Vehicle b1(VehicleType::BIKE, 1, "B1");
    Vehicle b2(VehicleType::BIKE, 2, "B2");
 
    Vehicle c1(VehicleType::CAR, 1, "C1");
    Vehicle c2(VehicleType::CAR, 2, "C2");

    
    // try to park cars
    auto spot1 = lot.getVacantSpot(b1.getType());
    optional<int> t1 = nullopt;
    if(spot1.has_value()) {
        t1 = lot.park(b1.getId(), spot1.value(), 1);
    }


    optional<int> f1 = nullopt; // fare
    if(t1.has_value()) {
        f1 = lot.unpark(t1.value(), 2);
        if(f1.has_value())
            cout << f1.value() << endl;
    }   

    return 0;
}