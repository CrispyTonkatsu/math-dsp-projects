#include <array>
#include <iostream>
#include "filters.hpp"
#include "utils.hpp"

// TODO: Move this to the library and put it in the music section
std::vector<Complex> play_note(
  const std::size_t sample_rate,
  const double duration,
  const double target_freq,
  const double pluck_strength
) {
  constexpr uint16_t max_sample{15000};
  constexpr uint16_t max_bound{2 * max_sample + 1};
  const std::size_t length{static_cast<std::size_t>(sample_rate * duration)};

  std::vector<Complex> samples;
  samples.resize(length);

  const double target_value{(sample_rate / target_freq) - 0.5};
  const std::size_t L{static_cast<std::size_t>(target_value)};

  const std::size_t noise_length{static_cast<std::size_t>(pluck_strength * L)};

  for (std::size_t i{0}; i < noise_length; i++) {
    // TODO: probably improve the way the sounds are being generated
    int sample{(std::rand() % max_bound) - max_sample};

    samples[i] =
      Complex::from_cartesian(static_cast<double>(sample) / max_sample, 0.0);
  }

  {
    using namespace filters;

    const double delta{target_value - static_cast<double>(L)};
    const double half_omega{
      std::numbers::pi_v<double> * (target_freq / sample_rate)
    };

    // Getting the coefficient from delta
    const double fine_tune{
      std::sin((1 - delta) * half_omega) / std::sin((1 + delta) * half_omega)
    };

    apply_filters<LowPass, AllPass, Comb>(
      std::tuple{
        LowPass::Config{.a = 0.5},
        AllPass::Config{.a = fine_tune},
        Comb::Config{.R = 0.99985, .L = L},
    },
      samples
    );
  }

  return samples;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Missing starting frequency" << std::endl;
    return 0;
  }

  const double start_freq{std::stod(argv[1])};

  constexpr std::size_t sample_rate{44100};
  constexpr std::size_t duration{1};

  const std::array<std::size_t, 8> scale{0, 2, 4, 5, 7, 9, 11, 12};

  std::vector<Complex> samples{};
  for (std::size_t i{0}; i < 8; i++) {
    const double target_freq{start_freq * std::pow(2.0, scale[i] / 12.0)};

    std::vector<Complex> string{
      play_note(sample_rate, duration, target_freq, 0.5)
    };

    samples.insert(samples.end(), string.begin(), string.end());
  }

  WavData::write_wav("strings.wav", WavData::create_new(std::move(samples)));

  return 0;
}
