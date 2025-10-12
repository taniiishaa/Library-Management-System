#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // For remove() and rename()
#include <iomanip> // For formatting output (setw)

using namespace std;

// --- 1. BOOK CLASS (The core object) ---

class Book {
private:
    int bookID;
    char title[50];
    char author[50];
    bool isIssued;

public:
    // Constructor to initialize data members
    Book() : bookID(0), isIssued(false) {
        title[0] = '\0';
        author[0] = '\0';
    }

    // Function to get data from user (CREATE)
    void get_data() {
        cout << "\n\n--- Add New Book ---";
        cout << "\nEnter Book ID: ";
        cin >> bookID;
        cin.ignore(); 
        cout << "Enter Book Title: ";
        cin.getline(title, 50);
        cout << "Enter Author Name: ";
        cin.getline(author, 50);
        isIssued = false; // New books are always available
    }

    // Function to show book details (READ)
    void show_data() const {
        cout << "\nID: " << bookID;
        cout << setw(30) << left << "\tTitle: " << title;
        cout << setw(20) << left << "\tAuthor: " << author;
        cout << "\tStatus: " << (isIssued ? "Issued" : "Available");
    }

    // Accessors for private members
    int getBookID() const { return bookID; }
    bool getStatus() const { return isIssued; }

    // Mutator functions for transactions
    void issue_book() { isIssued = true; }
    void return_book() { isIssued = false; }
};

// --- 2. GLOBAL FILE I/O FUNCTIONS (The data persistence layer) ---

const char* FILENAME = "book.dat";

// Function to write a Book object to the file
void write_book() {
    Book book;
    book.get_data(); // Get details from user

    // Open file in binary append mode
    ofstream outFile(FILENAME, ios::binary | ios::app); 
    
    // Write the entire object to the file
    outFile.write(reinterpret_cast<char*>(&book), sizeof(Book)); 
    
    outFile.close();
    cout << "\n\nBook record successfully saved!";
    cin.ignore();
    cin.get();
}

// Function to read and display all Book records
void display_all_books() {
    Book book;
    ifstream inFile(FILENAME, ios::binary);
    
    if (!inFile) {
        cout << "\n\nFile could not be opened. (No records found)";
        cin.get();
        return;
    }

    cout << "\n\n\t\t\t--- ALL BOOK RECORDS ---\n\n";
    cout << "--------------------------------------------------------------------------------\n";
    
    // Read object by object until end of file
    while (inFile.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        book.show_data();
        cout << endl;
    }
    
    cout << "--------------------------------------------------------------------------------\n";
    inFile.close();
    cin.ignore();
    cin.get();
}

// Function to handle book issuing
void issue_book_func(int id) {
    Book book;
    fstream file;
    file.open(FILENAME, ios::binary | ios::in | ios::out); 
    
    if (!file) {
        cout << "Error: File not found or empty.";
        return;
    }

    bool found = false;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        if (book.getBookID() == id) {
            found = true;
            if (book.getStatus() == false) {
                // Change status and write the modified object back
                book.issue_book();
                int pos = file.tellg(); // Get current file pointer position
                file.seekg(pos - sizeof(Book)); // Move file pointer back by one Book size
                file.write(reinterpret_cast<char*>(&book), sizeof(Book));
                cout << "\n\nBook ID " << id << " successfully ISSUED.";
            } else {
                cout << "\n\nBook is already ISSUED.";
            }
            break;
        }
    }
    
    file.close();
    if (!found) {
        cout << "\nBook ID not found in records.";
    }
    cin.ignore();
    cin.get();
}

// Function to handle book returning (similar to issue_book_func)
void return_book_func(int id) {
    Book book;
    fstream file;
    file.open(FILENAME, ios::binary | ios::in | ios::out); 
    
    if (!file) {
        cout << "Error: File not found or empty.";
        return;
    }

    bool found = false;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        if (book.getBookID() == id) {
            found = true;
            if (book.getStatus() == true) {
                // Change status and write the modified object back
                book.return_book();
                int pos = file.tellg(); 
                file.seekg(pos - sizeof(Book));
                file.write(reinterpret_cast<char*>(&book), sizeof(Book));
                cout << "\n\nBook ID " << id << " successfully RETURNED.";
                // *** FINE CALCULATION LOGIC GOES HERE ***
                // E.g., cout << "\nFine applied: $X.XX";
            } else {
                cout << "\n\nBook was not issued.";
            }
            break;
        }
    }
    
    file.close();
    if (!found) {
        cout << "\nBook ID not found in records.";
    }
    cin.ignore();
    cin.get();
}

// --- 3. MENU AND DRIVER CODE ---

void admin_menu() {
    int choice, id;
    do {
        system("cls"); // Clear screen (Use "clear" on Linux/Mac)
        cout << "\n\n\t\t\t--- ADMINISTRATOR MENU ---";
        cout << "\n\t\t1. Add New Book";
        cout << "\n\t\t2. Display All Books";
        cout << "\n\t\t3. Issue Book";
        cout << "\n\t\t4. Return Book";
        cout << "\n\t\t5. Back to Main Menu";
        cout << "\n\n\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: write_book(); break;
            case 2: display_all_books(); break;
            case 3:
                cout << "\nEnter Book ID to Issue: ";
                cin >> id;
                issue_book_func(id);
                break;
            case 4:
                cout << "\nEnter Book ID to Return: ";
                cin >> id;
                return_book_func(id);
                break;
            case 5: return;
            default: cout << "\nInvalid choice. Try again.";
        }
    } while (choice != 5);
}

// Main function (The entry point)
int main() {
    int choice;

    do {
        system("cls"); // Clear screen
        cout << "\n\n\t\t\t--- LIBRARY MANAGEMENT SYSTEM ---";
        cout << "\n\t\t1. Admin Login";
        cout << "\n\t\t2. Student/User View (Browse Books)";
        cout << "\n\t\t3. Exit";
        cout << "\n\n\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            { // <-- FIX: Start of scope block
                // Simple password check (In a real app, this would be robust)
                string password;
                cout << "\nEnter Password: ";
                cin >> password;
                if (password == "admin123") {
                    admin_menu();
                } else {
                    cout << "\nIncorrect Password!";
                    cin.ignore();
                    cin.get();
                }
                break;
            } // <-- FIX: End of scope block
            case 2:
                // Students can only view the records
                display_all_books(); 
                break;
            case 3:
                cout << "\nThank you for using the Library System. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice. Try again.";
                cin.ignore();
                cin.get();
        }
    } while (choice != 3);

    return 0;
}