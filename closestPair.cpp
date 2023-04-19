/*
 * Name: Mathew Breland
 * Date Submitted: 3/8/2023
 * Lab Section: 001
 * Assignment Name: Finding the closest pair of points (LAB 6)
 */

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Point {

    double x;
    double y;
};

bool compareX(const Point& p1, const Point& p2) {

    return p1.x < p2.x;
}

bool compareY(const Point& p1, const Point& p2) {

    return p1.y < p2.y;
}

double distanceVal(const Point& p1, const Point& p2) {

    double dx = p1.x - p2.x;        // creation of a dx value that is the p1 x value minus the p2 x value
    double dy = p1.y - p2.y;        // creation of a dy value that is the p1 y value minus the p2 y value

    return sqrt(dx * dx + dy * dy); // returning the square root of these (distance formula)
}

double closestPairRec(vector<Point>& points, int left, int right) { // this is a helper function for the closestPair using a left and right integer

    if (left >= right) {
        return INFINITY;    // invalid parameters
    }

    int mid = (left + right) / 2;   // creation of a middle variable

    double result = min(closestPairRec(points, left, mid), closestPairRec(points, mid + 1, right));  // setting double d equal to a minimum function

    vector<Point> strip;

    for (int i = left; i <= right; i++) {

        if (abs(points[i].x - points[mid].x) < result) { // if the absolute value of the x point minus the middle value of the x point is less than result 

            strip.push_back(points[i]);             // push back the point
        }
    }
    sort(strip.begin(), strip.end(), compareY);     // sorting the vector using compareY

    for (int i = 0; i < strip.size(); i++) {

        for (int j = i + 1; j < strip.size() && strip[j].y - strip[i].y < result; j++) {

            result = min(result, distanceVal(strip[i], strip[j]));  // setting result equal to the minimum (function) from the result, and distance from both the strips
        }
    }
    return result;
}

double closestPair(string filename) {

    int n;
    double x, y;

    vector<Point> points;           // creation of a vector of points where the input of the file will be stored

    ifstream fin(filename);         // ifstream fin the file name that was given

    fin >> n;                       // intakes the amount of pairs in the file
    for (int i = 0; i < n; i++) {

        fin >> x >> y;              // for loop that gets the first value which is the x and the second value that gets the y
        points.push_back({ x, y }); // pushes them back to the vector of points 
    }

    fin.close();                    // closing the file

    sort(points.begin(), points.end(), compareX);   // after intaking the points and closing the file, sort the point in the vector from beginning to end

    return closestPairRec(points, 0, n - 1);
}

// commented out main but it was below this line
//int main()
//{
    //double min = closestPair("points250k.txt");

    //ASSERT_NEAR(min, 3.3634146364707639731e-06, 0.00000000000001e-06);
    //if (std::abs(min - 3.3634146364707639731e-06) > 0.00000000000001e-06)
    //{
    //    std::cout << std::scientific << std::setprecision(20);
    //    std::cout << "expected/correct value for min is 3.3634146364707639731e-06, actual value when testing " << min << ".\n";
    //    return 1;
    //}
    //std::cout << "Passed" << std::endl;
    //return 0;
//