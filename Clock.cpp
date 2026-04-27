#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <limits>
using namespace std;

/*
 * Name: Joohyun Lee
 * Course: CS 210
 * Project One: Chada Tech Clocks
 * Description:
 * This program displays a 12-hour clock and a 24-hour clock side by side.
 * The user enters an initial time, then uses a menu to add one hour,
 * one minute, or one second to both clocks simultaneously.
 */

// Global time values shared by both clock displays
int hourValue = 0;
int minuteValue = 0;
int secondValue = 0;

// Function prototypes
string formatTwoDigits(int number);
void displayClocks();
void displayMenu();
void updateTime();
void addOneHour();
void addOneMinute();
void addOneSecond();
bool getInitialTime();
int getMenuChoice();
void processChoice(int choice);

// Formats a number as two digits, adding a leading zero if needed
string formatTwoDigits(int number) {
    if (number < 10) {
        return "0" + to_string(number);
    }
    return to_string(number);
}

// Displays both 12-hour and 24-hour clocks side by side
void displayClocks() {
    int displayHour12 = hourValue % 12;
    if (displayHour12 == 0) {
        displayHour12 = 12;
    }

    string period = (hourValue >= 12) ? "PM" : "AM";

    cout << "***************************    ***************************" << endl;
    cout << "*      12-Hour Clock     *    *      24-Hour Clock     *" << endl;
    cout << "*      "
         << formatTwoDigits(displayHour12) << ":"
         << formatTwoDigits(minuteValue) << ":"
         << formatTwoDigits(secondValue) << " "
         << period
         << "      *    "
         << "*        "
         << formatTwoDigits(hourValue) << ":"
         << formatTwoDigits(minuteValue) << ":"
         << formatTwoDigits(secondValue)
         << "        *" << endl;
    cout << "***************************    ***************************" << endl;
    cout << endl;
}

// Displays the user menu
void displayMenu() {
    cout << "******************************" << endl;
    cout << "* 1 - Add One Hour          *" << endl;
    cout << "* 2 - Add One Minute        *" << endl;
    cout << "* 3 - Add One Second        *" << endl;
    cout << "* 4 - Exit Program          *" << endl;
    cout << "******************************" << endl;
}

// Keeps time values within valid ranges
void updateTime() {
    if (secondValue >= 60) {
        secondValue = 0;
        minuteValue++;
    }

    if (minuteValue >= 60) {
        minuteValue = 0;
        hourValue++;
    }

    if (hourValue >= 24) {
        hourValue = 0;
    }
}

// Adds one hour to the clock
void addOneHour() {
    hourValue++;
    updateTime();
}

// Adds one minute to the clock
void addOneMinute() {
    minuteValue++;
    updateTime();
}

// Adds one second to the clock
void addOneSecond() {
    secondValue++;
    updateTime();
}

// Gets and validates the initial time in HH:MM:SS format
bool getInitialTime() {
    string timeInput;

    while (true) {
        cout << "Enter initial time (HH:MM:SS): ";
        cin >> timeInput;

        if (sscanf(timeInput.c_str(), "%d:%d:%d", &hourValue, &minuteValue, &secondValue) == 3) {
            if (hourValue >= 0 && hourValue <= 23 &&
                minuteValue >= 0 && minuteValue <= 59 &&
                secondValue >= 0 && secondValue <= 59) {
                return true;
            }
        }

        cout << "Invalid time. Please enter time as HH:MM:SS using valid values." << endl;
        cout << endl;
    }
}

// Gets and validates the user's menu selection
int getMenuChoice() {
    int choice;

    while (true) {
        cout << "Select option: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 4." << endl;
            cout << endl;
            continue;
        }

        if (choice >= 1 && choice <= 4) {
            return choice;
        }

        cout << "Invalid command. Please select a valid option from 1 to 4." << endl;
        cout << endl;
    }
}

// Performs the correct action based on the user's menu choice
void processChoice(int choice) {
    if (choice == 1) {
        addOneHour();
    }
    else if (choice == 2) {
        addOneMinute();
    }
    else if (choice == 3) {
        addOneSecond();
    }
}

int main() {
    int userChoice = 0;

    // Get the starting time from the user
    getInitialTime();

    // Continue showing clocks and menu until the user exits
    while (userChoice != 4) {
        displayClocks();
        displayMenu();
        userChoice = getMenuChoice();

        if (userChoice != 4) {
            processChoice(userChoice);
            cout << endl;
        }
    }

    cout << "Program ended." << endl;

    return 0;
}