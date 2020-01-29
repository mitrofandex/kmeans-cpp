#include "Cluster.h"
#include "Point.h"
#include <iostream>

Cluster::Cluster(int id, Point p) : clusterId(id) {
    for (int i = 0; i < p.dimension(); i++) {
        centroid.push_back(p[i]);
    }
}

int Cluster::size() {
    return points.size();
}

int Cluster::getId() {
    return clusterId;
}

Point& Cluster::getPoint(int pos) {
    return points[pos];
}

double Cluster::getCentroid(int pos) {
    return centroid[pos];
}

void Cluster::setCentroid(int pos, double value) {
    centroid[pos] = value;
}

void Cluster::updateCentroid() {
    vector<double> newCentroid(centroid.size(), 0.0);

    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < centroid.size(); j++) {
            newCentroid[j] += getPoint(i)[j];
        }
    }
    for (int i = 0; i < centroid.size(); i++) {
        newCentroid[i] /= size();
        setCentroid(i, newCentroid[i]);
    }
}

void Cluster::printCentroid() {
    cout << '(';
    for (int j = 0; j < centroid.size() - 1; j++) {
        cout << getCentroid(j) << ", ";
    }
    cout << getCentroid(centroid.size() - 1) << ')' << endl;
}

void Cluster::addPoint(Point& p) {
    p.setCluster(clusterId);
    points.push_back(p);
}

void Cluster::removePoint(int id) {
    for (int i = 0; i < size(); i++) {
        if (points[i].getId() == id) {
            points.erase(points.begin() + i);
            return;
        }
    }
}