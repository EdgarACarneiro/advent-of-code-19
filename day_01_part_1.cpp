#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;


int main(int argc, char* argv[]) {
  ifstream infile("input/day1.txt");
  int sum = 0;

  int mass;
  while (infile >> mass) {
    sum += floor(mass / 3.0) - 2;
  }

  cout << sum << '\n';

  return 0;
}
