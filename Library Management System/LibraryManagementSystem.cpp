#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Book {
public:
    int bookID;
    string title;
    string author;
    bool issued;

    void input() {
        cout << "\nEnter Book ID: ";
        cin >> bookID;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;
    }

    void display() const {
        cout << left
             << setw(10) << bookID
             << setw(30) << title
             << setw(25) << author
             << setw(15) << (issued ? "Issued" : "Available")
             << endl;
    }
};

const string FILE_NAME = "books.txt";

// Load books from file
vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file(FILE_NAME);

    string line;

    while (getline(file, line)) {
        Book book;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        if (p1 == string::npos || p2 == string::npos || p3 == string::npos)
            continue;

        book.bookID = stoi(line.substr(0, p1));
        book.title = line.substr(p1 + 1, p2 - p1 - 1);
        book.author = line.substr(p2 + 1, p3 - p2 - 1);
        book.issued = stoi(line.substr(p3 + 1));

        books.push_back(book);
    }

    file.close();
    return books;
}

// Save books to file
void saveBooks(const vector<Book>& books) {
    ofstream file(FILE_NAME);

    for (const auto& book : books) {
        file << book.bookID << "|"
             << book.title << "|"
             << book.author << "|"
             << book.issued << endl;
    }

    file.close();
}

// Add book
void addBook() {
    Book book;
    book.input();

    ofstream file(FILE_NAME, ios::app);

    file << book.bookID << "|"
         << book.title << "|"
         << book.author << "|"
         << book.issued << endl;

    file.close();

    cout << "\nBook Added Successfully!\n";
}

// Display books
void displayBooks() {
    vector<Book> books = loadBooks();

    if (books.empty()) {
        cout << "\nNo books found.\n";
        return;
    }

    cout << "\n==========================================================================\n";
    cout << left
         << setw(10) << "Book ID"
         << setw(30) << "Title"
         << setw(25) << "Author"
         << setw(15) << "Status" << endl;
    cout << "==========================================================================\n";

    for (const auto& book : books) {
        book.display();
    }
}

// Search by title
void searchByTitle() {
    string searchTitle;

    cin.ignore();
    cout << "\nEnter Title to Search: ";
    getline(cin, searchTitle);

    vector<Book> books = loadBooks();
    bool found = false;

    for (const auto& book : books) {
        if (book.title.find(searchTitle) != string::npos) {
            if (!found) {
                cout << "\nMatching Books:\n\n";
            }
            book.display();
            found = true;
        }
    }

    if (!found)
        cout << "\nNo books found.\n";
}

// Search by author
void searchByAuthor() {
    string searchAuthor;

    cin.ignore();
    cout << "\nEnter Author Name: ";
    getline(cin, searchAuthor);

    vector<Book> books = loadBooks();
    bool found = false;

    for (const auto& book : books) {
        if (book.author.find(searchAuthor) != string::npos) {
            if (!found) {
                cout << "\nMatching Books:\n\n";
            }
            book.display();
            found = true;
        }
    }

    if (!found)
        cout << "\nNo books found.\n";
}

// Issue book
void issueBook() {
    int id;

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    vector<Book> books = loadBooks();

    for (auto& book : books) {
        if (book.bookID == id) {

            if (book.issued) {
                cout << "\nBook is already issued.\n";
                return;
            }

            book.issued = true;

            saveBooks(books);

            cout << "\nBook Issued Successfully!\n";
            return;
        }
    }

    cout << "\nBook not found.\n";
}

// Return book
void returnBook() {
    int id;

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    vector<Book> books = loadBooks();

    for (auto& book : books) {

        if (book.bookID == id) {

            if (!book.issued) {
                cout << "\nBook is already available.\n";
                return;
            }

            book.issued = false;

            saveBooks(books);

            cout << "\nBook Returned Successfully!\n";
            return;
        }
    }

    cout << "\nBook not found.\n";
}

// Delete book
void deleteBook() {
    int id;

    cout << "\nEnter Book ID to Delete: ";
    cin >> id;

    vector<Book> books = loadBooks();
    vector<Book> updatedBooks;

    bool found = false;

    for (const auto& book : books) {

        if (book.bookID == id) {
            found = true;
        }
        else {
            updatedBooks.push_back(book);
        }
    }

    if (!found) {
        cout << "\nBook not found.\n";
        return;
    }

    saveBooks(updatedBooks);

    cout << "\nBook Deleted Successfully!\n";
}

// Main menu
int main() {
    int choice;

    do {
        cout << "\n\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search By Title\n";
        cout << "4. Search By Author\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Delete Book\n";
        cout << "8. Exit\n";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            searchByTitle();
            break;

        case 4:
            searchByAuthor();
            break;

        case 5:
            issueBook();
            break;

        case 6:
            returnBook();
            break;

        case 7:
            deleteBook();
            break;

        case 8:
            cout << "\nThank You For Using Library Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 8);

    return 0;
}