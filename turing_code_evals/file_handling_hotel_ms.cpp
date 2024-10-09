#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_SUITES = 100;
const int MAX_RESERVATIONS = 100;

class Suite {
private:
    int suiteNumber;
    bool statusAvailable;
    double ratePerNight;

public:
    Suite(int number = 0, bool available = true, double rate = 0.0)
        : suiteNumber(number), statusAvailable(available), ratePerNight(rate) {}

    int getSuiteNumber() const { return suiteNumber; }
    bool isAvailable() const { return statusAvailable; }
    double getRate() const { return ratePerNight; }

    void setAvailability(bool availability) { statusAvailable = availability; }
    void setRate(double rate) { ratePerNight = rate; }

    void showSuiteDetails() const {
        cout << "Suite Number: " << suiteNumber << endl;
        cout << "Available: " << (statusAvailable ? "Yes" : "No") << endl;
        cout << "Rate per Night: $" << ratePerNight << endl;
    }
};

class Reservation {
private:
    int reservationID;
    int suiteNumber;
    string guestName;
    int stayDuration;
    string contactNumber;

public:
    Reservation(int id = 0, int suite = 0, string guest = "", int duration = 0, string contact = "")
        : reservationID(id), suiteNumber(suite), guestName(guest), stayDuration(duration), contactNumber(contact) {}

    int getReservationID() const { return reservationID; }
    int getSuiteNumber() const { return suiteNumber; }
    string getGuestName() const { return guestName; }
    int getDuration() const { return stayDuration; }
    string getContactNumber() const { return contactNumber; }

    double getTotalCost(const Suite &suite) const {
        return stayDuration * suite.getRate();
    }

    void showReservationDetails() const {
        cout << "Reservation ID: " << reservationID << endl;
        cout << "Suite Number: " << suiteNumber << endl;
        cout << "Guest Name: " << guestName << endl;
        cout << "Duration of Stay: " << stayDuration << endl;
        cout << "Contact Number: " << contactNumber << endl;
    }
};

class Invoice {
private:
    Reservation reservation;
    double grandTotal;

public:
    Invoice(const Reservation &res, const Suite &s) : reservation(res) {
        grandTotal = reservation.getTotalCost(s);
    }

    void showInvoice() const {
        cout << "----- Invoice Details -----" << endl;
        reservation.showReservationDetails();
        cout << "Total Cost: $" << grandTotal << endl;
    }
};

class HotelManager {
private:
    Suite suites[MAX_SUITES];
    Reservation reservations[MAX_RESERVATIONS];
    int suiteCount;
    int reservationCount;
    string adminPassword;

    void readSuitesFromFile() {
        ifstream file("suites.dat", ios::binary);
        if (!file) return;

        suiteCount = 0;
        while (file.read(reinterpret_cast<char*>(&suites[suiteCount]), sizeof(Suite)) && suiteCount < MAX_SUITES) {
            ++suiteCount;
        }

        file.close();
    }

    void writeSuitesToFile() const {
        ofstream file("suites.dat", ios::binary);
        for (int i = 0; i < suiteCount; ++i) {
            file.write(reinterpret_cast<const char*>(&suites[i]), sizeof(Suite));
        }

        file.close();
    }

    void readReservationsFromFile() {
        ifstream file("reservations.dat", ios::binary);
        if (!file) return;

        reservationCount = 0;
        while (file.read(reinterpret_cast<char*>(&reservations[reservationCount]), sizeof(Reservation)) && reservationCount < MAX_RESERVATIONS) {
            ++reservationCount;
        }

        file.close();
    }

    void writeReservationsToFile() const {
        ofstream file("reservations.dat", ios::binary);
        for (int i = 0; i < reservationCount; ++i) {
            file.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));
        }

        file.close();
    }

public:
    HotelManager() : suiteCount(0), reservationCount(0), adminPassword("<SECRET>") {
        readSuitesFromFile();
        readReservationsFromFile();
    }

    ~HotelManager() {
        writeSuitesToFile();
        writeReservationsToFile();
    }

    bool authenticate(const string &inputPassword) const {
        return inputPassword == adminPassword;
    }

    void addSuite() {
        int number;
        double rate;
        cout << "Enter suite number: ";
        cin >> number;
        cout << "Enter rate per night: ";
        cin >> rate;

        if (suiteCount < MAX_SUITES) {
            suites[suiteCount++] = Suite(number, true, rate);
            cout << "Suite successfully added!" << endl;
        } else {
            cout << "Suite limit reached!" << endl;
        }
    }

    void deleteSuite() {
        int number;
        cout << "Enter suite number to delete: ";
        cin >> number;

        for (int i = 0; i < suiteCount; ++i) {
            if (suites[i].getSuiteNumber() == number) {
                for (int j = i; j < suiteCount - 1; ++j) {
                    suites[j] = suites[j + 1];
                }
                --suiteCount;
                cout << "Suite successfully removed!" << endl;
                return;
            }
        }

        cout << "Suite not found!" << endl;
    }

    void showSuites() const {
        for (int i = 0; i < suiteCount; ++i) {
            suites[i].showSuiteDetails();
            cout << "------------------" << endl;
        }
    }

    void overseeReservations() {
        int option;
        cout << "1. see All Reservations\n2. Delete a Reservation\n";
        cin >> option;

        switch (option) {
        case 1:
            for (int i = 0; i < reservationCount; ++i) {
                reservations[i].showReservationDetails();
                cout << "------------------" << endl;
            }
            break;

        case 2:
            int reservationID;
            cout << "Enter reservation ID to delete: ";
            cin >> reservationID;

            for (int i = 0; i < reservationCount; ++i) {
                if (reservations[i].getReservationID() == reservationID) {
                    for (int j = i; j < reservationCount - 1; ++j) {
                        reservations[j] = reservations[j + 1];
                    }
                    --reservationCount;
                    cout << "Reservation successfully removed!" << endl;
                    return;
                }
            }

            cout << "Reservation not found!" << endl;
            break;

        default:
            cout << "Invalid selection!" << endl;
            break;
        }
    }
};

class Guest {
private:
    Suite availableSuites[MAX_SUITES];
    Reservation reservations[MAX_RESERVATIONS];
    int availableSuiteCount;
    int reservationCount;
    static int reservationCounter;
    string contactNumber;

    void loadSuitesFromFile() {
        ifstream file("suites.dat", ios::binary);
        if (!file) return;

        availableSuiteCount = 0;
        Suite suite;
        while (file.read(reinterpret_cast<char*>(&suite), sizeof(Suite))) {
            if (suite.isAvailable()) {
                if (availableSuiteCount < MAX_SUITES) {
                    availableSuites[availableSuiteCount++] = suite;
                } else {
                    cout << "Available suite limit reached!" << endl;
                }
            }
        }

        file.close();
    }

    void loadReservationsFromFile() {
        ifstream file("reservations.dat", ios::binary);
        if (!file) return;

        reservationCount = 0;
        Reservation reservation;
        while (file.read(reinterpret_cast<char*>(&reservation), sizeof(Reservation))) {
            if (reservation.getContactNumber() == contactNumber) {
                if (reservationCount < MAX_RESERVATIONS) {
                    reservations[reservationCount++] = reservation;
                } else {
                    cout << "Reservation limit reached!" << endl;
                }
            }
        }

        file.close();
    }

public:
    Guest(const string &contact) : contactNumber(contact), availableSuiteCount(0), reservationCount(0) {
        loadSuitesFromFile();
        loadReservationsFromFile();
    }

    void showAvailableSuites() const {
        for (int i = 0; i < availableSuiteCount; ++i) {
            availableSuites[i].showSuiteDetails();
            cout << "------------------" << endl;
        }
    }

    void reserveSuite() {
        int suiteNumber;
        string guestName;
        int nights;

        cout << "Enter suite number to reserve: ";
        cin >> suiteNumber;
        cout << "Enter your name: ";
        cin >> guestName;
        cout << "Enter duration of stay: ";
        cin >> nights;

        for (int i = 0; i < availableSuiteCount; ++i) {
            if (availableSuites[i].getSuiteNumber() == suiteNumber) {
                Reservation newReservation(++reservationCounter, suiteNumber, guestName, nights, contactNumber);
                if (reservationCount < MAX_RESERVATIONS) {
                    reservations[reservationCount++] = newReservation;
                } else {
                    cout << "Reservation limit reached!" << endl;
                }
                availableSuites[i].setAvailability(false);

                Invoice invoice(newReservation, availableSuites[i]);
                invoice.showInvoice();

                // Save the new reservation to the reservations.dat file
                ofstream file("reservations.dat", ios::binary | ios::app);
                file.write(reinterpret_cast<const char*>(&newReservation), sizeof(newReservation));
                file.close();

                cout << "Suite reserved successfully!" << endl;
                return;
            }
        }

        cout << "Suite not available!" << endl;
    }

    void showCurrentReservations() const {
        for (int i = 0; i < reservationCount; ++i) {
            reservations[i].showReservationDetails();
            cout << "------------------" << endl;
        }
    }

    void displayPendingPayments() const {
        for (int i = 0; i < reservationCount; ++i) {
            for (int j = 0; j < availableSuiteCount; ++j) {
                if (reservations[i].getSuiteNumber() == availableSuites[j].getSuiteNumber()) {
                    Invoice invoice(reservations[i], availableSuites[j]);
                    invoice.showInvoice();
                    break;
                }
            }
        }
    }
};

int Guest::reservationCounter = 0;

int main() {
    int profileType;
    cout << "Welcome to Hotel Management System\n";
    cout << "1. Guest\n2. Hotel Manager\nSelect your profile: ";
    cin >> profileType;

    if (profileType == 1) {
        string contactNumber;
        cout << "Enter your contact number: ";
        cin >> contactNumber;

        Guest guest(contactNumber);
        int action;
        do {
            cout << "1. View Available Suites\n2. Reserve a Suite\n3. View Current Reservations\n4. Show Pending Payments\n5. Exit\n";
            cin >> action;

            switch (action) {
            case 1:
                guest.showAvailableSuites();
                break;
            case 2:
                guest.reserveSuite();
                break;
            case 3:
                guest.showCurrentReservations();
                break;
            case 4:
                guest.displayPendingPayments();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid selection! Try again.\n";
                break;
            }
        } while (action != 5);
    } else if (profileType == 2) {
        HotelManager manager;
        string passkey;

        cout << "Enter passkey: ";
        cin >> passkey;

        if (manager.authenticate(passkey)) {
            int action;
            do {
                cout << "1. Add Suite\n2. Delete Suite\n3. Show Suites\n4. Oversee Reservations\n5. Exit\n";
                cin >> action;

                switch (action) {
                case 1:
                    manager.addSuite();
                    break;
                case 2:
                    manager.deleteSuite();
                    break;
                case 3:
                    manager.showSuites();
                    break;
                case 4:
                    manager.overseeReservations();
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid selection! Try again.\n";
                    break;
                }
            } while (action != 5);
        } else {
            cout << "Invalid passkey! Access denied.\n";
        }
    } else {
        cout << "Invalid profile type! Exiting...\n";
    }

    return 0;
}
