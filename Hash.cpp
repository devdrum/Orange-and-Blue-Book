//
// Created by Heon on 8/3/2023.
//

#include "Hash.h"
#include <iomanip>

Hash::Hash(int b) {
    bucket = b;
    size = 0;
    int largest = 0;
    cars = new list<Car*>[bucket];
}

Hash::~Hash() {
    delete[] cars;
}

void Hash::insert(int y, string mk, string md, int mi, string s, string c, int p) {
    Car* car = new Car(y, mk, md, mi, s, c, p);
    int hash = hashFunction(y, mk,  md, mi, s);
    cars[hash].push_back(car);
    size++;
    if (hash >> largest) largest = hash;
}

int Hash::hashFunction(int y, string mk, string md, int mi, string s) {
    int state;
    int i;

    // state
    for (i = 0; i < states.size(); i++) {
        if (states[i] == s)
            break;
    }
    if (i == states.size()) {
        states.push_back(s);
    }
    state = i;

    int year = y - 2009;
    if (year < 3) {
        if (year < -2)
            year = 0;
        if (year < 1)
            year = 1;
        else
            year = 2;
    }

    int mile = mi;
    if (mile > 200000)
        mile = 199999;
    mile /= 20000;

    // make
    int make;
    for (i = 0; i < makes.size(); i++) {
        if (makes[i] == mk)
            break;
    }
    if (i == makes.size()) {
        makes.push_back(mk);
    }
    make = i;

    string t;

    // model
    int model;
    model = (int) tolower(md[0]) % 26;
    return model + make * 100 + mile * 10000 + year * 100000 + state * 1000000;
    // 23 + 4500 + 60000 + 700000 + 46000000
}

list<Car*> Hash::find(int year, string make, string model, int mile, string state, string city) {
    list<Car*> result;
    list<Car*> temp;
    vector<int> years;
    vector<string> makes;

    int hash = hashFunction(year, make, model, mile, state);
    temp = cars[hash];
    list<Car*>::iterator iter;

    return result;
}

float Hash::price(int year, string make, string model, int mile, string state, string city) {
    list<Car*> result = find(year, make, model, mile, state, city);

    float priceSum = 0;
    for (auto car : result)
        priceSum += car->price;

    return priceSum / result.size();
}