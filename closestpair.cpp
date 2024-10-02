#include "closestpair.h"
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>  // used to seed srand for extra credit
#include <iostream>
using namespace std;

//brute force algorithm - O(n^2)
Outcome brute(const vector<Point>& data) {
    Outcome best(data[0], data[1], distSquared(data[0],data[1]));
    for (unsigned int j=1; j < data.size(); j++) {
        for (unsigned int k=0; k < j; k++) {
            long long temp = distSquared(data[j], data[k]);
            if (temp < best.dsq) {
                best = Outcome(data[j], data[k], temp);
            }
        }
    }
    return best;
}

//divide-and-conquer algorithm - O(nlogn)
//customized brute force function
Outcome customBrute(const vector<Point>& points) {
    long long minDist = LLONG_MAX;
    Outcome best;

    //compares every pair of points
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            long long dist = distSquared(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
                best = Outcome(points[i], points[j], dist);
            }
        }
    }
    return best; //returns the two closest points and their squared distance
}

//finds the closest pair of points
Outcome closestPair(const vector<Point>& pointsX, const vector<Point>& pointsY) {
    int n = pointsX.size();

    if (n <= 200) { //base case
        Outcome result = customBrute(pointsX);
        return result;
    } else {
        //divides the points
        int mid = n / 2;
        Point midPoint = pointsX[mid];
        
        vector<Point> leftX(pointsX.begin(), pointsX.begin() + mid);
        vector<Point> rightX(pointsX.begin() + mid, pointsX.end());
        
        //rearranges the points by y-coords
        vector<Point> leftY, rightY;
        for (const auto& point : pointsY) {
            if (point.x <= midPoint.x) {
                leftY.push_back(point);
            } else {
                rightY.push_back(point);
            }
        }

        //recursive calls
        Outcome leftPair = closestPair(leftX, leftY);
        Outcome rightPair = closestPair(rightX, rightY);

        //compares closest pairs
        Outcome best = (leftPair.dsq < rightPair.dsq) ? leftPair : rightPair;
        long long delta = best.dsq;

        //handles strip - points w/in a distance delta
        vector<Point> strip_band;
        for (const auto& point : pointsY) {
            if (abs(point.x - midPoint.x) <= delta) {
                strip_band.push_back(point);
            }
        }

        //checks points in the strip
        for (size_t i = 0; i < strip_band.size(); ++i) {
            for (size_t j = i + 1; j < min(i + 7, strip_band.size()); ++j) {
                    long long d = distSquared(strip_band[i], strip_band[j]);
                    if (d < delta) {
                        best = Outcome(strip_band[i], strip_band[j], d);
                        delta = d;
                    }
            }
        }
        return best; //returns closest pair
    }
}

//performs divide-and-conquer
Outcome efficient(const vector<Point>& data) {
    //initialize coordinate vectors 
    vector<Point> pointsX = data;
    vector<Point> pointsY = data;

    //sorts points by X and Y coordinates
    sort(pointsX.begin(), pointsX.end(), compareByX);
    sort(pointsY.begin(), pointsY.end(), compareByY);

    //calls the recursive function
    return closestPair(pointsX, pointsY);
}

Outcome extra(const vector<Point>& data) {
    return Outcome();
}
