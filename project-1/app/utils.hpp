#pragma once

#include <optional>
#include <string_view>
#include <vector>

#include "complex.hpp"

namespace utils {
std::optional<std::vector<Complex>>
read_file(std::string_view file_path, std::optional<std::size_t> read_until);
}
