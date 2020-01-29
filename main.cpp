#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"
using namespace std;

int main(int argc, char **argv) {
    // Show usage message if no arguments passed
    if (argc == 1) {
        cerr << "Usage: " << argv[0] << " <input_file> <n_clusters> [<n_iterations>] [<random_state>]" << endl;
        return 1;
    }

    // Read the input file and create matrix X
    vector<Point> X;
    string s;
    int id = 0;
    ifstream file(argv[1]);
    while (getline(file, s))
        X.emplace_back(id++, s);
    cout << "Points count: " << X.size() << endl << endl;

    // Read the parameters for algorithm
    int kClusters, nIterations = 100, randomState = 42;
    kClusters = stoi(argv[2]);

    if (kClusters <= 0 || kClusters > X.size()) {
        cerr << "Number of clusters must be in range 1..." << X.size() << endl;
        return 1;
    }

    switch (argc) {
        case 4: {nIterations = stoi(argv[3]); break;}
        case 5: {nIterations = stoi(argv[3]); randomState = stoi(argv[4]); break;}
    }

    cout << "Clusters count: " << kClusters << endl;
    cout << "Number of iterations: " << nIterations << endl;
    cout << "Random state: " << randomState << endl;
    cout << endl;

    // Begin clustering
    cout << "Starting.." << endl;
    KMeans km(kClusters, nIterations, randomState);
    km.fit(X);
    vector<int> labels = km.predict(X);

    cout << "Labels: ";
    for (auto& label: labels)
        cout << label << ' ';

    // Write labels to file
    ofstream outFile("../output.txt");
    for (auto& label: labels)
        outFile << label << '\n';

    // Write centroids to file
    ofstream outFile2("../centroids.txt");
    for (int i = 0; i < kClusters; i++) {
        for (int j = 0; j < X[0].dimension() - 1; j++) {
            outFile2 << km.getCluster(i).getCentroid(j) << ' ';
        }
        outFile2 << km.getCluster(i).getCentroid(X[0].dimension() - 1) << '\n';
    }

    return 0;
}