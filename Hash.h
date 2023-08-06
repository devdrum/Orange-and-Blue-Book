//
// Created by Heon on 8/3/2023.
//

#ifndef UNTITLED1_HASH_H
#define UNTITLED1_HASH_H

#include "Car.h"
#include <vector>
#include <list>
#include <string>
#include <iterator>

class Hash {
    int bucket;
    unsigned int size;
    list<Car*> *cars;
    vector<string> states;
    vector<string> makes;
public:
    int largest;
    Hash(int b = 70000000);
    ~Hash();
    void insert(int y, string mk, string md, int mi, string s, string c, int p);
    int hashFunction(int y, string mk, string md, int mi, string s);
    list<Car*> find(int year = 0, string make = 0, string model = 0, int mile = 0, string state = 0, string city = 0);
    float price(int year = 0, string make = 0, string model = 0, int mile = 0, string state = 0, string city = 0);
    unsigned int getSize();
};


#endif //UNTITLED1_HASH_H
