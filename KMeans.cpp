#include "KMeans.h"
#include "Cluster.h"
#include "Point.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>
using namespace std;

KMeans::KMeans(int k, int iter, int state) : kClusters(k), nIterations(iter), randomState(state) {
}

void KMeans::fit(vector<Point>& X) {
    n = X.size();
    m = X[0].dimension();

    bool finished = false;
    clustersInit(X);
    cout << "Initialized centroids with random points." << endl;
    printCentroids();
    cout << "Starting Initial distribution" << endl;
    distributePoints(X);
    cout << "Finished initial distribution" << endl;
    cout << endl;

    for (int i = 0; i < nIterations; i++) {
        cout << "Iteration: " << i + 1 << endl;
        cout << "Updating centroids..." << endl;
        updateCentroids();
        cout << "Centroids updated" << endl;
        if (distributePoints(X)) {
            cout << "Finished after " << i+1 << " iterations." << endl;
            finished = true;
            break;
        }
    }
//    updateCentroids();
    cout << endl;
    if (!finished)
        cout << "Finished after " << nIterations << " iterations." << endl;
    printCentroids();
}

Cluster& KMeans::getCluster(int pos) {
    return clusters[pos];
}

void KMeans::clustersInit(vector<Point>& X) {
    vector<int> indices;

    // Fill indices array 0...(n-1)
    for(int i = 0; i < n; i++)
        indices.push_back(i);


    // Shuffle
    std::random_device rd;
    std::mt19937 g(rd());
    g.seed(randomState);
    shuffle(indices.begin(), indices.end(), g);

//    cout << "Shuffled indices: ";
//    for (int ix: indices) cout << ix << ' ';
//    cout << endl;

    for (int i = 0; i < kClusters; i++) {
        clusters.emplace_back(i, X[indices[i]]);
    }

}

bool KMeans::distributePoints(vector<Point> &X) {
    bool allSame = true;
    for (int i = 0; i < n; i++) {
        int currentClusterId = X[i].getClusterId();
        int nearestClusterId = getNearestClusterId(X[i]);
        if (currentClusterId != nearestClusterId) {
            allSame = false;
            // Remove this point from previous cluster
            if (currentClusterId != -1)
                getCluster(currentClusterId).removePoint(X[i].getId());
            // Add to new cluster
            getCluster(nearestClusterId).addPoint(X[i]);
            X[i].setCluster(nearestClusterId);
        }
    }
    return allSame;
}

void KMeans::updateCentroids() {
    vector<double> newCentroid;
    for (int i = 0; i < kClusters; i++) {
//        cout << "Starting update for cluster#" << i << endl;
        getCluster(i).updateCentroid();
//        cout << "Updated centroid for cluster#" << i << endl;
    }
}

int KMeans::getNearestClusterId(Point& p) {
    vector<double> distances;

    for (int i = 0; i < kClusters; i++) {
        double clusterDistance = 0;
        for (int j = 0; j < p.dimension(); j++) {
            clusterDistance += pow(p[j] - clusters[i].getCentroid(j), 2);
        }
        distances.push_back(sqrt(clusterDistance));
    }

//    cout << "Distances for Point#" << p.getId() << " : ";
//    for (double d: distances) cout << d << ' ';
//    cout << endl;

    return distance(distances.begin(), min_element(distances.begin(), distances.end()));
}

void KMeans::printCentroids() {
    for (int i = 0; i < kClusters; i++) {
        cout << "Cluster #" << i+1 << " centroid: ";
        getCluster(i).printCentroid();
    }
    cout << endl;
}

vector<int> KMeans::predict(vector<Point> &X) {
    vector<int> labels;
    for (int i = 0; i < n; i++) {
        int nearestClusterId = getNearestClusterId(X[i]);
        labels.push_back(nearestClusterId);
    }
    return labels;
}