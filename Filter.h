#ifndef UNTITLED1_FILTER_H
#define UNTITLED1_FILTER_H

#include <iostream>

#include "Car.h"

using namespace std;

class Filter {
public:
    int year;
    string make;
    string model;
    int mile;
    string state;
    string city;
    Filter(int y = 0, string mk = 0, string md = 0, int mi = 0, string s = 0, string c = 0);
    bool Compare(Car* c);
};


#endif //UNTITLED1_FILTER_H
