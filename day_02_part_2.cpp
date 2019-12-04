#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void split(const string &str, vector<int> &v, char delim = ',')
{
    stringstream ss(str);
    string token;

    while (getline(ss, token, delim))
    {
        v.push_back(stoi(token));
    }
}

int findValue(vector<int> intcodes, int a, int b)
{
    // Replacing positions
    intcodes[1] = a;
    intcodes[2] = b;

    // Processing Intcodes
    for (int i = 0; i < intcodes.size(); i+=4)
    {
        switch (intcodes[i])
        {
        case 1:
            intcodes[intcodes[i + 3]] =
                intcodes[intcodes[i + 1]] +
                intcodes[intcodes[i + 2]];
            break;
        case 2:
            intcodes[intcodes[i + 3]] =
                intcodes[intcodes[i + 1]] *
                intcodes[intcodes[i + 2]];
            break;
        case 99:
            // Forcing stop
            i = intcodes.size();
            break;
        default:
            cout << "ERROR\n";
        }
    }

    return intcodes[0];
}

int score(int a, int b)
{
    return 100 * a + b;
}

int main()
{
    ifstream infile("input/day2.txt");
    vector<int> intcodes;

    // Parsing values to list
    string list;
    infile >> list;
    split(list, intcodes);

    // Brute force approach
    for (int i = 0; i < 99; ++i)
    {
        for (int j = 0; j < 99; ++j)
        {
            if (findValue(intcodes, i, j) == 19690720)
            {
                cout << score(i, j) << '\n';
                return 0;
            }
        }
    }

    return -1;
}