#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_FLIGHTS = 100;
const int MAX_BOOKINGS = 500;

struct Flight {
    string flightNo, from, to, time;
    int econFare, busFare;
};

struct Booking {
    string flightNo;
    string name;
    string passport;
    string cls;
    string seat;
    string date;
    string ptype;
};

Flight flights[MAX_FLIGHTS];
Booking bookings[MAX_BOOKINGS];
int flightCount = 0;
int bookingCount = 0;

void loadFlights() {
    flightCount = 0;
    ifstream fin("flights.txt");
    while (fin >> flights[flightCount].flightNo
               >> flights[flightCount].from
               >> flights[flightCount].to
               >> flights[flightCount].time
               >> flights[flightCount].econFare
               >> flights[flightCount].busFare) {
        flightCount++;
    }
    fin.close();
}

void saveFlights() {
    ofstream fout("flights.txt");
    for (int i = 0; i < flightCount; i++)
        fout << flights[i].flightNo << " "
             << flights[i].from << " "
             << flights[i].to << " "
             << flights[i].time << " "
             << flights[i].econFare << " "
             << flights[i].busFare << endl;
    fout.close();
}

void loadBookings() {
    bookingCount = 0;
    ifstream fin("bookings.txt");
    string line;

    while (getline(fin, line)) {
        int pos = 0, idx = 0;
        string parts[7];

        while ((pos = line.find('|')) != string::npos) {
            parts[idx++] = line.substr(0, pos);
            line.erase(0, pos + 1);
        }
        parts[idx] = line;

        bookings[bookingCount].flightNo = parts[0];
        bookings[bookingCount].name     = parts[1];
        bookings[bookingCount].passport = parts[2];
        bookings[bookingCount].cls      = parts[3];
        bookings[bookingCount].seat     = parts[4];
        bookings[bookingCount].date     = parts[5];
        bookings[bookingCount].ptype    = parts[6];
        bookingCount++;
    }
    fin.close();
}

void saveBookings() {
    ofstream fout("bookings.txt");
    for (int i = 0; i < bookingCount; i++)
        fout << bookings[i].flightNo << "|"
             << bookings[i].name << "|"
             << bookings[i].passport << "|"
             << bookings[i].cls << "|"
             << bookings[i].seat << "|"
             << bookings[i].date << "|"
             << bookings[i].ptype << endl;
    fout.close();
}

bool seatTaken(string fno, string date, string seat) {
    for (int i = 0; i < bookingCount; i++)
        if (bookings[i].flightNo == fno &&
            bookings[i].date == date &&
            bookings[i].seat == seat)
            return true;
    return false;
}

string nextDate(string d) {
    int day = (d[0]-'0')*10 + (d[1]-'0') + 1;
    string rest = d.substr(2);
    if (day < 10) return "0" + to_string(day) + rest;
    return to_string(day) + rest;
}

bool isValidDate(string d) {
    
    if (d.length() != 10 || d[2] != '-' || d[5] != '-')
        return false;

    int day   = (d[0]-'0')*10 + (d[1]-'0');
    int month = (d[3]-'0')*10 + (d[4]-'0');
    int year  = (d[6]-'0')*1000 + (d[7]-'0')*100 +
                (d[8]-'0')*10 + (d[9]-'0');

    
    if (day < 1 || month < 1 || month > 12)
        return false;

    
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1])
        return false;

    if (year < 2026) return false;
    if (year == 2026 && month == 1 && day < 9) return false;

    return true;
}


void printSeat(string seat, bool taken) {
    if (taken) cout << "[ X ] ";
    else cout << "[" << seat << "] ";
}

void showSeatMap(string fno, string date) {
    cout << "\n--- Business Class ---\n";
    printSeat("B1", seatTaken(fno, date, "B1"));
    printSeat("B2", seatTaken(fno, date, "B2"));
    cout << endl;
    printSeat("B3", seatTaken(fno, date, "B3"));
    printSeat("B4", seatTaken(fno, date, "B4"));
    cout << endl;
    printSeat("B5", seatTaken(fno, date, "B5"));
    cout << endl;

    cout << "\n---Economy Class ---\n";
    for (int i = 1; i <= 10; i++) {
        string s = "E" + to_string(i);
        printSeat(s, seatTaken(fno, date, s));
        if (i % 2 == 0) cout << endl;
    }
}


bool viewFlights() {
    string dest, date;
    cout << "Enter destination: ";
    cin >> dest;
    cout << "Enter date (DD-MM-YYYY): ";
    cin >> date;

    if (!isValidDate(date)) {
        cout << "Invalid date. Please enter a date on or after 09-01-2026.\n";
        return false;
    }

    string nd = nextDate(date);
    cout << "\nAvailable Flights\n";
    cout << "------------------------------------------\n";

    cout << "\n--- Flights on " << date << " ---\n";
    for (int i = 0; i < flightCount; i++)
        if (flights[i].to == dest)
            cout << flights[i].flightNo << " " << flights[i].from << "->"
                 << flights[i].to << " | " << date << " | "
                 << flights[i].time << endl;

    cout << "\n--- Flights on " << nd << " ---\n";
    for (int i = 0; i < flightCount; i++)
        if (flights[i].to == dest)
            cout << flights[i].flightNo << " " << flights[i].from << "->"
                 << flights[i].to << " | " << nd << " | "
                 << flights[i].time << endl;

    return true;
}


void bookFlight() {
    if (!viewFlights()) return;

    Booking b;
    cout << "\nEnter Flight No: ";
    cin >> b.flightNo;
    cout << "Enter Date: ";
    cin >> b.date;

    if (!isValidDate(b.date)) {
        cout << "Invalid date.\n";
        return;
    }
 
    showSeatMap(b.flightNo, b.date);
    cout << "\nClass (B/E): ";
    cin >> b.cls;
    cout << "Seat: ";
    cin >> b.seat;

    if (seatTaken(b.flightNo, b.date, b.seat)) {
        cout << "Seat already booked.\n";
        return;
    }

    cin.ignore();
    cout << "Passenger Name: ";
    getline(cin, b.name);
    cout << "Passport Number: ";
    cin >> b.passport;
    cout << "Passenger Type (Normal/Student/Military/Senior): ";
    cin >> b.ptype;

    bookings[bookingCount++] = b;
    saveBookings();

    int baseFare = 0;
    for (int i = 0; i < flightCount; i++)
        if (flights[i].flightNo == b.flightNo)
            baseFare = (b.cls == "B") ? flights[i].busFare : flights[i].econFare;

    double discount = (b.ptype != "Normal") ? baseFare * 0.05 : 0;
    double tax = baseFare * 0.05;
    double total = baseFare - discount + tax;

    cout << "\n----------- BOARDING PASS -----------\n";
    cout << "Passenger : " << b.name << endl;
    cout << "Passport : " << b.passport << endl;
    cout << "Flight : " << b.flightNo << endl;
    cout << "Date : " << b.date << endl;
    cout << "Seat : " << b.seat << endl;
    cout << "Fare : " << baseFare << endl;
    cout << "Discount : -" << discount << endl;
    cout << "Tax (5%) : +" << tax << endl;
    cout << "TOTAL : " << total << endl;
    cout << "\nBooking completed successfully.\n";
}
void viewBookings() {
    if (bookingCount == 0) {
        cout << "\nNo bookings found.\n";
        return;
    }

    cout << "\n---------------- ALL BOOKINGS ----------------\n";
    cout << left << setw(8)  << "Flight"
     << setw(12) << "From"
     << setw(12) << "To"
     << setw(20) << "Name"
     << setw(16) << "Passport"
     << setw(8)  << "Cls"
     << setw(6)  << "Seat"
     << setw(12) << "Date"
     << setw(10) << "Type" << endl;


    cout << "--------------------------------------------------------------------------\n";

    for (int i = 0; i < bookingCount; i++) {
        string from = "-", to = "-";

        // find flight details
        for (int j = 0; j < flightCount; j++) {
            if (flights[j].flightNo == bookings[i].flightNo) {
                from = flights[j].from;
                to   = flights[j].to;
                break;
            }
        }

        cout << left << setw(8)  << bookings[i].flightNo
             << setw(12) << from
             << setw(12) << to
             << setw(20) << bookings[i].name
             << setw(16) << bookings[i].passport
             << setw(8)  << bookings[i].cls
             << setw(6)  << bookings[i].seat
             << setw(12) << bookings[i].date
             << setw(10) << bookings[i].ptype << endl;

    }
}

void cancelBooking() {
    string fno, date, seat;
    cout << "Flight No: ";
    cin >> fno;
    cout << "Date: ";
    cin >> date;
    cout << "Seat: ";
    cin >> seat;

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].flightNo == fno &&
            bookings[i].date == date &&
            bookings[i].seat == seat) {

            for (int j = i; j < bookingCount - 1; j++)
                bookings[j] = bookings[j + 1];

            bookingCount--;
            saveBookings();
            cout << "Booking canceled successfully.\n";
            return;
        }
    }
    cout << "Booking not found.\n";
}

void adminMenu() {
    string u, p;
    cout << "Admin Username: ";
    cin >> u;
    cout << "Admin Password: ";
    cin >> p;

    if (u != "admin" || p != "admin123") {
        cout << "Invalid admin credentials.\n";
        return;
    }

    int ch;
    do {
        cout << "\n--- ADMIN PORTAL ---\n";
        cout << "1. Add Flight\n2. Cancel Flight\n3. Delay Flight\n4. Exit\nChoice: ";
        cin >> ch;

        if (ch == 1) {
            flights[flightCount++] = Flight();
            cout << "Flight No: "; cin >> flights[flightCount-1].flightNo;
            cout << "From: "; cin >> flights[flightCount-1].from;
            cout << "To: "; cin >> flights[flightCount-1].to;
            cout << "Time: "; cin >> flights[flightCount-1].time;
            cout << "Economy Fare: "; cin >> flights[flightCount-1].econFare;
            cout << "Business Fare: "; cin >> flights[flightCount-1].busFare;
            saveFlights();
            cout << "\nFlight added successfully.\n";
        }
        else if (ch == 2) {
            string fno;
            cout<<"Enter Flight No: ";
            cin >> fno;
            for (int i = 0; i < flightCount; i++)
                if (flights[i].flightNo == fno) {
                    for (int j = i; j < flightCount - 1; j++)
                        flights[j] = flights[j + 1];
                    flightCount--;
                    saveFlights();
                    cout << "\nFlight canceled successfully.\n";
                    break;
                }
        }
        else if (ch == 3) {
            string fno;
            cin >> fno;
            for (int i = 0; i < flightCount; i++)
                if (flights[i].flightNo == fno) {
                    cin >> flights[i].time;
                    saveFlights();
                    cout << "\nFlight time updated successfully.\n";
                    break;
                }
        }
    } while (ch != 4);
}

int main() {
    loadFlights();
    loadBookings();

    int ch;
    do {
        cout << "\n===== FLIGHT RESERVATION SYSTEM =====\n";
        cout << "1. View Flights\n2. Book Flight\n3. Cancel Booking\n4. View Bookings\n5. Admin Portal\n6. Exit\nChoice: ";
        cin >> ch;

        if (ch == 1) viewFlights();
        else if (ch == 2) bookFlight();
        else if (ch == 3) cancelBooking();
        else if (ch == 4) viewBookings();   
        else if (ch == 5) adminMenu();

    } while (ch != 6);
    cout << "\nThank you for using our Flight Reservation System.\n";
    return 0;
}


