#include "filters.hpp"
#include "utils.hpp"
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 4) {
    std::cerr
        << "Missing arguments: <coefficient>, <execution count>, <input.wav>"
        << std::endl;
    return 0;
  }

  std::optional<WavData> wav_opt{WavData::read_wav(argv[3])};
  if (!wav_opt.has_value()) {
    return 0;
  }

  WavData wav{wav_opt.value()};

  // const float coefficient{std::stof(argv[1])};
  // const std::size_t iter_count{std::stoull(argv[2])};
  //
  // for (std::size_t i{0}; i < iter_count; i++) {
  //   filters::lowpass(wav.samples, coefficient);
  // }

  // TODO: Normalize the data

  WavData::write_wav("processed.wav", wav);

  return 0;
}
