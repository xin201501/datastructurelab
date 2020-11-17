#pragma once
#include "stack.h"
#include <string>
#if __cplusplus >= 201703L
#include <string_view> //c++17引入,只读字符串,创建/拷贝不需要堆空间分配
#endif
class ParkingLot {
private:
  Stack<std::string> parkingLine;

public:
  ParkingLot() = default;
  ParkingLot(std::initializer_list<std::string> cars) : parkingLine(cars) {}
  friend std::ostream &operator<<(std::ostream &os,
                                  const ParkingLot &parkingLot) {
    return os << parkingLot.parkingLine;
  }
  friend std::istream &operator>>(std::istream &is, ParkingLot &parkingLot) {
    return is >> parkingLot.parkingLine;
  }
#if __has_include(<string_view>)
  void enter(std::string_view carName) { parkingLine.push(carName.data()); }
  bool quit(std::string_view carName) {
    decltype(parkingLine) temporaryQuitCars;
    if (!parkingLine.contains(carName.data())) {
      return false;
    }
    while (parkingLine.top() != carName) {
      temporaryQuitCars.push(parkingLine.top());
      parkingLine.pop();
    }
    parkingLine.pop();
    while (!temporaryQuitCars.isEmpty()) {
      parkingLine.push(temporaryQuitCars.top());
      temporaryQuitCars.pop();
    }
    return true;
  }
#else
  void enter(const std::string &carName) { parkingLine.push(carName); }
  bool quit(const std::string &carName) {
    decltype(parkingLine) temporaryQuitCars;
    if(!parkingLine.contains(carName){
      return false;
    }
    while (parkingLine.top() != carName) {
      temporaryQuitCars.push(parkingLine.top());
      parkingLine.pop();
    }
    parkingLine.pop();
    while (!temporaryQuitCars.isEmpty()){
      parkingLine.push(temporaryQuitCars.top());
      temporaryQuitCars.pop();
    }
    return true;
  }
#endif
};