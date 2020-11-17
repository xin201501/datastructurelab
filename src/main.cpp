#include "../include/parkinglot.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using namespace std::literals;
int main() {
  ParkingLot lot{"a", "b", "c", "d"};
  lot.quit("b");
  cout << lot;
}