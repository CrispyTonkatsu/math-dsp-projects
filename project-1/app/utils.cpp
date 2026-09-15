#include "utils.hpp"
#include "parser.hpp"

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

std::optional<std::vector<Complex>>
utils::read_file(std::string_view file_path,
                 std::optional<std::size_t> read_until) {
  std::ifstream file{file_path.data()};

  if (!file.is_open()) {
    std::cerr << "File not found: " << file_path << "\n";
    return std::nullopt;
  }

  std::vector<Complex> output;
  std::size_t lines_read{0};

  while (!file.eof()) {
    std::string buffer{};
    std::getline(file, buffer);

    const std::optional<Complex> number_opt{parse_cartesian(buffer)};
    if (!number_opt) {
      std::cerr << "Invalid Number: " << buffer << "\n";
      return std::nullopt;
    }

    output.push_back(number_opt.value());
    lines_read++;

    if (read_until && lines_read == *read_until) {
      break;
    }
  }

  return output;
}
