#include "../include/parkinglot.h"
#include <fstream>
#include <iostream>
#include <string>
const char *defaultInputFileName = "data.txt";
using std::cerr;
//约定在控制台中传入的第一个参数为输入文件名
int main(int argc, const char *argv[]) {
  ParkingLot lot;
  std::ifstream in;
  switch (argc) {
  case 1:
    in.open(defaultInputFileName);
    break;
  case 2:
    in.open(argv[1]);
    break;
  case 3: {
    in.open(argv[1]);
    lot = ParkingLot(argv[2]);
    break;
  }
  default: {
    cerr << "main function arguments invalid,exit.";
    return -1;
  }
  }
  if (!in) {
    cerr << "open input file failed，exit.";
    return -1;
  }
  std::string processedFileInfo;
  while (std::getline(in, processedFileInfo)) {
    //变量存储车名的下一位置
    auto lastCarNamePostion = processedFileInfo.find(" arrives");
    if (lastCarNamePostion == std::string::npos) {
      lastCarNamePostion = processedFileInfo.find(" departs");
      if (lastCarNamePostion == std::string::npos) {
        throw std::invalid_argument("txt format error!");
      }
      lot.quit(processedFileInfo.substr(0, lastCarNamePostion));
    } else {
      lot.enter(processedFileInfo.substr(0, lastCarNamePostion));
    }
  }
}