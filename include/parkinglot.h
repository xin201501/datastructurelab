#pragma once
#include "stack.h"
#include <fstream>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <utility>

#if __cplusplus >= 201703L
#include <string_view> //c++17引入,只读字符串,创建/拷贝不需要堆空间分配
#endif
class ParkingLot {
private:
  Stack<std::string> parkingLine;
  std::unordered_map<std::string, size_t> moveCount;
  std::string writeFilename;
  size_t carCount = 0;
  size_t capacity;
#if __cplusplus >= 201703L
  inline static const char *defaultOutputFileName = "output.txt";
#else
  static const char *defaultOutputFileName;
#endif
public:
#if __cplusplus >= 201703L
  ParkingLot(std::string_view writeFilename = defaultOutputFileName,
             size_t capacity = 5)
      : writeFilename(writeFilename), capacity(capacity) {}
#else
  ParkingLot(const std::string &writeFilename = defaultOutputFileName,
             size_t capacity = 5)
      : writeFilename(writeFilename), capacity(capacity) {}
#endif
#if __cplusplus >= 201703L
  ParkingLot(std::initializer_list<std::string> cars,
             std::string_view writeFilename = defaultOutputFileName,
             size_t capacity = 5)
#else
  ParkingLot(std::initializer_list<std::string> cars,
             const std::string &writeFilename = defaultOutputFileName,
             size_t capacity = 5)
#endif
      : parkingLine(cars), writeFilename(writeFilename), capacity(capacity) {
  }
  friend std::ostream &operator<<(std::ostream &os,
                                  const ParkingLot &parkingLot) {
    return os << parkingLot.parkingLine;
  }
  ParkingLot(const ParkingLot &another) = default;
  ParkingLot(ParkingLot &&another) noexcept
      : parkingLine(std::move(another.parkingLine)),
        moveCount(std::move(another.moveCount)),
        writeFilename(std::move(another.writeFilename)),
        carCount(another.carCount), capacity(another.capacity) {}
  ParkingLot &operator=(const ParkingLot &another) {
    parkingLine = another.parkingLine;
    moveCount = another.moveCount;
    writeFilename = another.writeFilename;
    carCount = another.carCount;
    capacity = another.capacity;
    return *this;
  }
  ParkingLot &operator=(ParkingLot &&another) {
#if __cplusplus >= 201703L
    std::exchange(*this, another);
#else
    parkingLine = std::move(another.parkingLine);
    moveCount = std::move(another.moveCount);
    writeFilename = std::move(another.writeFilename);
    carCount = another.carCount;
    capacity = another.capacity;
#endif
    return *this;
  }
  ~ParkingLot() {
    std::ofstream out(writeFilename, std::ofstream::app);
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
    if (carCount == capacity) {
      out << "Sorry " << carName << ',' << " the lot is full\n";
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
    std::ofstream out(writeFilename, std::ofstream::app);
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
    moveCount.erase(car.data());
    carCount--;
    while (!temporaryQuitCars.isEmpty()) {
      parkingLine.push(temporaryQuitCars.top());
      temporaryQuitCars.pop();
    }
    return true;
  }
};
#if __cplusplus < 201703L
const char *ParkingLot::defaultOutputFileName = "output.txt";
#endif