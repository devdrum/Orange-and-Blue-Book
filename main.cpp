#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <chrono>

#include "Hash.h"
#include "Tree.h"

using namespace std;
using namespace std::chrono;

void Read(Hash &hash, Tree &tree);
// string GetRegion(string state);

int main() {

    Hash hash; // Create a hash object to store vehicle data - DATA STRUCTURE 1
    Tree tree; // Create a tree object to store vehicle data - DATA STRUCTURE 2

    Read(hash, tree);
    int userYear = 1900;
    string userMake;
    string userModel;
    int userMileage = 0;
    string userState;
    string userLocation;
    string userCity;
    int carValue = 0;
    int dataStructureSelection = 0;

    // Ascii Art Title... courtesy of https://patorjk.com/software/taag/#p=display&f=Big%20Money-nw&t=Orange%20and%20Blue%20Book
    cout << "________                                                          .___ " << endl
         << "\\_____  \\____________    ____    ____   ____   _____    ____    __| _/ " << endl <<
         " /   |   \\_  __ \\__  \\  /    \\  / ___\\_/ __ \\  \\__  \\  /    \\  / __ |  " << endl
         << "/    |    \\  | \\\// __ \\|   |  \\/ /_/  >  ___/   / __ \\|   |  \\/ /_/ |  " << endl <<
         "\\_______  /__|  (____  /___|  /\\___  / \\___  > (____  /___|  /\\____ |  " << endl
         << "        \\/           \\/     \\\//_____/      \\/       \\/     \\/      \\/  " << endl <<
         "__________.__                  __________               __    " << endl
         << "\\______   \\  |  __ __   ____   \\______   \\ ____   ____ |  | __" << endl <<
         " |    |  _/  | |  |  \\_/ __ \\   |    |  _\//  _ \\ /  _ \\|  |/ /" << endl
         << " |    |   \\  |_|  |  /\\  ___/   |    |   (  <_> |  <_> )    < " << endl <<
         " |______  /____/____/  \\___  >  |______  /\\____/ \\____/|__|_ \\" << endl
         << "        \\/                 \\/          \\/                   \\/ " << endl << endl << endl;

    // Main Input - Let's collect the user's vehicle information to lookup
    int errorState = 1;

    while (errorState != 0)
    {
        errorState = 0;

        cout << "Welcome to the Orange and Blue Book" << endl << endl << "Please select a data strcuture and enter your vehicle information" << endl << endl << "Select Data Strcuture (1 = hashtable, 2 = N-Ary Tree): ";
        cin >> dataStructureSelection;
        cout << endl << "Vehicle Year (yyyy): ";
        cin >> userYear;
        cout << endl << "Vehicle Make: ";
        cin >> userMake;
        cout << endl << "Vehicle Model: ";
        cin >> userModel;
        cout << endl << "Vehicle Mileage: ";
        cin >> userMileage;
        cout << endl << "What state are you in (abbreviated e.g. FL): ";
        cin >> userState;
        cout << endl << "What city are you in: ";
        char st[40];
        cin.ignore();
        cin.getline(st, 40);
        userCity = st;


        if (dataStructureSelection != 1 && dataStructureSelection != 2){
            errorState = 1;
            cout << "Invalid entry for Data Structure Selection" << endl;
        }
        if (userYear < 0 || userYear > 2020){
            errorState = 1;
            cout << "Invalid entry for Year" << endl;
        }

        if (userMake == ""){
            errorState = 1;
            cout << "Invalid entry for Make" << endl;
        }
        if (userModel == ""){
            errorState = 1;
            cout << "Invalid entry for Model" << endl;
        }
        if (userMileage < 0 || userMileage > 9999999){
            errorState = 1;
            cout << "Invalid entry for Mileage" << endl;
        }
        if (userState == ""){
            errorState = 1;
            cout << "Invalid entry for State" << endl;
        }
        if (userCity == ""){
            errorState = 1;
            cout << "Invalid entry for City" << endl;
        }
        if (errorState == 1)
            cout << "Please re-input your selections" << endl;

        // userLocation = GetRegion(userState); // Not currently being used

    }

    auto start = high_resolution_clock::now(); // Let's start a chrono timer - https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now

    // Let's find our price based on which structure was chosen
    if (dataStructureSelection == 1)
    {
        // HashTable GetAverage
        carValue = hash.price(userYear, userMake, userModel, userMileage, userState, userCity);
    }
    else if (dataStructureSelection == 2)
    {
        // N-Ary/RedBlack GetAverage
        Filter filter(userYear, userMake, userModel, userMileage, userState, userCity);
        carValue = tree.price(&filter);
    }

    auto stop = high_resolution_clock::now(); // Stop the timer
    auto duration = duration_cast<microseconds>(stop - start); // Calculate runtime for lookup

    cout << "Your estimated value: " << carValue << endl << "Time Elapsed: " << duration.count() << endl; // Display results
}

void Read(Hash &hash, Tree &tree) {
    string line;                // Tracker for current line of commands from CSV input

    ifstream read("true_car_listings.csv"); // Import CSV file insto input stream

    // The first line will contain the headers of the CSV, discard this

    getline(read, line);
    // cout << line << endl;
    int iterations = 0;
    auto start = high_resolution_clock::now(); // Let's start a chrono timer - https://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
    // Iterate through each subsequent line until we reach the EOF
    while (!read.eof()) {
        // Temporary variables to build objects, and insert our data into the structures
        string price;
        string year;
        string mileage;
        string city;
        string state;
        string vin;
        string make;
        string model;
        string region;

        getline(read, line, ',');
        price = line;
        getline(read, line, ',');
        year = line;
        getline(read, line, ',');
        mileage = line;
        getline(read, line, ',');
        city = line;
        getline(read, line, ',');
        state = line;
        state.erase(0, 1);
        for (char &c: state) c = toupper(c);
        getline(read, line, ',');
        vin = line;
        getline(read, line, ',');
        make = line;
        getline(read, line);
        model = line;
        // insert data
        try {
            hash.insert(stoi(year), make, model, stoi(mileage), state, city, stoi(price));
            tree.insert(stoi(year), make, model, stoi(mileage), state, city, stoi(price));
        } catch (const std::runtime_error &re) {
            cout << iterations << ". Error: " << re.what() << endl;
            cout << price << " " << year << " " << mileage << " " << city << " " << state << " " << vin << " "
                 << make
                 << " " << model << endl;
        } catch (const std::exception &ex) {
            cout << iterations << ". Error: " << ex.what() << endl;
            cout << "Wrong input: " << price << " " << year << " " << mileage << " " << city << " " << state << " "
                 << vin << " " << make << " " << model << endl;
        }
    }
    read.close();
    read.clear();
}
