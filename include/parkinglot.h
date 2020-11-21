#pragma once
#include "stack.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#if __cplusplus >= 201703L
#include <string_view> //c++17引入,只读字符串,创建/拷贝不需要堆空间分配
#endif
#if __cplusplus < 201703L
namespace {
size_t CAPACITY = 5;
const char *defaultOutputFileName = "output.txt";
} // namespace
#endif
class ParkingLot {
private:
  Stack<std::string> parkingLine;
  std::unordered_map<std::string, size_t> moveCount;
  std::string writeFilename;
  size_t carCount = 0;
#if __cplusplus >= 201703L
  inline static size_t CAPACITY = 5;
  inline static const char *defaultOutputFileName = "output.txt";
#endif
public:
#if __cplusplus >= 201703L
  ParkingLot(std::string_view writeFilename = defaultOutputFileName)
      : writeFilename(writeFilename) {}
#else
  ParkingLot(const std::string &writeFilename = defaultOutPutFileName)
      writeFilename(writeFilename) {}
#endif
  ParkingLot(std::initializer_list<std::string> cars,
             const std::string &writeFilename = defaultOutputFileName)
      : parkingLine(cars), writeFilename(writeFilename) {}
  friend std::ostream &operator<<(std::ostream &os,
                                  const ParkingLot &parkingLot) {
    return os << parkingLot.parkingLine;
  }
  ParkingLot(const ParkingLot &another) = default;
  ParkingLot(ParkingLot &&another) noexcept
      : parkingLine(std::move(another.parkingLine)),
        moveCount(std::move(another.moveCount)),
        writeFilename(std::move(another.writeFilename)),
        carCount(another.carCount) {}
  ParkingLot &operator=(const ParkingLot &another) {
    parkingLine = another.parkingLine;
    moveCount = another.moveCount;
    writeFilename = another.writeFilename;
    carCount = another.carCount;
    return *this;
  }
  ParkingLot &operator=(ParkingLot &&another) {
    std::exchange(*this, another);
    return *this;
  }
  ~ParkingLot() {
    std::ofstream out("output.txt", std::ofstream::app);
    while (!parkingLine.isEmpty()) {
#if __cplusplus >= 201703L
      std::string_view carName = parkingLine.top();
#else
      const std::string &carName = parkingLine.top();
#endif
      out << carName << " was moved " << moveCount[carName.data()]
          << " times while it was here\n";
      parkingLine.pop();
    }
  }
  Stack<std::string> &getParkingLine() { return parkingLine; }
  const Stack<std::string> &getParkingLine() const { return parkingLine; }
  std::unordered_map<std::string, size_t> &getMoveCount() { return moveCount; }
  const std::unordered_map<std::string, size_t> &getMoveCount() const {
    return moveCount;
  }
#if __cplusplus >= 201703L
  bool enter(std::string_view carName)
#else
  bool enter(const std::string &carName)
#endif
  {
    std::ofstream out(writeFilename, std::ofstream::app);
    if (carCount == CAPACITY) {
      out << "Sorry " << carName << ',' << "the lot is full\n";
      return false;
    }
    parkingLine.push(carName.data());
    moveCount.insert({carName.data(), 0});
    carCount++;
    return true;
  }
#if __cplusplus >= 201703L
  bool quit(std::string_view carName)
#else
  bool quit(const std::string &carName)
#endif
  {
    std::ofstream out("output.txt", std::ofstream::app);
    decltype(parkingLine) temporaryQuitCars;
    if (moveCount.find(carName.data()) == moveCount.cend()) {
      return false;
    }
    while (parkingLine.top() != carName) {
#if __cplusplus >= 201703L
      std::string_view mostFrontCar = parkingLine.top();
#else
      const std::string &mostFrontCar = parkingLine.top();
#endif
      temporaryQuitCars.push(mostFrontCar.data());
#if __cplusplus >= 201703L
      for (auto &[name, count] : moveCount) {
        if (name == mostFrontCar) {
          count++;
          break;
        }
      }
#else
      for (auto it = moveCount.begin(); it != moveCount.end(); it++) {
        if (it->first == mostFrontCar) {
          ++it->second;
          break;
        }
      }
#endif
      parkingLine.pop();
    }
#if __cplusplus >= 201703L
    std::string_view car = parkingLine.top();
#else
    const std::string &car = parkingLine.top();
#endif
    out << car << " was moved " << moveCount[car.data()]
        << " times while it was here\n";
    parkingLine.pop();
    carCount--;
    while (!temporaryQuitCars.isEmpty()) {
      parkingLine.push(temporaryQuitCars.top());
      temporaryQuitCars.pop();
    }
    return true;
  }
};