#include <cstddef>
#include <iostream>
#include <ostream>
#include "filters.hpp"
#include "utils.hpp"

std::vector<Complex> play_note(
  const std::size_t sample_rate,
  const double duration,
  const double, // target_freq
  const std::size_t noise_length
) {
  constexpr uint16_t max_range{15000};
  const std::size_t length{static_cast<std::size_t>(sample_rate * duration)};

  std::vector<Complex> samples;
  samples.resize(length);

  for (std::size_t i{0}; i < noise_length; i++) {
    int sample{(std::rand() % max_range) - (max_range / 2)};

    samples[i] =
      Complex::from_cartesian(static_cast<double>(sample) / max_range, 0.0);
  }

  {
    using namespace filters;

    apply_filters<LowPass, AllPass, Comb>(
      std::tuple{
        LowPass::Config{.a = 0.5},
        AllPass::Config{.a = 0.158},
        Comb::Config{.R = 0.99985, .L = 99},
    },
      samples
    );
  }

  return samples;
}

// TODO: Add input to the app
int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Missing starting frequency" << std::endl;
    return 0;
  }

  const double start_freq{std::stod(argv[1])};

  constexpr std::size_t sample_rate{44100};
  constexpr std::size_t duration{1};

  std::vector<Complex> samples{
    play_note(sample_rate, duration, start_freq, 99)
  };

  WavData::write_wav("strings.wav", WavData::create_new(std::move(samples)));

  return 0;
}
