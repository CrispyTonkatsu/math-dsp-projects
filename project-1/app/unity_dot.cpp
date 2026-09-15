#include "complex.hpp"
#include "utils.hpp"
#include <iostream>
#include <ostream>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Not enough arguments" << std::endl;
    return 0;
  }

  const std::size_t number_count{std::stoul(argv[1])};
  const std::string file_path{argv[2]};

  std::optional<std::vector<Complex>> numbers_opt{
      utils::read_file(file_path, number_count)};

  if (!numbers_opt) {
    return 0;
  }

  const ComplexVec vec{*numbers_opt};
  const ComplexVec roots{ComplexVec::from_nth_roots(number_count)};

  std::cout << vec.inner_product(roots) << std::endl;

  return 0;
}
