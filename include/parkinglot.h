#pragma once
#include "io.h"
#include "stack.h"
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

#if __cplusplus >= 201703L
#include <string_view> //c++17引入,只读字符串,创建/拷贝不需要堆空间分配
#endif
class ParkingLot {
private:
  Stack<std::string> parkingLine;
  std::map<std::string, size_t> moveCount;
#if __cplusplus >= 201703L
  static auto isVaildInput(std::string_view str)
#else
  static unsigned long long isVaildInput(const std::string &str)
#endif
  {
    return str.find(" arrives");
  }

public:
  ParkingLot() = default;
  ParkingLot(std::initializer_list<std::string> cars) : parkingLine(cars) {}
#if __cplusplus >= 201703L
  ParkingLot(std::string_view inputFilename = "data.txt")
#else
  ParkingLot(const std::string &inputFilename = "data.txt")
#endif
      : parkingLine(readFile(inputFilename)) {
  }
  friend std::ostream &operator<<(std::ostream &os,
                                  const ParkingLot &parkingLot) {
    return os << parkingLot.parkingLine;
  }
  friend std::istream &operator>>(std::istream &is, ParkingLot &parkingLot) {
    std::string readLine;
    std::getline(is, readLine);
    auto suffixIndex = isVaildInput(readLine);
    if (suffixIndex == std::string::npos) {
      throw std::invalid_argument("input format invalid!");
    }
    parkingLot.parkingLine.push(readLine.substr(0, suffixIndex));
    return is;
  }
#if __cplusplus >= 201703L
  void enter(std::string_view carName) { parkingLine.push(carName.data()); }
  bool quit(std::string_view carName) {
    decltype(parkingLine) temporaryQuitCars;
    if (!parkingLine.contains(carName.data())) {
      return false;
    }
    while (parkingLine.top() != carName) {
      std::string mostFrontCar = parkingLine.top();
      temporaryQuitCars.push(mostFrontCar);
      moveCount[mostFrontCar]++;
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
    if (!parkingLine.contains(carName)) {
      return false;
    }
    while (parkingLine.top() != carName) {
      std::string mostFrontCar = parkingLine.top();
      temporaryQuitCars.push(mostFrontCar);
      moveCount[mostFrontCar]++;
      parkingLine.pop();
    }
    parkingLine.pop();
    while (!temporaryQuitCars.isEmpty()) {
      parkingLine.push(temporaryQuitCars.top());
      temporaryQuitCars.pop();
    }
    return true;
  }
#endif
};