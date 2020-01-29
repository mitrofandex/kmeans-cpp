#ifndef __CLUSTER_H
#define __CLUSTER_H

#include <vector>
using namespace std;
class Point;


class Cluster {
    int clusterId;
    vector<double> centroid;
    vector<Point> points;
public:
    Cluster(int id, Point p);
    int size();
    int getId();
    Point& getPoint(int pos);
    double getCentroid(int pos);
    void setCentroid(int pos, double value);
    void updateCentroid();
    void addPoint(Point& p);
    void removePoint(int id);
    void printCentroid();
};


#endif //__CLUSTER_H
