#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <limits>
#include <vector>

using namespace std;

struct User{
    string username;
    string password;
};

struct Car {
    string carID;
    string model;
    int capacity;
    double rentalCharge;
    bool isAvailable;
};

struct Driver {
    string driverID;
    string name;
    string contact;
    bool isAvailable;
};

struct Passenger {
    string name;
    string contact;
};

struct Booking {
    string carID;
    string passengerName;
    string passengerContact;
    double rentalCharge;
    string bookingDate;
    string driverID;
};

const int MAX_CARS = 100;
const int MAX_DRIVERS = 100;
const int MAX_BOOKINGS = 100;

Car cars[MAX_CARS];
Driver drivers[MAX_DRIVERS];
Booking bookings[MAX_BOOKINGS];

int carCount = 0, driverCount = 0, bookingCount = 0;

vector<User> users; // Vector to hold registered users
string currentPassengerContact;

bool authenticateUser (const string &role) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (role == "admin") {
        return (username == "admin" && password == "admin123");
    } else if (role == "passenger") {
        // Check if the user exists in the users vector
        for (const auto &user : users) {
            if (user.username == username && user.password == password) {
                currentPassengerContact = username; // Set the current passenger
                return true;
            }
        }
        return false;
    }
    return false;
}

void loadUsersFromFile() {
    ifstream file("users.txt");
    if (!file) {
        cout << "No user data found. Starting with an empty list.\n";
        return;
    }
    User user;
    while (file >> user.username >> user.password) {
        users.push_back(user);
    }
}

void saveUsersToFile() {
    ofstream file("users.txt");
    if (!file) {
        cout << "Error opening file for writing user data.\n";
        return;
    }
    for (const auto &user : users) {
        file << user.username << " " << user.password << "\n";
    }
}

void registerUser () {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;

    // Check if username already exists
    for (const auto &user : users) {
        if (user.username == username) {
            cout << "Username already taken. Please choose a different username.\n";
            return;
        }
    }

    cout << "Enter a password: ";
    cin >> password;

    // Add new user to the vector
    users.push_back({username, password});
    saveUsersToFile();
    cout << "Registration successful! You can now log in.\n";
}

void viewUsers() {
    cout << left << setw(20) << "Username" << setw(20) << "Password" << endl;
    cout << string(40, '-') << endl;
    for (const auto &user : users) {
        cout << left << setw(20) << user.username << setw(20) << user.password << endl;
    }
}

void saveCarsToFile() {
    ofstream file("cars.txt");
    if (!file) {
        cout << "Error opening file for writing car data.\n";
        return;
    }
    for (int i = 0; i < carCount; i++) {
        file << cars[i].carID << " "
             << cars[i].model << " "
             << cars[i].capacity << " "
             << cars[i].rentalCharge << " "
             << cars[i].isAvailable << "\n";
    }
}

void loadCarsFromFile() {
    ifstream file("cars.txt");
    if (!file) {
        cout << "No car data found. Starting with an empty list.\n";
        return;
    }
    carCount = 0;
    while (file >> cars[carCount].carID >> cars[carCount].model 
                >> cars[carCount].capacity >> cars[carCount].rentalCharge 
                >> cars[carCount].isAvailable) {
        carCount++;
    }
}

void saveDriversToFile() {
    ofstream file("drivers.txt");
    if (!file) {
        cout << "Error opening file for writing driver data.\n";
        return;
    }
    for (int i = 0; i < driverCount; i++) {
        file << drivers[i].driverID << " "
             << drivers[i].name << " "
             << drivers[i].contact << " "
             << drivers[i].isAvailable << "\n";
    }
}

void loadDriversFromFile() {
    ifstream file("drivers.txt");
    if (!file) {
        cout << "No driver data found. Starting with an empty list.\n";
        return;
    }
    driverCount = 0;
    while (file >> drivers[driverCount].driverID >> drivers[driverCount].name 
                >> drivers[driverCount].contact >> drivers[driverCount].isAvailable) {
        driverCount++;
    }
}

void saveBookingsToFile() {
   ofstream file("bookings.txt");
    if (!file) {
        cout << "Error opening file for writing booking data.\n";
        return;
    }
    for (int i = 0; i < bookingCount; i++) {
        file << bookings[i].carID << " "
             << bookings[i].passengerName << " "
             << bookings[i].passengerContact << " "
             << bookings[i].rentalCharge << " "
             << bookings[i].bookingDate << " "
             << bookings[i].driverID << "\n";
    }
}

void loadBookingsFromFile() {
    ifstream file("bookings.txt");
    if (!file) {
        cout << "No booking data found. Starting with an empty list.\n";
        return;
    }
    bookingCount = 0;
    while (file >> bookings[bookingCount].carID >> bookings[bookingCount].passengerName 
                >> bookings[bookingCount].passengerContact >> bookings[bookingCount].rentalCharge 
                >> bookings[bookingCount].bookingDate >> bookings[bookingCount].driverID) {
        bookingCount++;
    }
}

bool isValidMobileNumber(const string &number) {
    if (number.length() != 10) return false;
    for (char c : number) {
        if (!isdigit(c)) return false;
    }
    return true;
}

//-----------------------Add new car-----------------------
void addCar() {
    if (carCount >= MAX_CARS) {
        cout << "Car limit reached. Cannot add more cars.\n";
        return;
    }

    string newCarID;
    while (true) {
        cout << "Enter Car ID: ";
        cin >> newCarID;
        bool idExists = false;
        for (int i = 0; i < carCount; i++) {
            if (cars[i].carID == newCarID) {
                idExists = true;
                break;
            }
        }

        if (idExists) {
            cout << "Entered Car ID is already taken. Please enter a new Car ID.\n";
        } else {
            cars[carCount].carID = newCarID;
            break;
        }
    }
    cout << "Enter Car Model: ";
    cin.ignore();
    getline(cin, cars[carCount].model);
    
    cout << "Enter Capacity: ";
    while (!(cin >> cars[carCount].capacity) || cars[carCount].capacity <= 0) {
        cout << "Invalid input. Please enter a positive integer for capacity: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter Rental Charge: ";
    while (!(cin >> cars[carCount].rentalCharge) || cars[carCount].rentalCharge < 0) {
        cout << "Invalid input. Please enter a non-negative number for rental charge: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cars[carCount].isAvailable = true;
    carCount++;
    saveCarsToFile();
    cout << "Car added successfully!\n";
}
//-----------------------Display cars in table form-----------------------
void viewCars() {
    cout << left << setw(15) << "Car ID" 
         << setw(20) << "Model" 
         << setw(10) << "Capacity" 
         << setw(15) << "Rental Charge" 
         << setw(10) << "Available" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < carCount; i++) {
        cout << left << setw(15) << cars[i].carID
             << setw(20) << cars[i].model
             << setw(10) << cars[i].capacity
             << setw(15) << fixed << setprecision(2) << cars[i].rentalCharge
             << setw(10) << (cars[i].isAvailable ? "Yes" : "No") << endl;
    }
}
//-----------------------Remove car based on car id-----------------------
void removeCar() {
    viewCars();
    string carID;
    cout << "Enter Car ID to remove: ";
    cin >> carID;
    for (int i = 0; i < carCount; i++) {
        if (cars[i].carID == carID) {
            for (int j = i; j < carCount - 1; j++) {
                cars [j] = cars[j + 1];
            }
            carCount--;
            saveCarsToFile();
            cout << "Car removed successfully!\n";
            return;
        }
    }
    cout << "Car not found!\n";
}
//-----------------------Add new driver-----------------------
void addDriver() {
    if (driverCount >= MAX_DRIVERS) {
        cout << "Driver limit reached. Cannot add more drivers.\n";
        return;
    }

    string newDriverID;
    while (true) {
        cout << "Enter Driver ID: ";
        cin >> newDriverID;
        bool idExists = false;
        for (int i = 0; i < driverCount; i++) {
            if (drivers[i].driverID == newDriverID) {
                idExists = true;
                break;
            }
        }
        if (idExists) {
            cout << "Entered Driver ID is already taken. Please enter a new Driver ID.\n";
        } else {
            drivers[driverCount].driverID = newDriverID;
            break;
        }
    }

    cout << "Enter Driver Name: ";
    cin.ignore();
    getline(cin, drivers[driverCount].name);
    
    cout << "Enter Driver Contact (10 digits): ";
    string contact;
    cin >> contact;
    while (!isValidMobileNumber(contact)) {
        cout << "Invalid input. Please enter a valid 10-digit mobile number: ";
        cin >> contact;
    }
    drivers[driverCount].contact = contact;
    drivers[driverCount].isAvailable = true;
    driverCount++;
    saveDriversToFile();
    cout << "Driver added successfully!\n";
}

//-----------------------View driver in table form-----------------------
void viewDrivers() {
    cout << left << setw(15) << "Driver ID" 
         << setw(20) << "Name" 
         << setw(15) << "Contact" 
         << setw(10) << "Available" << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < driverCount; i++) {
        cout << left << setw(15) << drivers[i].driverID
             << setw(20) << drivers[i].name
             << setw(15) << drivers[i].contact
             << setw(10) << (drivers[i].isAvailable ? "Yes" : "No") << endl;
    }
}
//-----------------------Remove driver from list-----------------------

void removeDriver() {
    viewDrivers();
    string driverID;    
    cout << "Enter Driver ID to remove: ";
    cin >> driverID;
    for (int i = 0; i < driverCount; i++) {
        if (drivers[i].driverID == driverID) {
            for (int j = i; j < driverCount - 1; j++) {
                drivers[j] = drivers[j + 1];
            }
            driverCount--;
            saveDriversToFile();
            cout << "Driver removed successfully!\n";
            return;
        }
    }
    cout << "Driver not found!\n";
}

//-----------------------View bookings in tabular form-----------------------
void viewBookings() {
    cout << left << setw(15) << "Car ID" 
         << setw(20) << "Passenger Name" 
         << setw(15) << "Contact" 
         << setw(15) << "Rental Charge" 
         << setw(15) << "Booking Date" 
         << setw(15) << "Driver ID" << endl;
    cout << string(100, '-') << endl;
    for (int i = 0; i < bookingCount; i++) {
        cout << left << setw(15) << bookings[i].carID
             << setw(20) << bookings[i].passengerName
             << setw(15) << bookings[i].passengerContact
             << setw(15) << fixed << setprecision(2) << bookings[i].rentalCharge
             << setw(15) << bookings[i].bookingDate
             << setw(15) << bookings[i].driverID << endl;
    }
}

//-----------------------Search car according to user needs-----------------------
void searchCar() {
    int capacity;
    double maxCharge;

    cout << "Enter required capacity: ";
    while (!(cin >> capacity) || capacity <= 0) {
        cout << "Invalid input. Please enter a positive integer for capacity: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter maximum rental charge: ";
    while (!(cin >> maxCharge) || maxCharge < 0) {
        cout << "Invalid input. Please enter a non-negative number for maximum rental charge: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << left << setw(15) << "Car ID" 
         << setw(20) << "Model" 
         << setw(10) << "Capacity" 
         << setw(15) << "Rental Charge" 
         << setw(10) << "Available" << endl;
    cout << string(70, '-') << endl;
    bool found = false;
    for (int i = 0; i < carCount; i++) {
        if (cars[i].capacity >= capacity && cars[i].rentalCharge <= maxCharge && cars[i].isAvailable) {
            cout << left << setw(15) << cars[i].carID
                 << setw(20) << cars[i].model
                 << setw(10) << cars[i].capacity
                 << setw(15) << fixed << setprecision(2) << cars[i].rentalCharge
                 << setw(10) << (cars[i].isAvailable ? "Yes" : "No") << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Sorry!!! We have no cars available as per your requirements.\n";
    }
}

//-----------------------Validation of date-----------------------
bool isValidDate(const string &date) {
    if (date.size() != 10 || date[2] != '-' || date[5] != '-') {
        return false;
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) {
            return false;
        }
    }
    time_t t = time(0);
    tm *now = localtime(&t);
    int currentDay = now->tm_mday;
    int currentMonth = now->tm_mon + 1;
    int currentYear = now->tm_year + 1900;

    if (year < currentYear || 
        (year == currentYear && month < currentMonth) || 
        (year == currentYear && month == currentMonth && day < currentDay)) {
        return false;
    }
    return true;
}

//-----------------------Book a car-----------------------
void bookCar() {
    string carID, bookingDate;
    Passenger passenger;
    char withDriver;
    viewCars();
    cout<< "------------------------------------" << endl;
    cout << "Enter Car ID to book: ";
    cin >> carID;

    for (int i = 0; i < carCount; i++) {
        if (cars[i].carID == carID && cars[i].isAvailable) {
            cout << "Enter Passenger Name: ";
            cin.ignore();
            getline(cin, passenger.name);
            cout << "Enter Passenger Contact (10 digits): ";
            string contact;
            cin >> contact;
            while (!isValidMobileNumber(contact)) {
                cout << "Invalid input. Please enter a valid 10-digit mobile number: ";
                cin >> contact;
            }
            passenger.contact = contact;
            currentPassengerContact = passenger.contact;
            while (true) {
                cout << "Enter Booking Date (DD-MM-YYYY): ";
                cin >> bookingDate;

                if (isValidDate(bookingDate)) {
                    break; 
                } else {
                    cout << "Entered date is not valid. Please enter current or upcoming date in DD-MM-YYYY format.\n";
                }
            }
            cout << "Do you want to book car with a driver? (y/n): ";
            cin >> withDriver;
            string assignedDriverID = "";
            if (withDriver == 'y' || withDriver == 'Y') {
                bool driverAvailable = false;
                for (int j = 0; j < driverCount; j++) {
                    if (drivers[j].isAvailable) {
                        assignedDriverID = drivers[j].driverID;
                        drivers[j].isAvailable = false;
                        driverAvailable = true;
                        break;
                    }
                }
                if (!driverAvailable) {
                    cout<< "------------------------------------" << endl;
                    cout << "Sorry, car cannot be booked. Driver is not available for this car right now.\n";
                    return;
                }
            }
            bookings[bookingCount++] = {carID, passenger.name, passenger.contact, cars[i].rentalCharge, bookingDate, assignedDriverID};
            cars[i].isAvailable = false;

            saveBookingsToFile();
            saveCarsToFile();
            saveDriversToFile();
            cout<< "------------------------------------" << endl;
            cout << "Car booked successfully! ";
            if (!assignedDriverID.empty()) {
                cout << "Driver assigned: " << assignedDriverID << endl;
            } else {
                cout << "Car booked successfully without a driver.\n";
            }
            return;
        }
    }
    cout<< "------------------------------------" << endl;
    cout << "Car not available for booking!\n";
}

//-----------------------View invoice of booked car-----------------------
void viewInvoice() {
    bool found = false;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].passengerContact == currentPassengerContact) {
            cout << "------------------------------------" << endl;
            cout << "Booking Invoice:\n";
            cout << "Car ID: " << bookings[i].carID << endl;
            cout << "Passenger Name: " << bookings[i].passengerName << endl;
            cout << "Passenger Contact: " << bookings[i].passengerContact << endl;
            cout << "Rental Charge: " << fixed << setprecision(2) << bookings[i].rentalCharge << endl;
            cout << "Booking Date: " << bookings[i].bookingDate << endl;
            for (int j = 0; j < driverCount; j++) {
                if (drivers[j].driverID == bookings[i].driverID) {
                    cout << "Driver Name: " << drivers[j].name << endl;
                    cout << "Driver Contact: " << drivers[j].contact << endl;
                    break;
                }
            }
            found = true; // Set the flag to true if an invoice is found
        }
    }
    if (!found) {
        cout << "No invoices found for the current user.\n";
    }
}

//-----------------------Cancel a booked car-----------------------
void cancelBooking() {
    string carID, passengerContact;
    viewCars();
    cout << "Enter Car ID to cancel booking: ";
    cin >> carID;
    cout << "Enter your contact number: ";
    cin >> passengerContact;

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].carID == carID && bookings[i].passengerContact == passengerContact) {
            for (int j = 0; j < carCount; j++) {
                if (cars[j].carID == carID) {
                    cars[j].isAvailable = true;
                    break;
                }
            }
        if (!bookings[i].driverID.empty()) {
            for (int j = 0; j < driverCount; j++) {
                if (drivers[j].driverID == bookings[i].driverID) {
                    drivers[j].isAvailable = true;
                    break;
                }
            }
        }
            cout << "Booking canceled successfully! Money refunded for Car ID: " << carID << endl;

            for (int j = i; j < bookingCount - 1; j++) {
                bookings[j] = bookings[j + 1];
            }
            bookingCount--;
            saveBookingsToFile();
            saveCarsToFile();
            saveDriversToFile();
            return;
        }
    }
    cout << "Booking not found!\n";
}
//-----------------------Main function-----------------------
int main() {
    loadCarsFromFile();
    loadDriversFromFile();
    loadBookingsFromFile();
    loadUsersFromFile(); // Load users from file

    int choice;

    while (true) {
        cout << "\n                             ---------------------------------- HIRE CARS MANAGEMENT SYSTEM ----------------------------------" << endl;
        cout << "1. Admin Login\n2. Passenger Login\n3. Exit\nEnter choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input! Please enter a valid number (1, 2, or 3): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (choice == 1) {
            if (!authenticateUser ("admin")) {
                cout << "Invalid credentials!\n";
                continue;
            }

            while (true) {
                cout << "------------------------------------";
                cout << "\n1. Add Car\n2. Remove Car\n3. Add Driver\n4. Remove Driver\n5. View Cars\n6. View Drivers\n7. View Bookings\n8. View Users\n9. Logout\n";
                cout << "------------------------------------" << endl;
                cout << "Enter choice: ";
                while (!(cin >> choice)) {
                    cout << "Invalid input! Please enter a valid number (1-9): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (choice == 1) addCar();
                else if (choice == 2) removeCar();
                else if (choice == 3) addDriver();
                else if (choice == 4) removeDriver();
                else if (choice == 5) viewCars();
                else if (choice == 6) viewDrivers();
                else if (choice == 7) viewBookings();
                else if (choice == 8) viewUsers(); // View registered users
                else if (choice == 9) break;
                else cout << "Invalid choice !\n";
            }
        } else if (choice == 2) {
            cout << "1. Login\n2. Register\nEnter choice: ";
            int passengerChoice;
            cin >> passengerChoice;

            if (passengerChoice == 1) {
                if (!authenticateUser ("passenger")) {
                    cout << "Profile not found. You have to register first.\n";
                    continue;
                }
                while (true) {
                    cout << "------------------------------------";
                    cout << "\n1. View Cars\n2. View Drivers\n3. Search Car\n4. Book Car\n5. View Invoice\n6. Cancel Booking\n7. Logout\n";
                    cout << "------------------------------------" << endl;
                    cout << "Enter choice: ";
                    while (!(cin >> choice)) {
                        cout << "Invalid input! Please enter a valid number (1-7): ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    if (choice == 1) viewCars();
                    else if (choice == 2) viewDrivers();
                    else if (choice == 3) searchCar();
                    else if (choice == 4) bookCar();
                    else if (choice == 5) viewInvoice();
                    else if (choice == 6) cancelBooking();
                    else if (choice == 7) break;
                    else cout << "Invalid choice!\n";
                }
            } else if (passengerChoice == 2) {
                registerUser (); // Call the registration function
            } else {
                cout << "Invalid choice!\n";
            }
        } else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}