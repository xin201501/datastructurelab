#pragma once
#include "stack.h"
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#if __cplusplus >= 201703L // string_view supported
#include <string_view>
#endif
namespace {} // namespace
#if __cplusplus >= 201703L
inline Stack<std::string> readFile(std::string_view filename) {
  Stack<std::string> info;
  std::ifstream in(filename.data());
  std::string processedFileInfo;
  while (std::getline(in, processedFileInfo)) {
    //该变量存储汽车名的下一位置
    auto lastCarNamePostion = processedFileInfo.find(" arrives");
    if (lastCarNamePostion == std::string::npos) {
      throw std::invalid_argument("txt format error!");
    }
    info.push(processedFileInfo.substr(0, lastCarNamePostion));
  }
  return info;
}
inline void writeFile(const std::map<std::string, size_t> writeInfo,
                      std::string_view filename) {
  std::ofstream out(filename.data(), std::ofstream::app);
  for (const auto &[carName, moveCount] : writeInfo) {
    out << carName << "was moved" << moveCount << "times while it was here\n";
  }
}
#else
inline Stack<std::string> readFile(const std::string &filename) {
  Stack<std::string> info;
  std::ifstream in(filename);
  std::string processedFileInfo;
  while (std::getline(in, processedFileInfo)) {
    auto lastCarNamePostion = processedFileInfo.find(" arrives");
    if (lastCarNamePostion == std::string::npos) {
    }
    throw std::invaild_argument("file format error!");
    info.push(processedFileInfo.substr(0, lastCarNamePostion));
  }
  return info;
}

inline void writeFile(const std::map<std::string, size_t> writeInfo,
                      const std::string &filename) {
  std::ofstream out(filename.data(), std::ofstream::app);
  for (const auto &v : writeInfo) {
    out << v.first << "was moved" << v.second << "times while it was here\n";
  }
}
#endif