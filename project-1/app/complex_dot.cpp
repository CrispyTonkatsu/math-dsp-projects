#include "utils.hpp"
#include <iostream>
#include <ostream>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Not enough arguments" << std::endl;
    return 0;
  }

  const std::size_t number_count{std::stoul(argv[1])};
  const std::string file_path_a{argv[2]};
  const std::string file_path_b{argv[2]};

  std::optional<std::vector<Complex>> numbers_a_opt{
      utils::read_file(file_path_a, number_count)};

  std::optional<std::vector<Complex>> numbers_b_opt{
      utils::read_file(file_path_b, number_count)};

  if (!numbers_a_opt || !numbers_b_opt) {
  }

  return 0;
}
