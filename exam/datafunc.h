#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>
using namespace std;

struct Book {
    string title;
    int publicationYear;
    bool overdue;
    bool inCirculation;
};

struct User {
    string username;
    int password;
    vector<pair<int, bool>> borrowedBooks;
};

void createLibrary(map<int, Book>& libraryDatabase) {
    libraryDatabase[1] = { "The First Book", 2022, 0, 1 };
    libraryDatabase[2] = { "The Second Tome", 2023, 0, 1 };
    libraryDatabase[3] = { "The Third Novel", 1, 0 };
    libraryDatabase[4] = { "The Fourth Chronicle", 2020, 0, 1 };
    libraryDatabase[5] = { "The Fifth Reference Book", 2021, 0, 1 };
    libraryDatabase[6] = { "The Sixth Journal", 2022, 0, 1 };
    libraryDatabase[7] = { "The Seventh Diary", 2023, 1, 0 };
    libraryDatabase[8] = { "The Eighth Log", 2021, 0, 1 };
    libraryDatabase[9] = { "The Ninth Binder", 2022, 0, 1 };
    libraryDatabase[10] = { "The Tenth Treatise", 2023, 1, 1 };
}

void populateUserDatabase(map<int, User>& userDatabase, const map<int, Book>& libraryDatabase) {
    userDatabase[111] = { "User111", 123, {{1, 0}, {2, 0}, {3, 1}, {4, 1}, {5, 0}, {6, 0}, {7, 1}, {8, 0}, {9, 0}, {10, 1}} };
    userDatabase[222] = { "User222", 456, {{1, 1}, {2, 0}, {3, 1}, {4, 0}, {5, 1}, {6, 1}, {7, 0}, {8, 0}, {9, 1}, {10, 1}} };
    userDatabase[333] = { "User333", 789, {{1, 0}, {2, 1}, {3, 1}, {4, 0}, {5, 0}, {6, 1}, {7, 1}, {8, 1}, {9, 0}, {10, 0}} };
    userDatabase[444] = { "User444", 999, {{1, 1}, {2, 1}, {3, 0}, {4, 1}, {5, 1}, {6, 0}, {7, 0}, {8, 1}, {9, 0}, {10, 0}} };
}

void displayLibrary(const map<int, Book>& libraryDatabase) {
    for (const auto& entry : libraryDatabase) {
        cout << "Book: " << entry.first << ", Title: " << entry.second.title << ", Year: " << entry.second.publicationYear << endl;
    }
}

bool login(int userKey, int password, const map<int, User>& userDatabase) {
    auto it = userDatabase.find(userKey);

    if (it != userDatabase.end()) {
        int storedPassword = it->second.password;

        if (password == storedPassword) {
            cout << "Login successful." << endl;
            return true;
        }
        else {
            cout << "Login failed. Incorrect password for user " << userKey << endl;
            return false;
        }
    }
    else {
        cout << "Login failed. User " << userKey << " not found." << endl;
        return false;
    }
}

// displays user borrowed books
void displayUserData(int userID, const map<int, User>& userDatabase, const map<int, Book>& libraryDatabase) {
    auto it = userDatabase.find(userID);

    if (it != userDatabase.end()) {
        cout << "User " << userID << " (" << it->second.username << ") has borrowed: ";
        for (const auto& entry : it->second.borrowedBooks) {
            int bookID = entry.first;
            bool isOverdue = entry.second;

            // retrieve book title from libraryDatabase
            auto bookIt = libraryDatabase.find(bookID);
            if (bookIt != libraryDatabase.end()) {
                cout << bookIt->second.title;

                if (isOverdue) {
                    cout << " (Overdue)";
                }

                cout << ", ";
            }
        }
        cout << endl;
    } else {
        cout << "User " << userID << " not found in the user database." << endl;
    }
}

void displayUnavailableBooks(const map<int, Book>& libraryDatabase) {
    cout << "Unavailable Books:" << endl;

    for (const auto& entry : libraryDatabase) {
        if (!entry.second.inCirculation) {
            cout << "Book " << entry.first << ": " << entry.second.title << endl;
        }
    }
}

void displayOverdueBooks(const map<int, User>& userDatabase, const map<int, Book>& libraryDatabase) {
    cout << "Overdue Books:" << endl;

    for (const auto& userEntry : userDatabase) {
        for (const auto& borrowedBook : userEntry.second.borrowedBooks) {
            int bookID = borrowedBook.first;
            bool overdue = borrowedBook.second;

            auto bookIt = libraryDatabase.find(bookID);
            if (bookIt != libraryDatabase.end() && overdue) {
                cout << "User " << userEntry.first << " (" << userEntry.second.username << ") - ";
                cout << "Book " << bookID << ": " << bookIt->second.title << endl;
            }
        }
    }
}

// Check if the keyword is present in the book title (case-insensitive)
void searchBook(const string& keyword, const map<int, Book>& libraryDatabase) {
    cout << "Search Results for '" << keyword << "':" << endl;
    for (const auto& entry : libraryDatabase) {
        if (entry.second.title.find(keyword) != string::npos) {
            cout << "Book: " << entry.first << ", Title: " << entry.second.title
                << ", Year: " << entry.second.publicationYear << endl;
        }
    }
}

void helpDesk() {
	cout << "\n  --list of commands-- \n\n";
	cout << "/help - displays this menu" << endl;
	cout << "/data - displays current user data (list of borrowed books)" << endl;
	cout << "/search - search functionality" << endl;
	cout << "/over - displays overdue borrows (admin only)" << endl;
	cout << "/avail - displays unavailable books" << endl;
	cout << "/cat - displays the catalogue" << endl;
	cout << "/logout - return to login screen" << endl;
	cout << "/exit - closes the program" << endl;
	
}
