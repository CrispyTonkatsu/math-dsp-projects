#include "utils.hpp"
#include <iostream>
#include <ostream>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Not enough arguments" << std::endl;
    return 0;
  }

  const std::size_t number_count{std::stoul(argv[1])};
  const std::string file_path{argv[2]};
  const double rotate_mutiplier{std::stod(argv[3])};

  std::optional<std::vector<Complex>> numbers_opt{
      utils::read_file(file_path, number_count)};

  if (!numbers_opt) {
    return 0;
  }

  std::vector<Complex> numbers{std::move(*numbers_opt)};
  for (const Complex &number : numbers) {
    Complex rotated_number{
        number.rotate(2.0 * std::numbers::pi_v<double> * rotate_mutiplier)};

    std::cout << rotated_number << "\n ";
  }

  return 0;
}
