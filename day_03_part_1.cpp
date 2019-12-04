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
    Point() : x(0), y(0) {}

    Point(int x, int y) : x(x), y(y) {}

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

class Line
{
public:
    Point bPoint;
    Point ePoint;

    Line(string instruction, Point begin) : bPoint(begin)
    {
        int change = stoi(instruction.substr(1, instruction.size() - 1));

        switch (instruction.at(0))
        {
        case 'U':
            ePoint = Point(bPoint.getX(), bPoint.getY() + change);
            break;
        case 'D':
            ePoint = Point(bPoint.getX(), bPoint.getY() - change);
            break;
        case 'R':
            ePoint = Point(bPoint.getX() + change, bPoint.getY());
            break;
        case 'L':
            ePoint = Point(bPoint.getX() - change, bPoint.getY());
            break;
        }
    }

    Point *getIntersection(Line l)
    {
        float p0_x = bPoint.getX();
        float p0_y = bPoint.getY();
        float p1_x = ePoint.getX();
        float p1_y = ePoint.getY();

        float p2_x = l.bPoint.getX();
        float p2_y = l.bPoint.getY();
        float p3_x = l.ePoint.getX();
        float p3_y = l.ePoint.getY();
        float s1_x, s1_y, s2_x, s2_y;

        s1_x = p1_x - p0_x;
        s1_y = p1_y - p0_y;
        s2_x = p3_x - p2_x;
        s2_y = p3_y - p2_y;

        float s, t;
        s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
        t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

        if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        {
            // Collision detected
            return new Point(p0_x + (t * s1_x), p0_y + (t * s1_y));
        }

        return NULL; // No collision
    }
};

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
 
    vector<vector<Line> > wires;
    for (int i = 0; i < instructions.size(); ++i)
    {
        vector<Line> wire;
        for (int j = 0; j < instructions[i].size(); ++j)
            wire.push_back(Line(instructions[i][j], (j == 0 ? Point() : wire[j - 1].ePoint)));
        wires.push_back(wire);
    }

    int sDist = INT_MAX;

    // Find common points between wires
    for (int i = 0; i < wires[0].size(); ++i)
        for (int j = 0; j < wires[1].size(); ++j)
        {
            Point *intersection = wires[0][i].getIntersection(wires[1][j]);
            if (intersection != NULL)
            {
                int dist = manhattan_dist(Point(0, 0), *intersection);
                if (dist < sDist)
                    sDist = dist;
            }
        }

    cout << sDist << endl;
    return 0;
}