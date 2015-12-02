#include <iostream>
#include <cfloat>
#include "closest-pair.hh"

const double INFINITY = DBL_MAX; //bigger than any possible interpoint
//distance
void printPointPair(const Point&, const Point&);
void printPointPair(const PointPair&);
PointPair divide(Point**, Point**, int);
/*
Closest Pair Functions

Given a collection of nPoints points, find and ***print***
* the closest pair of points
* the distance between them
in the form "(x1, y1) (x2, y2) distance"

INPUTS:
- points sorted in nondecreasing order by X coordinate
- points sorted in nondecreasing order by Y coordinate
- # of input points
*/


PointPair bruteForce(Point* pointsByX[], Point* pointsByY[], int nPoints)
{
Point a, b;
double min = INFINITY, dist;
for (int i = 0; i < nPoints - 1; ++i)
for (int j = i + 1; j < nPoints; ++j) {
dist = pointsByX[i]->distance(pointsByX[j]);
if (min > dist) {
min = dist;
a = *pointsByX[i];
b = *pointsByX[j];
}
}
printPointPair(a, b);
return PointPair(a, b);
}

PointPair divCon(Point* pointsByX[], Point* pointsByY[], int nPoints)
{
PointPair p = divide(pointsByX, pointsByY, nPoints);
printPointPair(p);
return p;
}

PointPair divide(Point* pointsByX[], Point* pointsByY[], int nPoints)
{
using namespace std;
if (nPoints > 3) {
//divide
// set line
int bisect = pointsByX[nPoints/2]->x();
// sort Y lists to create new ones
Point* yL[nPoints];
Point* yR[nPoints];
int lenL = 0, lenR = 0;
for (int i = 0; i < nPoints; ++i) {
if (pointsByY[i]->x() <= bisect) {
yL[lenL] = pointsByY[i];
++lenL;
}
if (pointsByY[i]->x() >= bisect) {
yR[lenR] = pointsByY[i];
++lenR;
}
}

//conquer
// pass sorted arrays for repeat
PointPair pair1 = divide(pointsByX, yL, lenL);
PointPair pair2 = divide(pointsByX + nPoints - lenR, yR, lenR);
PointPair correct;
//combine
// find mindist
double p1Dist = pair1.distance(),
p2Dist = pair2.distance(),
min = 0;
if (p1Dist < p2Dist) {
correct = pair1;
min = p1Dist;
} else {
correct = pair2;
min = p2Dist;
}

// remove all non-2(mindist) points from y array
// I reuse yL here, since it is the longer than the array I need anyway
int stripLen = 0;
for (int i = 0; i < nPoints; ++i) {
if (pointsByY[i]->x() >= bisect - min
|| pointsByY[i]->x() <= bisect + min) {
yL[stripLen] = pointsByY[i];
++stripLen;
}
}
// then check next seven repeated until the end of the list
for (int i = 0; i < stripLen; ++i)
for (int j = i+1; j-i < 8 && j < stripLen; ++j)
if (yL[i]->distance(yL[j]) < min) {
min = yL[i]->distance(yL[j]);
correct.p1() = yL[i];
correct.p2() = yL[j];
}
return correct;
} else {
return bruteForce(pointsByX, pointsByY, nPoints);
}
}

void printPointPair(const PointPair& pp)
{
using namespace std;
double dist = pp.distance();

cout << pp << " " << dist << endl;
}

void printPointPair(const Point& a, const Point& b)
{
using namespace std;
double dist = a.distance(&b);
cout << a << " " << b << " " << dist << endl;
}
