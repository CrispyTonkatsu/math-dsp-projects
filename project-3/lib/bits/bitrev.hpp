#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

std::uint64_t reverse_add(std::uint64_t bits, std::size_t bit_count);

std::string pretty_bitset(std::uint64_t bits, std::size_t bit_count);
