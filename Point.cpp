#include "Point.h"
#include <sstream>
using namespace std;

Point::Point(int id, const string& s) : pointId(id), clusterId(-1) {
    stringstream ss(s);
    int value;
    while (ss >> value) {
        values.push_back(value);
    }
}

int Point::dimension() {
    return values.size();
}

int Point::getId() {
    return pointId;
}

int Point::getClusterId() {
    return clusterId;
}

void Point::setCluster(int id) {
    clusterId = id;
}

int Point::operator[](int i) {
    return values[i];
}