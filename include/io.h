#pragma once
#include "stack.h"
#include <fstream>
#include <string>
#include <vector>

#if __cplusplus >= 201703L // string_view supported
#include <string_view>
#endif
namespace {} // namespace
#if __cplusplus >= 201703L
inline void
writeFile(const std::vector<std::pair<std::string, size_t>> &writeInfo,
          std::string_view filename) {
  std::ofstream out(filename.data(), std::ofstream::app);
  for (const auto &[carName, moveCount] : writeInfo) {
    out << carName << "was moved" << moveCount << "times while it was here\n";
  }
}
#else
inline void writeFile(const std::map<std::string, size_t> &writeInfo,
                      const std::string &filename) {
  std::ofstream out(filename.data(), std::ofstream::app);
  for (const auto &v : writeInfo) {
    out << v.first << "was moved" << v.second << "times while it was here\n";
  }
}
#endif