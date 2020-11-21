#include "../include/parkinglot.h"
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
int main() {
  ParkingLot lot{"a", "b", "c", "d"};
  lot.quit("b");
  cin >> lot;
  cout << lot;
}