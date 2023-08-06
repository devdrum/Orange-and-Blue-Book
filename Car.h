#ifndef UNTITLED1_CAR_H
#define UNTITLED1_CAR_H

#include <iostream>

using namespace std;

class Car {
public:
    int year;
    string make;
    string model;
    int mile;
    string state;
    string city;
    int price;

    Car(int y, string mk, string md, int mi, string s, string c, int p);
};


#endif //UNTITLED1_CAR_H
