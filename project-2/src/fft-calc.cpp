#include <iostream>

#include "complex.hpp"
#include "fft.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Not enough arguments";
    return 1;
  }

  const std::size_t n{std::stoull(argv[1])};
  const std::string file_path{argv[2]};

  const std::optional<std::vector<Complex>> input_opt{
      utils::read_file(file_path, n),
  };

  if (!input_opt.has_value()) {
    return 1;
  }

  const ComplexVec input{std::move(input_opt.value())};
  const ComplexVec output{FFT(input, n)};

  std::cout << output;

  return 0;
}
