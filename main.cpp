#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

constexpr int MaxRecord = 100;

    struct details {
        int id{};
        string author, name;
        bool available{};
    };

details book[MaxRecord];
int BookCount = 0;

void ViewAllBooks();
void SearchBook();
void AddBook();
void EditBook();
void DeleteBook();
void CheckAvailability();
void Borrow();
void Exit();
void Continue();

int main() {
    int option;
    do {
        cout << "\n=======================================\n";
        cout << "Library Management System";
        cout << "\n=======================================\n";
        cout << "[1] View All Books\n";
        cout << "[2] Search Book\n";
        cout << "[3] Add Book\n";
        cout << "[4] Edit Book\n";
        cout << "[5] Delete Book\n";
        cout << "[6] Check Availability\n";
        cout << "[7] Borrow\n";
        cout << "[8] Exit";
        cout << "\n=======================================\n";
        cout << "What would you like to do?\n";
        cout << "Enter number of option: ";
        cin >> option;

        switch (option) {
            case 1: ViewAllBooks(); break;
            case 2: SearchBook(); break;
            case 3: AddBook(); break;
            case 4: EditBook(); break;
            case 5: DeleteBook(); break;
            case 6: CheckAvailability(); break;
            case 7: Borrow(); break;
            case 8: Exit(); break;
            default: cout <<"Invalid choice\n";
                     cout << "Please select from numbers 1-8 and try again.\n";
        }
        if (option != 8) {
            Continue();
        }
    }while (option != 8);

    return 0;
}

void ViewAllBooks() {
    if (BookCount == 0) {
        cout << "There are currently no books in the database.\n";
        return;
    }

    cout << left << setw(5) << "No."
         << setw(14) << "ID"
         << setw(23) << "Author"
         << setw(23) << "Name"
         << setw(10) << "Available\n";
    cout << "------------------------------------------------------------------------------\n";

    for (int i = 0; i < BookCount; ++i) {
        if (book[i].available)
            cout << setw(5) << i + 1
                    << setw(10) << book[i].id
                    << setw(20) << book[i].author
                    << setw(33) << book[i].name
                    << setw(15) << "Yes" << endl;
        else
            cout << setw(5) << i + 1
                    << setw(10) << book[i].id
                    << setw(20) << book[i].author
                    << setw(33) << book[i].name
                    << setw(15) << "No" << endl;
    }
}

void SearchBook() {
    int id;
    cout << "Enter book ID: ";
    cin >> id;

    for (int i = 0; i < BookCount; ++i) {
        if (book[i].id == id) {
            cout << "Book found: \n";
            cout << "Id: " << book[i].id << endl;
            cout << "Author: " << book[i].author << endl;
            cout << "Name: " << book[i].name << endl;
            if (book[i].available)
                cout << "Available: " << "Yes\n";
            else
                cout << "Available: " << "No\n";
            return;
         }
    }
    cout << "Book not found.\n";
}

void AddBook() {
    if (BookCount >= MaxRecord) {
        cout << "The limit of books available in the library has been reached.\n";
        cout << "Please upgrade or free up the library storage.\n";
        return;
    }

    int id;
    string author, name;

    while (true) {
        cout << "Enter book ID: ";
        cin >> id;

        bool duplicate = false;
        for (int i = 0; i < BookCount; ++i) {
            if (book[i].id == id) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            cout << "This ID is already taken. Please enter a unique ID.\n" << endl;
        } else {
            break;
        }
    }

    cin.ignore();
    cout << "Enter author: ";
    getline(cin, author);

    cout << "Enter book name: ";
    getline(cin, name);

    book[BookCount] = {id, author, name, true};
    BookCount++;

    cout << "Book successfully added!\n";
}


void EditBook() {
    int id;
    cout << "Enter book ID to edit: ";
    cin >> id;

    for (int i = 0; i < BookCount; ++i) {
        if (book[i].id == id) {
            string author, name;
            cout << "Enter new author: ";
            cin.ignore();
            getline(cin, author);
            cout << "Enter new book name: ";
            getline(cin, name);

            book[i].author = author;
            book[i].name = name;

            cout << "Book successfully updated!\n";
            return;

        }
    }
    cout << "Book not found.\n";
}

void DeleteBook() {
    int id;
    cout << "Enter book ID to delete: ";
    cin >> id;

    for (int i = 0; i < BookCount; ++i) {
        if (book[i].id ==id) {
            for (int j = i; j < BookCount - 1; ++j) {
                book[j] = book[j + 1];
            }
            BookCount--;
            cout << "Book successfully deleted!\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void CheckAvailability() {
    int id;
    cout << "Enter book ID to check availability: ";
    cin >> id;

    for (int i = 0; i < BookCount; ++i) {
        if (book[i].id == id) {
            cout << "Book '" << book[i].name << "' is ";
            if (book[i].available)
                cout << "availabe." << endl;
            else
                cout << "not available." << endl;
            return;
        }
    }
    cout << "Book not found.\n";
}

void Borrow() {
    int id;
    cout << "Enter book ID to borrow: ";
    cin >> id;

    for (int i = 0; i < BookCount; ++i) {
        if (book[i].id == id) {
            if (book[i].available) {
                book[i].available = false;
                cout << "You have successfuly borrowed '" << book[i].name << "'.\n";
            } else {
                cout << "Sorry, that book is currently unavailable.\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

void Exit() {
    cout << "Thank you for using the library!";
}

void Continue() {
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}