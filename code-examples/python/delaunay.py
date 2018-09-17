import numpy as np
from scipy.spatial import Delaunay
import matplotlib.pyplot as plt
import random

maxdist=.1

points=[[random.random(),random.random()] for x in range(1000)]
points=np.array([x for x in points if x[0]<.25 or x[0]>.75 or x[1]>.75])
tri = Delaunay(points).simplices

def dist(line):
    x=line[0][0]-line[0][1]
    y=line[1][0]-line[1][1]
    return x*x+y*y

def plotSimplices(tri,points,maxdist):
    for s in tri:
        for x in [[0,1],[0,2],[1,2]]:
            line=([points[s][x[0]][0],points[s][x[1]][0]],[points[s][x[0]][1],points[s][x[1]][1]])
            if dist(line)<maxdist*maxdist:
                plt.plot(line[0],line[1])
    plt.show()

plotSimplices(tri,points,maxdist)

