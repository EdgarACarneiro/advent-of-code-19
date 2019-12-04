#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void split(const string &str, vector<string> &v, char delim = ',')
{
    stringstream ss(str);
    string token;

    while (getline(ss, token, delim))
    {
        v.push_back((token));
    }
}

class Point
{
private:
    int x;
    int y;

public:
    Point(int x, int y) : x(x), y(y)
    {
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    bool operator==(Point p2)
    {
        return x == p2.getX() && y == p2.getY();
    }
};

// class Line
// {
// private:
//     Point bPoint;
//     Point ePoint;
//     bool vertical;
// public:
//     Line(string instruction, Point begin): bPoint(begin) {
//         int change = stoi(instruction.erase(0, 1));

//         switch(instruction[0]) {
//             case 'U':
//                 ePoint = Point(bPoint.getX(), bPoint.getY() + change);
//                 vertical = true;
//             case 'D':
//                 ePoint = Point(bPoint.getX(), bPoint.getY() - change);
//                 vertical = true;
//             case 'R':
//                 ePoint = Point(bPoint.getX() + change, bPoint.getY());
//                 vertical = false;
//             case 'L':
//                 ePoint = Point(bPoint.getX() - change, bPoint.getY());
//                 vertical = false;
//         }
//     }

//     Point getEndPoint() {
//         return ePoint;
//     }

//     Point* getIntersection(Line l) {
//         if (true) {
//             return new Point(0, 0);
//         }
//         return NULL;
//     }
// };

void addLinePoints(string instruction, vector<Point> &wire, Point lastPoint)
{
    int change = stoi(instruction.substr(1, instruction.size() - 1));

    switch (instruction.at(0))
    {
    case 'U':
        for (int i = 1; i <= change; ++i)
            wire.push_back(Point(lastPoint.getX(), lastPoint.getY() + i));
    case 'D':
        for (int i = 1; i <= change; ++i)
            wire.push_back(Point(lastPoint.getX(), lastPoint.getY() - i));
    case 'R':
        for (int i = 1; i <= change; ++i)
            wire.push_back(Point(lastPoint.getX() + i, lastPoint.getY()));
    case 'L':
        for (int i = 1; i <= change; ++i)
            wire.push_back(Point(lastPoint.getX() - i, lastPoint.getY()));
    }
}

int manhattan_dist(Point a, Point b)
{
    return abs(a.getX() - b.getX()) + abs(a.getY() - b.getY());
}

int main()
{
    ifstream infile("input/day3.txt");
    vector<vector<string> > instructions;

    // Parsing values to list
    string list;
    while (infile >> list)
    {
        vector<string> line_inst;
        split(list, line_inst);
        instructions.push_back(line_inst);
    }

    // inefficient approach -> storing all the points
    vector<vector<Point> > wires;
    for (int i = 0; i < instructions.size(); ++i)
    {
        vector<Point> wire;
        for (int j = 0; j < instructions[i].size(); ++j)
            addLinePoints(instructions[i][j], wire, (j == 0 ? Point(0, 0) : wire[j - 1]));
        wires.push_back(wire);
    }

    int sDist = INT_MAX;

    // Find common points between wires
    for (int i = 0; i < wires[0].size(); ++i)
        for (int j = i + 1; j < wires[1].size(); ++j)
            if (wires[0][i] == wires[1][j] && manhattan_dist(Point(0, 0), wires[0][j]) <= sDist)
                sDist = manhattan_dist(Point(0, 0), wires[0][j]);

    cout << sDist << endl;
}