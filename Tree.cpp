#include "Tree.h"

Tree::Node* Tree::insertHelper(Car* car, Node* node, int n) {
    if (node == nullptr){
        Node* temp = new Node(car);
        node = temp;
        return node;
    }
    int i;
    vector<Node*>* children = &node->children;
    switch (n) {
        case 0:
            if (car->state == node->car->state) i = 0;
            else
                for (i = 1; i < children->size(); i++)
                    if(car->state == children->at(i)->car->state)
                        break;
            break;
        case 1:
            if (car->make == node->car->make) i = 0;
            else
                for (i = 1; i < children->size(); i++)
                    if(car->make == children->at(i)->car->make)
                        break;
            break;
        case 2:
            if (car->model == node->car->model) i = 0;
            else
                for (i = 1; i < children->size(); i++)
                    if(car->model == children->at(i)->car->model)
                        break;
            break;
        case 3:
            if (car->year == node->car->year) i = 0;
            else
                for (i = 1; i < children->size(); i++)
                    if(car->year == children->at(i)->car->year)
                        break;
            break;
        case 4:
            if (car->city == node->car->city) i = 0;
            else
                for (i = 1; i < children->size(); i++)
                    if(car->city == children->at(i)->car->city)
                        break;
            break;
        case 5:
            if (car->mile == node->car->mile) i = 0;
            else
                for (i = 1; i < children->size(); i++)
                    if(car->mile == children->at(i)->car->mile)
                        break;
            break;
    }
    if (i < children->size()) {
        children->at(i) = insertHelper(car, children->at(i), n+1);
    }
    else {
        Node* temp = new Node(car);
        children->push_back(temp);
    }
    return node;
}
void Tree::insert(int y, string mk, string md, int mi, string s, string c, int p) {
    Car* car = new Car(y, mk, md, mi, s, c, p);
    root = insertHelper(car, root, 0);
}

void Tree::findHelper(Filter* f, Tree::Node *node, int n, list<Car*>* l) {
    if (node == nullptr){
        return;
    }
    Car* car = node->car;
    if (f->Compare(car)) {
        l->push_back(car);
        return;
    }
    int i;
    vector<Node*> children = node->children;
    switch (n) {
        case 0:
            if (f->state != node->car->state) {
                for (i = 0; i < children.size(); i++) {
                    if (children[i]->car->state == f->state) {
                        findHelper(f, children[i], 1, l);
                        return;
                    }
                }
            }
            break;
        case 1:
            if (f->make != node->car->make) {
                for (i = 0; i < children.size(); i++) {
                    if (children[i]->car->make == f->make) {
                        findHelper(f, children[i], 2, l);
                        return;
                    }
                }
            }
            break;
        case 2:
            if (f->model != node->car->model) {
                for (i = 0; i < children.size(); i++) {
                    if (children[i]->car->model == f->model) {
                        findHelper(f, children[i], 3, l);
                        return;
                    }
                }
            }
            break;
        case 3:
            if (f->year != node->car->year) {
                for (i = 0; i < children.size(); i++) {
                    if (children[i]->car->year == f->year) {
                        findHelper(f, children[i], 3, l);
                        return;
                    }
                }
            }
            break;
        case 4:
            if (f->city != node->car->city) {
                for (i = 0; i < children.size(); i++) {
                    if (children[i]->car->city == f->city) {
                        findHelper(f, children[i], 3, l);
                        return;
                    }
                }
            }
            break;
        case 5:
            if (f->mile != node->car->mile) {
                for (i = 0; i < children.size(); i++) {
                    if (children[i]->car->mile == f->mile) {
                        findHelper(f, children[i], 3, l);
                        return;
                    }
                }
            }
    }
}

list<Car*> Tree::find(Filter *f) {
    list<Car*> l;
    findHelper(f, root, 0, &l);
    return l;
}

int Tree::price(Filter *f) {
    list<Car*> result = find(f);
    cout << result.size() << " " << endl;

    float priceSum = 0;
    for (auto car : result)
        priceSum += car->price;

    return priceSum / result.size();
}