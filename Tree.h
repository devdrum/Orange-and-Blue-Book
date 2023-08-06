//
// Created by Heon on 8/4/2023.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include <iostream>
#include <vector>
#include <list>

#include "car.h"
#include "filter.h"

class Tree {
public:
    struct Node {
        Car* car;
        std::vector<Node*> children{nullptr};
        Node(Car* car): car(car) {}
    };
    Node* root;
    Tree(): root(nullptr){}
    void insert(int y, string mk, string md, int mi, string s, string c, int p);
    list<Car*> find(Filter* f);
    void findHelper(Filter* f, Node* node, int n, list<Car*>* l);
    Node* insertHelper(Car* car, Node* node, int n);
    int price(Filter* f);
};


#endif //UNTITLED1_TREE_H
