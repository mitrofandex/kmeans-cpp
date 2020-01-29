import pandas as pd
import matplotlib.pyplot as plt

points = pd.read_csv("input.txt", sep=' ', names=['x', 'y'])
labels = pd.read_csv("output.txt", header=None, squeeze=True)
centroids = pd.read_csv("centroids.txt", sep=' ', names=['x', 'y'])

plt.scatter(points.x, points.y, c=labels)
plt.scatter(centroids.x, centroids.y, marker='x')
plt.show()
