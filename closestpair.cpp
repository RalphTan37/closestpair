#include "closestpair.h"
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>  // used to seed srand for extra credit
using namespace std;

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

Outcome closestStrip(std::vector<Point>& strip, long long d) {
    if (strip.size() < 2) {
        return Outcome(); // Handle case with insufficient points
    }
    Outcome best(strip[0], strip[1], d);
    std::sort(strip.begin(), strip.end(), compareByY);

    // Traverse through the strip and check only points that are within d
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < best.dsq; ++j) {
            long long dist = distSquared(strip[i], strip[j]);
            if (dist < best.dsq) {
                best = Outcome(strip[i], strip[j], dist);
            }
        }
    }
    return best;
}

Outcome customBrute(const std::vector<Point>& points) {
    long long minDist = LLONG_MAX;
    Outcome bestPair;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            long long dist = distSquared(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
                bestPair = Outcome(points[i], points[j], dist);
            }
        }
    }
    return bestPair;
}

// Recursive function to find the closest pair of points
Outcome closestPairRec(const std::vector<Point>& pointsX, const std::vector<Point>& pointsY) {
    int n = pointsX.size();
    if (n <= 3) {
        return customBrute(pointsX); // Use brute force for small datasets
    }

    // Divide the points into left and right halves
    int mid = n / 2;
    Point midPoint = pointsX[mid];

    // Create y-sorted lists for left and right halves
    std::vector<Point> leftY, rightY;
    for (const auto& point : pointsY) {
        if (point.x <= midPoint.x) {
            leftY.push_back(point);
        }
        else {
            rightY.push_back(point);
        }
    }
    std::vector<Point> leftX(pointsX.begin(), pointsX.begin() + mid);
    std::vector<Point> rightX(pointsX.begin() + mid, pointsX.end());
    // Recursively find closest pairs in the left and right halves
    Outcome leftPair = closestPairRec(leftX, leftY);
    Outcome rightPair = closestPairRec(rightX, rightY);

    // Find the smaller of the two results
    Outcome bestPair = (leftPair.dsq < rightPair.dsq) ? leftPair : rightPair;

    // Create a strip around the midpoint
    std::vector<Point> strip;
    for (const auto& point : pointsY) {
        if (std::abs(point.x - midPoint.x) < std::sqrt(bestPair.dsq)) {
            strip.push_back(point);
        }
    }

    // Find the closest pair in the strip
    Outcome stripPair = closestStrip(strip, bestPair.dsq);

    // Return the best of the two
    return (stripPair.dsq < bestPair.dsq) ? stripPair : bestPair;
}

Outcome efficient(const vector<Point>& data) {
    if (data.size() <= 3) {
        return customBrute(data);
    }
    std::vector<Point> pointsX = data;
    std::vector<Point> pointsY = data;

    // Sort points based on x-coordinates and y-coordinates
    std::sort(pointsX.begin(), pointsX.end(), compareByX);
    std::sort(pointsY.begin(), pointsY.end(), compareByY);

    // Call the recursive function
    return closestPairRec(pointsX, pointsY);
    //return Outcome();
}

Outcome extra(const vector<Point>& data) {
    return Outcome();
}
