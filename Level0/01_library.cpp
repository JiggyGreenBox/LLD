// Level 0
// Below sde1 level of difficulty
//     book and library
//     student gradebook
//     bank account
//     shopping cart
//     simple atm

/*
LLD Practice 01: Book and Library Management

Problem statement
Beginner

Design and implement a simple Library Management System in C++.
A library maintains a collection of books. Each book has a unique ID, 
a title, and an author. Users should be able to find books, borrow 
available books, and return borrowed books.
Your task is to design the classes and implement the functionality 
described below.

Functional requirements
1. Add a book to the library.
2. Find a book using its ID.
3. Borrow a book if it exists and is available.
4. Return a book if it is currently borrowed.
5. Display all books along with their availability.

Business rules
- Each book ID must be unique.
- A book cannot be borrowed if it is already borrowed.
- A book cannot be returned if it is already available.
- Attempting to find or borrow a nonexistent book must fail 
gracefully.

Out of scope
- User accounts and membership.
- Due dates, fines and reservations.
- Multiple copies of the same book.
- Databases, networking and concurrent access.

Expected deliverable
- A class diagram or a written description of your classes.
- A working C++ implementation.
- A small main() demonstrating adding, finding, borrowing and 
returning a book.

*/

/*
library
    - unordered_map<int, Book> books
    + addBook(Book book)
    + borrowBook(id)
    + returnBook(id)    
    + displayAvailableBooks()

book
    - int ID
    - string author
    - string description
    - string title
    - bool borrowed
    + details
*/

#include <bits/stdc++.h>
using namespace std;

class Book {
    private:
        int book_id;
        string title;
        string author;
        string description;
        bool borrowed;
    public:
        Book(   int book_id,
                string title,
                string author,
                string description) :
                
                book_id(book_id),
                title(title),
                author(author),
                description(description),
                borrowed(false) {}

        void getDescription() const {
            cout << title + " by: " + author + ".\n" + description + "\n";
        }

        int id() const {
            return book_id;
        }

        bool isBorrowed() const {
            return borrowed;
        }

        bool borrow() {
            // cant borrow a borrowed book
            if(borrowed){                
                return false;
            }

            borrowed = true;
            return true;
        }

        bool returnBook() {
            // cant return a unborrowed book
            if(!borrowed){                
                return false;
            }

            borrowed = false;
            return true;
        }
};

class Library {
    private:
        unordered_map<int, Book> books;
    public:
        void addBook(Book book) {

            auto it = books.find(book.id());
            if(it != books.end())
                return;

            // books[book.id()] = book;
            books.emplace(book.id(), book);
        }

        Book* findBook(int book_id) {
            auto it = books.find(book_id);
            if(it == books.end())
                return nullptr;

            return &it->second;
        }
        
        bool borrowBook(int book_id) {
            auto it = books.find(book_id);
            if(it == books.end())
                return false; // invalid book id

            return it->second.borrow();
        }

        bool returnBook(int book_id) {
            auto it = books.find(book_id);
            if(it == books.end())
                return false; // invalid book id
            
            return it->second.returnBook();
        }

        void displayAvailableBooks() {
            for(const auto &[id, book] : books) {
                if(!book.isBorrowed()) {
                    book.getDescription();
                }
            }
        }

        void displayBooks() {
        for (const auto& [id, book] : books) {
            cout << "ID: " << id << '\n';
            book.getDescription();
            cout << "Status: "
                << (book.isBorrowed() ? "Borrowed" : "Available")
                << "\n\n";
        }
    }
};

int main() {


    Library lb;
    Book b1(101, "LLD", "abc", "Book on LLD");
    Book b2(102, "HLD", "xyz", "Book on HLD");
    lb.addBook(b1);
    lb.addBook(b2);

    lb.displayAvailableBooks();

    lb.borrowBook(101);
    lb.returnBook(101);
    if(!lb.returnBook(101))
        cout << "cant return unborrowed book" << endl;

    lb.borrowBook(101);
    if(!lb.borrowBook(101))
        cout << "cant borrow borrowed book" << endl;


    if(!lb.borrowBook(1011))
        cout << "cant borrow non existent book" << endl;

    lb.displayAvailableBooks();
    lb.displayBooks();
    
    if (auto* b = lb.findBook(102)) {
        b->getDescription();
    } else {
        cout << "Book not found\n";
    }

    return 0;
}
