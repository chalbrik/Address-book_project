#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Contact {
    int id;
    string name;
    string lastName;
    string telephone;
    string email;
    string address;
};

struct User {
    int userId;
    string username;
    string password;
};

string readLine() {
    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

char getSymbol() {
    string input = "";
    char symbol = {0};

    while(1) {
        cin.sync();
        getline(cin, input);

        if(input.length() == 1) {
            symbol = input[0];
            break;
        }
        cout << "This is not a single character. Try again: " << endl;
    }
    return symbol;
}


void getUsersFromFile(vector <User> &users) {
    fstream usersDataFile;
    string line;
    int numberOfLine = 1;

    User userData;
    string extract = "";
    int indexOfVerticalBar = 0;
    int lenghtOfLineAfterVerticalBar = 0;
    int caseCounter = 0;

    usersDataFile.open("Users_data.txt", ios::in);

    if(usersDataFile.good()) {
        while(getline(usersDataFile, line)) {

            switch(numberOfLine) {
            case 1:

                while(line.size()>0) {

                    indexOfVerticalBar = line.find('|');

                    extract = line.substr(0, indexOfVerticalBar);

                    caseCounter++;

                    lenghtOfLineAfterVerticalBar = line.size() - extract.size();

                    line = line.substr(indexOfVerticalBar + 1, lenghtOfLineAfterVerticalBar - 1);

                    switch(caseCounter) {
                    case 1:
                        userData.userId = stoi(extract);
                        break;
                    case 2:
                        userData.username = extract;
                        break;
                    case 3:
                        userData.password = extract;
                        break;
                    }
                }
                break;
            }
            if(numberOfLine == 1) {
                users.push_back(userData);
                caseCounter = 0;
                numberOfLine = 0;
            }
            numberOfLine++;
        }
    }
    usersDataFile.close();
}

void logIn(vector <User> &users) {

    string username = "";
    string password = "";

    system("cls");
    cout << "Username: ";
    username = readLine();
    cout << "Password: ";
    password = readLine();

    for(size_t i = 0; i < users.size(); i++) {
        if(username == users[i].username && password == users[i].password) {
            cout << "Zalogowano" << endl;
            system("pause");

        } else if(username != users[i].username && password == users[i].password) {
            cout << "Nieprawodlowy login" << endl;
            system("pause");

        } else if(username == users[i].username && password != users[i].password) {
            cout << "Nieprawidlowe haslo" << endl;
            system("pause");
        }
    }

    return;
}

void signIn(vector <User> &users) {

    fstream usersDataFile;

    User userData;
    string username = "";
    string password = "";

    system("cls");
    cout << "Enter username: ";
    userData.username = readLine();
    cout << "Enter password: ";
    userData.password = readLine();

    userData.userId = (users.size() > 0) ? users[users.size() - 1].userId + 1 : 1;

    users.push_back(userData);

    usersDataFile.open("Users_data.txt", ios::out | ios::app);

    usersDataFile << userData.userId << "|" << userData.username << "|" << userData.password << "|" << endl;

    return;
}


void getContactsFromFile(vector <Contact> &contacts) {
    fstream file;
    string line;
    int numberOfLine = 1;

    Contact contactData;
    string extract = "";
    int indexOfVerticalBar = 0;
    int lenghtOfLineAfterVerticalBar = 0;
    int caseCounter = 0;

    file.open("Address_book.txt", ios::in);

    if(file.good()) {
        while(getline(file, line)) {

            switch(numberOfLine) {
            case 1:

                while(line.size()>0) {

                    indexOfVerticalBar = line.find('|');

                    extract = line.substr(0, indexOfVerticalBar);

                    caseCounter++;

                    lenghtOfLineAfterVerticalBar = line.size() - extract.size();

                    line = line.substr(indexOfVerticalBar + 1, lenghtOfLineAfterVerticalBar - 1);

                    switch(caseCounter) {
                    case 1:
                        contactData.id = stoi(extract);
                        break;
                    case 2:
                        contactData.name = extract;
                        break;
                    case 3:
                        contactData.lastName = extract;
                        break;
                    case 4:
                        contactData.telephone = extract;
                        break;
                    case 5:
                        contactData.email = extract;
                        break;
                    case 6:
                        contactData.address = extract;
                        break;
                    }
                }
                break;
            }
            if(numberOfLine == 1) {
                contacts.push_back(contactData);
                caseCounter = 0;
                numberOfLine = 0;
            }
            numberOfLine++;
        }
    }
    file.close();
}

void saveContactsToFile(vector <Contact> &contacts) {
    fstream file;
    int indexNumber = contacts.size() - 1;

    file.open("Address_book.txt", ios::out | ios::app);

    file << contacts[indexNumber].id << "|" << contacts[indexNumber].name << "|" << contacts[indexNumber].lastName << "|" << contacts[indexNumber].telephone << "|" << contacts[indexNumber].email << "|" << contacts[indexNumber].address << "|" << endl;

    file.close();
}

void overrideContactsInFile(vector <Contact> &contacts, int index, bool edit) { //moze trzebabedzie tutaj dodac warunek otwierania sie plikow czy istnieja
    fstream file;
    vector <string> fileLines;
    string fileLine;
    string editedContact = "";

    file.open("Address_book.txt", ios::in);

    if(file.fail()) {
        cout << "File doesn't exist." << endl << endl;
        system("pause");
        return;
    }

    while(getline(file, fileLine)) {
        fileLines.push_back(fileLine);
    }

    file.close();

    fileLines.erase(fileLines.begin() + index);

    if(edit == true) {
        editedContact = to_string(contacts[index].id) + "|" + contacts[index].name + "|" + contacts[index].lastName + "|" + contacts[index].telephone + "|" + contacts[index].email + "|" + contacts[index].address + "|";
        fileLines.insert(fileLines.begin() + index, editedContact);
    }

    file.open("Address_book.txt", ios::out);

    if(file.fail()) {
        cout << "File doesn't exist." << endl << endl;
        system("pause");
        return;
    }

    for(size_t j = 0; j < fileLines.size(); j++) {
        file << fileLines[j] << endl;
    }

}

void saveContact(vector <Contact> &contacts) {

    Contact contactData;

    system("cls");
    cout << "///ADDRESS BOOK -> Save contact" << endl << endl;

    cout << "Name: ";
    contactData.name = readLine();

    cout << "Last name: ";
    contactData.lastName = readLine();

    cout << "Telephone number: ";
    contactData.telephone = readLine();

    cout << "Email: ";
    contactData.email = readLine();

    cout << "Home addres: ";
    contactData.address = readLine();

    contactData.id = (contacts.size() > 0) ? contacts[contacts.size() - 1].id + 1 : 1;

    contacts.push_back(contactData);

    cout << contacts.size();

    saveContactsToFile(contacts);

    system("cls");
    cout << "///ADDRESS BOOK -> Save contact" << endl << endl;
    cout << "Contact was successfully added to address book." << endl << endl;
    system("pause");
}

void writeOutContacts(vector <Contact> &contacts, int index) {
    cout << "ID: " << contacts[index].id <<  endl;
    cout << "Name: " << contacts[index].name << endl;
    cout << "Last name: " << contacts[index].lastName << endl;
    cout << "Telephone number: " << contacts[index].telephone << endl;
    cout << "Email: " << contacts[index].email << endl;
    cout << "Home address: " << contacts[index].address << endl;
    cout << endl;
}

void searchContact(vector <Contact> &contacts) {
    char choice;
    string lookFor;
    int numberOfContacts = contacts.size();

    while(1) {
        system("cls");

        cout << "///ADDRESS BOOK -> Search contact" << endl << endl;

        if(numberOfContacts > 0) {
            cout << "1 - Search after name" << endl;
            cout << "2 - Search after last name" << endl;
            cout << "3 - Show all contacts" << endl;
            cout << "4 - Back to main menu" << endl;
            cout << endl;
            cout << "Option: ";
            choice = getSymbol();

            if(choice == '1') {
                system("cls");
                cout << "Name: ";
                lookFor = readLine();
                cout << endl;

                for(int i=0; i < numberOfContacts; i++) {
                    if(lookFor == contacts[i].name) {
                        writeOutContacts(contacts, i);
                    } else if(lookFor != contacts[i].name && i == numberOfContacts - 1) {
                        cout << "This contact doesn't exist." << endl;
                    }
                }

                cout << endl;
                system("pause");

            } else if(choice == '2') {
                system("cls");
                cout << "Last name: ";
                lookFor = readLine();
                cout << endl;

                for(int i=0; i < numberOfContacts; i++) {
                    if(lookFor == contacts[i].lastName) {
                        writeOutContacts(contacts, i);
                    } else if(lookFor != contacts[i].lastName && i == numberOfContacts - 1) {
                        cout << "This contact doesn't exist." << endl;
                    }
                }
                cout << endl;
                system("pause");

            } else if(choice == '3') {
                system("cls");

                for(int i=0; i < numberOfContacts; i++) {
                    writeOutContacts(contacts, i);
                }
                cout << endl;
                system("pause");

            } else if(choice == '4') {
                return;
            }
        } else {
            cout << "Address book is empty." << endl;
            cout << endl;
            system("pause");
            return;
        }
    }
}

void getRidOfContact(vector <Contact> &contacts) {

    char choice;
    char getRidOfConfirmation;
    string idToGetRidOf;

    while(1) {
        system("cls");

        cout << "///BOOK ADDRESS -> Delete contact" << endl << endl;

        if(contacts.size() > 0) {

            cout << "1 - Choose contact to delete" << endl;
            cout << "2 - Show all contacts" << endl;
            cout << "3 - Back to main menu" << endl;
            cout << endl;
            cout << "Option: ";
            choice = getSymbol();
            cout << endl;

            if(choice == '1') {
                cout << "Insert ID to delete contact: ";
                cin >> idToGetRidOf;

                for(size_t i = 0; i < contacts.size(); i++) {
                    if(stoi(idToGetRidOf) == contacts[i].id) {
                        system("cls");
                        cout << "You request for deleting: " << endl;
                        writeOutContacts(contacts, i);
                        cout << endl;
                        cout << "Are you sure you want to delete that contact? If yes, press - y. If no, press - n." << endl;
                        getRidOfConfirmation = getSymbol();

                        if(getRidOfConfirmation == 'y' || getRidOfConfirmation == 'Y') {
                            contacts.erase(contacts.begin() + i);
                            overrideContactsInFile(contacts, i, false);
                        } else {
                            return;
                        }
                    } else if(stoi(idToGetRidOf) != contacts[i].id && i == contacts.size() - 1) {
                        cout << endl;
                        cout << "Contact with given ID doesn't exist." << endl << endl;
                        system("pause");
                        return;
                    }
                }

            } else if(choice == '2') {
                system("cls");

                for(size_t i=0; i < contacts.size(); i++) {
                    writeOutContacts(contacts, i);
                }
                cout << endl;
                system("pause");

            } else if(choice == '3') {
                return;
            }
        } else {
            cout << "Address book is empty." << endl;
            cout << endl;
            system("pause");
            return;

        }
    }
}

void editContact(vector <Contact> &contacts) {

    string idToChange = "";
    char choice;
    int numberOfContacts = contacts.size();
    while(1) {
        system("cls");

        cout << "///BOOK ADDRESS -> Edit contact" << endl << endl;

        if(numberOfContacts > 0) {

            cout << "1 - Choose contact to edit" << endl;
            cout << "2 - Show all contacts" << endl;
            cout << "3 - Back to main menu" << endl;
            cout << endl << endl;
            cout << "Option: ";
            choice = getSymbol();
            cout << endl;
            if(choice == '1') {
                cout << "Insert ID to edit: ";
                cin >> idToChange;
                cout << endl;

                for(int i =0; i < numberOfContacts; i++) {
                    if(stoi(idToChange) == contacts[i].id) {

                        system("cls");

                        cout << "Edytujesz kontakt: " << endl << endl;
                        writeOutContacts(contacts, i);
                        cout << endl;

                        cout << "Which element would you like to change:" << endl;
                        cout << "1 - Name" << endl;
                        cout << "2 - Last name" << endl;
                        cout << "3 - Telephone number" << endl;
                        cout << "4 - Email" << endl;
                        cout << "5 - Home address" << endl;
                        cout << "6 - Back to menu" << endl;
                        cout << endl << endl;
                        cout << "Option: ";
                        cin >> choice;
                        cout << endl;

                        if(choice == '1') {
                            cout << "Insert new name: ";
                            contacts[i].name = readLine();

                        } else if(choice == '2') {
                            cout << "Insert new last name: ";
                            contacts[i].lastName = readLine();

                        } else if(choice == '3') {
                            cout << "Insert new telephone number: ";
                            contacts[i].telephone = readLine();

                        } else if(choice == '4') {
                            cout << "Insert new email: ";
                            contacts[i].email = readLine();

                        } else if(choice == '5') {
                            cout << "Insert new home address: ";
                            contacts[i].address = readLine();

                        } else if(choice == '6') {
                            return;
                        }
                        overrideContactsInFile(contacts, i, true);
                    }
                }
            } else if(choice == '2') {
                system("cls");

                for(int i=0; i < numberOfContacts; i++) {
                    writeOutContacts(contacts, i);
                }
                cout << endl;
                system("pause");

            } else if(choice == '3') {
                return;
            }
        } else {
            cout << "Address book is empty." << endl;
            cout << endl;
            system("pause");
            return;
        }
    }

}

void displayMainAddressBookPage(vector <Contact> &contacts) {
    char choice;

    system("cls");
    cout << "///ADDRESS BOOK///" << endl << endl;
    cout << "Number of contacts in the book - " << contacts.size() << endl << endl;
    cout << "1 - Save contact" << endl;
    cout << "2 - Search contact" << endl;
    cout << "3 - Delete contact" << endl;
    cout << "4 - Edit contact" << endl;
    cout << "5 - Close address book" << endl;
    cout << endl;
    cout << "Option: ";
    choice = getSymbol();
    cout << endl;

    if(choice == '1') {
        saveContact(contacts);

    } else if(choice == '2') {
        searchContact(contacts);

    } else if(choice == '3') {
        getRidOfContact(contacts);

    } else if(choice == '4') {
        editContact(contacts);

    } else if(choice == '5') {
        exit(0);
    }

    return;
}

void displayEntryAppPage(vector <User> &users) {
    char chosenOption;

    system("cls");

    cout << "Liczba userow: " << users.size() << endl << endl; //potem usun

    cout << "ADDRESS BOOK" << endl << endl;
    cout << "1 - Log in" << endl;
    cout << "2 - Sign in" << endl;
    cout << "3 - Close app" << endl << endl;
    cout << "Option: ";

    chosenOption = getSymbol();

    if(chosenOption == '1') {
        logIn(users);

    } else if(chosenOption == '2') {
        signIn(users);

    } else if(chosenOption == '3') {
        exit(0);

    } else {
        system("cls");
        cout << "This option is not a possibility. Try again." << endl << endl;
        system("pause");
    }

    return;
}

int main() {

    vector <User> users;
    vector <Contact> contacts;

    getUsersFromFile(users);

    getContactsFromFile(contacts);

    while(1) {

        displayEntryAppPage(users);

        //displayMainAddressBookPage(contacts);
    }

    return 0;
}
