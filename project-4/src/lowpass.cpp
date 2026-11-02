#include "filters.hpp"
#include "utils.hpp"
#include <iostream>
#include <ostream>

int main(int argc, char **argv) {
  if (argc < 4) {
    std::cerr
        << "Missing arguments: <coefficient>, <execution count>, <input.wav>"
        << std::endl;
    return 0;
  }

  const std::string file{argv[3]};

  std::optional<WavData> wav_opt{WavData::read_wav(file)};
  if (!wav_opt.has_value()) {
    return 0;
  }

  WavData wav{wav_opt.value()};

  const float coefficient{std::stof(argv[1])};
  const std::size_t iter_count{std::stoull(argv[2])};

  for (std::size_t i{0}; i < iter_count; i++) {
    filters::lowpass(wav.samples, coefficient);
  }

  filters::normalize(wav.samples, -1.5);

  const std::string final_file{
      "./processed-" + file.substr(file.find_last_of('/') + 1),
  };

  WavData::write_wav(final_file, wav);

  return 0;
}
