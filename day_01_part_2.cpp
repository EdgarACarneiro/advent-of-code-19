#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

int compute_fuel(int mass)
{
  return floor(mass / 3.0) - 2;
}

int main(int argc, char *argv[])
{
  ifstream infile("input/day1.txt");
  int sum = 0;

  int mass;
  while (infile >> mass)
  {
    int rec_fuel = 0;

    while (true)
    {
      mass = compute_fuel(mass);

      if (mass >= 0)
        rec_fuel += mass;
      else
        break;
    }

    sum += rec_fuel;
  }

  cout << sum << '\n';

  return 0;
}
