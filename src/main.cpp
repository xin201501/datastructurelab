#include "../include/parkinglot.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main() {
  ParkingLot lot{"a", "b", "c", "d"};
  lot.quit("b");
  cout << lot;
}
