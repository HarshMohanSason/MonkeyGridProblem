#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class Point {  //Class to represent a point
public:
    int x; //value for x coordinate
    int y;  //value for y coordinate

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    //Custom comparator to make sure no duplicate values are stored
    friend bool operator<(const Point& p1, const Point& p2) {
        if (p1.x != p2.x)
            return p1.x < p2.x;
        return p1.y < p2.y;
    }
};

//Function to sum two points
int sumPoints(Point p) {
    int sumX = 0;
    int sumY = 0;
    int x = abs(p.x);
    int y = abs(p.y);
    while (x > 0 || y > 0) { //looping through both numbers
        int numX = x % 10;   //Note we are taking a mod of the number as we are using simple number splitting: 12 % 10 = 2, then divide the no by 10 to strip it
        int numY = y % 10;
        x /= 10;
        y /= 10;
        sumX += numX;
        sumY += numY;
    }
    return sumX + sumY;
}

bool isAccessible(Point p) {
    int sum = sumPoints(p);
    return sum <= 19; //returns true if less than or equal to 19
}

int findPoints(Point startPoint) { //function to find the points by using a Simple BFS search
    set<Point> totalPoints; //store the totalPoints
    queue<Point> q; //queue to perform BFS for each point
    set<Point> visited;   //store the visited values and check if they exist so the BFS doesn't go in an infinite loop and to also avoid iterating through duplicate values

    q.push(startPoint); //push the initial point

    while (!q.empty()) {
        Point p = q.front();
        q.pop();

        if (visited.find(p) != visited.end()){ //if no duplicate is found, continue
            continue;
          }

        visited.insert(p);  //insert the new point in the queue
        totalPoints.insert(p); //insert the point int the total points

        vector<Point> newPoints = {Point(p.x + 1, p.y), Point(p.x - 1, p.y), //create a new vector to store all possible 4 steps the monkey can take being at that particular point
                                   Point(p.x, p.y + 1), Point(p.x, p.y - 1)};

        for (auto& newPoint : newPoints) { //iterate through this vector and check if these points are accessible or not
            if (isAccessible(newPoint)) {
                q.push(newPoint);
            }
        }
    }
    return totalPoints.size(); //return the total points the monkey can reach
}

int main() {
    Point g(0, 0);
    int total_points = findPoints(g);
    cout << total_points;
    return 0;
}
