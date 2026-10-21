# sde0 level problems
1. Digital Clock / Stopwatch
2. Bank Account System
3. Simple Counter / Tally Marker
4. Library Book Tracker



# pre requisites
1. OOP basics
    class, obect, constructor, static, final, overloading, overriding
2. Four pillars
    Encap, abstraction, inheritance, poly
3. Relationships
    association, aggregation, composition
4. SOLID
5. Interface vs Abstract
6. Design patterns
7. UML basics
8. LLD problems


# SDE1 OOD/LLD roadmap

## Level 1 — Basic object collaboration

Goal: multiple classes working together, sensible responsibilities, validation, and state management.

### 01 Shopping Cart
 - Next problem
 - Product, CartItem, ShoppingCart
 - Add/remove items, update quantities, calculate totals, prevent duplicates.
### 02 Student Gradebook
 - Student, Course, Gradebook
 - Manage grades, calculate averages, handle missing records.
### 03 Simple ATM
 - Account, ATM, Transaction
 - Withdraw, deposit, check balance, reject invalid transactions.
### 04 Tic-Tac-Toe
 - Board, Game, Player
 - Validate moves, detect wins, handle draws and turns.

## Level 2 — State, rules, and object relationships

Goal: model a real-world system where several objects must cooperate while preserving rules.

### 05 Parking Lot — simplified
 - Vehicle, ParkingSpot, ParkingLot, Ticket
 - Park and unpark vehicles, find compatible spots, track availability.
### 06 Vending Machine
 - Product, Inventory, VendingMachine, Transaction
 - Select an item, accept payment, dispense products, handle insufficient funds and out-of-stock items.
### 07 Elevator — single elevator
 - Elevator, Request, Controller
 - Handle floor requests, movement, direction, and door state.
### 08 Splitwise — simplified
 - User, Group, Expense, Split
 - Split expenses equally, calculate balances, and record who owes whom.

## Level 3 — Extensible design
- Goal: handle changing requirements without turning the code into a collection of conditionals. 
- Introduce interfaces and design patterns only when they solve a real problem.
### 09 Notification Service

Email/SMS/push channels, sender interface

Add channels without rewriting the notification workflow.

### 10 Logger

Logger, log levels, output destinations

Support multiple outputs and configurable log levels.

### 11 Payment Processing

Payment, PaymentMethod, PaymentProcessor

Support multiple payment methods, failures, and transaction states.

### 12 Movie Ticket Booking

Movie, Show, Seat, Booking, Payment

Handle seat availability, booking lifecycle, and conflicting reservations.

## Level 4 — SDE1 interview readiness, then SDE2 stretch

These are more challenging. Attempt them after you can independently design the earlier systems.

| #  | Problem                      | Main challenge                                              |
| -- | ---------------------------- | ----------------------------------------------------------- |
| 13 | File System / Directory Tree | Hierarchies and recursive composition                       |
| 14 | LRU Cache                    | Data structures and constant-time operations                |
| 15 | Rate Limiter                 | Time-based state and concurrency considerations             |
| 16 | Multi-elevator system        | Scheduling and coordination                                 |
| 17 | Full Splitwise               | Multiple split types and balance simplification             |
| 18 | Extensible Parking Lot       | New vehicle/spot types and pricing policies                 |
| 19 | Food Delivery                | Orders, restaurants, delivery assignment, state transitions |

These aren't all mandatory SDE1 problems. In particular, LRU Cache is often more of a data-structure or machine-coding exercise, while the larger booking and delivery systems can extend into SDE2 territory.

## How I recommend you practise each problem

Use the same process each time, so you're learning a repeatable skill rather than memorizing solutions.

1. Requirements: Write down the features and important edge cases.
2. Design: Identify classes, their responsibilities, relationships, and public methods.
3. Review: Check whether each class owns the right state and whether responsibilities are duplicated.
4. Implementation: Write the C++ code and test normal and failure cases.
5. Extension: Change one requirement and see whether your design can accommodate it cleanly.

For your first few problems, do both design and implementation. Later, practise some as timed design interviews and others as coding exercises. That's the progression we discussed previously.&#x20;

My recommendation: start with Shopping Cart, then Student Gradebook, then Tic-Tac-Toe. Don't rush to Parking Lot or Vending Machine yet. Once the first three feel manageable, move up. The goal is to build enough confidence to reason through an unfamiliar design—not to finish the longest possible list.