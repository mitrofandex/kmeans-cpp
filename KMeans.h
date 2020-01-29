#ifndef __KMEANS_H
#define __KMEANS_H

#include <vector>
using namespace std;
class Point;
class Cluster;

class KMeans {
    int kClusters, nIterations, randomState;
    int n, m;
    vector<Cluster> clusters;
    int getNearestClusterId(Point& p);
    void clustersInit(vector<Point>& X);
    bool distributePoints(vector<Point>& X);
    void updateCentroids();
public:
    KMeans(int k, int iter = 100, int state = 42);
    Cluster& getCluster(int pos);
    void fit(vector<Point>& X);
    vector<int> predict(vector<Point>& X);
    void printCentroids();
};


#endif //__KMEANS_H
