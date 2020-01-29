#ifndef __POINT_H
#define __POINT_H

#include <vector>
#include <sstream>
using namespace std;


class Point {
    int pointId, clusterId;
    vector<double> values;
public:
    Point(int id, const string& s);
    int dimension();
    int getId();
    int getClusterId();
    void setCluster(int id);
    int operator[](int i);
};


#endif //__POINT_H
