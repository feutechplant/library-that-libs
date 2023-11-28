#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include "datafunc.h"
using namespace std;

int main() {

    // basic initialization stuff
    string cmd, searchTerm;
    int userID, entpassword;
    map<int, Book> libraryDatabase;
    map<int, User> userDatabase;
    createLibrary(libraryDatabase);
    populateUserDatabase(userDatabase, libraryDatabase);

    // for login
    start:
    cout << "Enter user ID: ";
    cin >> userID;
    cout << "Enter password for user " << userID << ": ";
    cin >> entpassword;

    if (login(userID, entpassword, userDatabase)) {

        while (true) {

            // admin check
            if (userID == 333) {
                cout << "You are an administrator and have special priviliges." << endl;
            }
            // menu
            cout << "Enter a command, type /help for list of commands: ";
            cin >> cmd;
            
            if (cmd == "/data") {
                displayUserData(userID, userDatabase, libraryDatabase);
            } else if (cmd == "/avail") {
                displayUnavailableBooks(libraryDatabase);
            } else if ((cmd == "/over") && (userID == 333)) {
                displayOverdueBooks(userDatabase, libraryDatabase);
            } else if (cmd == "/cat") {
            	displayLibrary(libraryDatabase);
			} else if (cmd == "/search") {
				cout << "Enter a keyword to search for a book: ";
				cin >> searchTerm;
				searchBook(searchTerm, libraryDatabase);
			} else if (cmd == "/help") {
				helpDesk();
			} else if (cmd == "/logout") {
				goto start;
			} else if (cmd == "/exit") {
                cout << "Exiting program." << endl;
                return 0;
            } else {
                cout << "Invalid command." << endl;
            }
        }
    }

    return 0;
}


