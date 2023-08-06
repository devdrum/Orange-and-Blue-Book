#include "Filter.h"

bool Filter::Compare(Car *c) {
    return c->state == state
        && c->city == city
        && c->make == make
        && c->model == model
        && c->mile == mile
        && c->year == year;
}

Filter::Filter(int y, string mk, string md, int mi, string s, string c) {
    year = y;
    make = mk;
    model = md;
    mile = mi;
    state = s;
    city = c;
}
