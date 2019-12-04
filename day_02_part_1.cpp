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

int main(int argc, char *argv[])
{
    ifstream infile("input/day2.txt");
    vector<int> intcodes;

    // Parsing values to list
    string list;
    infile >> list;
    split(list, intcodes);

    // Replacing positions
    intcodes[1] = 12;
    intcodes[2] = 2;

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

    cout << intcodes[0] << '\n';

    return 0;
}
