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

int findValue(int a, int b)
{
    ifstream infile("input/day2.txt");
    vector<int> intcodes;

    // Parsing values to list
    string list;
    infile >> list;
    split(list, intcodes);

    // Replacing positions
    intcodes[1] = a;
    intcodes[2] = b;

    // Processing Intcodes
    for (int i = 0; i < intcodes.size(); ++i)
    {
        switch (intcodes[i])
        {
        case 1:
            intcodes[intcodes[i + 3]] =
                intcodes[intcodes[i + 1]] +
                intcodes[intcodes[i + 2]];
            i += 3;
            break;
        case 2:
            intcodes[intcodes[i + 3]] =
                intcodes[intcodes[i + 1]] *
                intcodes[intcodes[i + 2]];
            i += 3;
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
    // Brute force approach
    for (int i = 0; i < 99; ++i)
    {
        for (int j = 0; j < 99; ++j)
        {
            if (findValue(i, j) == 19690720)
            {
                cout << score(i, j) << '\n';
                return 0;
            }
        }
    }

    return -1;
}