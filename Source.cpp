#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;
#include "Hash.h"

string GetRegion(string state);


int main() {

    int userYear;
    string userMake;
    string userModel;
    int userMileage;
    string userState;
    string userLocation;
    int carValue = 15000;



    // Ascii Art Title... courtesy of https://patorjk.com/software/taag/#p=display&f=Big%20Money-nw&t=Orange%20and%20Blue%20Book
    cout << "________                                                          .___ " << endl << "\\_____  \\____________    ____    ____   ____   _____    ____    __| _/ " << endl <<
        " /   |   \\_  __ \\__  \\  /    \\  / ___\\_/ __ \\  \\__  \\  /    \\  / __ |  " << endl << "/    |    \\  | \\\// __ \\|   |  \\/ /_/  >  ___/   / __ \\|   |  \\/ /_/ |  " << endl <<
        "\\_______  /__|  (____  /___|  /\\___  / \\___  > (____  /___|  /\\____ |  " << endl << "        \\/           \\/     \\\//_____/      \\/       \\/     \\/      \\/  " << endl <<
        "__________.__                  __________               __    " << endl << "\\______   \\  |  __ __   ____   \\______   \\ ____   ____ |  | __" << endl <<
        " |    |  _/  | |  |  \\_/ __ \\   |    |  _\//  _ \\ /  _ \\|  |/ /" << endl << " |    |   \\  |_|  |  /\\  ___/   |    |   (  <_> |  <_> )    < " << endl <<
        " |______  /____/____/  \\___  >  |______  /\\____/ \\____/|__|_ \\" << endl << "        \\/                 \\/          \\/                   \\/ " << endl << endl << endl;

    // Main Input - Let's collect the user's vehicle information to lookup
    cout << "Welcome to the Orange and Blue Book" << endl << endl << "Please enter your vehicle information" << endl << endl << "Vehicle Year (yyyy): ";
    cin >> userYear;
    cout << endl << "Vehicle Make: ";
    cin >> userMake;
    cout << endl << "Vehicle Model: ";
    cin >> userModel;
    cout << endl << "Vehicle Mileage: ";
    cin >> userMileage;
    cout << endl << "What state are you in (abbreviated e.g. FL): ";
    cin >> userState;
    cout << endl;

    userLocation = GetRegion(userState);

    //cout << userYear << " " << userMake << " " << userModel << " " << userMileage << " " << userState << " " << userLocation << endl;

    cout << "Your estimated value: " << carValue << endl;

    //Car car(2010, "Hyundai", "Veloster", 20000, "FL", "Gainesville", 10000);
    //Hash hash;
    //hash.insert(&car);
    //list<Car*> l = hash.find(2010, "Hyundai", "Veloster", 20000, "FL", "Gainesville");
    //Car l1 = **(l.begin());
    //cout << l1.model << ", " << l1.make << ", " << l1.year << ", " << l1.state << ", " << l1.city << ", " << l1.mileage << ", " << l1.price << endl;
    //return 0;

    string line;				// Tracker for current line of commands from CSV input

    Hash hash(100000); // Create a hash object to store vehicle data from CSV - DATA STRUCTURE 1

    ifstream read("true_car_listings.csv"); // Import CSV file insto input stream

    // The first line will contain the headers of the CSV, discard this

    getline(read, line);
    // cout << line << endl;


    // Iterate through each subsequent line until we reach the EOF
    while (!read.eof())
    {
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
        getline(read, line, ',');
        vin = line;
        getline(read, line, ',');
        make = line;
        getline(read, line);
        model = line;
        region = GetRegion(state);


        //cout << price << " " << year << " " << mileage << " " << city << " " << state << " " << vin << " " << make << " " << model << " " << region << endl;

        //hash.insert(stoi(year), make, model, stoi(mileage), state, city, stoi(price));

    }

}

string GetRegion(string state) // Convert state to region.
{
    vector<string> listOfSouthEastStates = { "WV", "VA", "KY", "TN", "NC", "SC", "GA", "AL", "MS", "AR", "LA", "FL" };
    vector<string> listOfNorthEastStates = { "ME", "MA", "RI", "CT", "NH", "VT", "NY", "PA", "NJ", "DE", "MD" };
    vector<string> listOfMidWestStates = { "OH", "IN", "MI", "IL", "MO", "WI", "MN", "IA", "KS", "NE", "SD", "ND" };
    vector<string> listOfSouthWestStates = { "TX", "OK", "NM", "AZ" };
    vector<string> listOfWestStates = { "CO", "WY", "MT", "ID", "WA", "OR", "UT", "NV", "CA", "AK", "HI" };



    if (find(listOfSouthEastStates.begin(), listOfSouthEastStates.end(), state) != listOfSouthEastStates.end())
        return "SouthEast";
    else if ((find(begin(listOfNorthEastStates), end(listOfNorthEastStates), state) != end(listOfNorthEastStates)))
        return "NorthEast";
    else if ((find(begin(listOfMidWestStates), end(listOfMidWestStates), state) != end(listOfMidWestStates)))
        return "MidWest";
    else if ((find(begin(listOfSouthWestStates), end(listOfSouthWestStates), state) != end(listOfSouthWestStates)))
        return "SouthWest";
    else
        return "West";
}
