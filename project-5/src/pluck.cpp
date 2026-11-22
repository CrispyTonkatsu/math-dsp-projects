#include "filters.hpp"
#include "utils.hpp"

int main(int, char**) {
  constexpr std::size_t sample_rate{44100};
  constexpr uint16_t max_range{1 << 15};
  constexpr std::size_t length{sample_rate * 5};

  std::vector<Complex> samples;
  samples.resize(length);

  for (std::size_t i{0}; i < length; i++) {
    int sample{std::rand() % max_range};

    samples[i] =
      Complex::from_cartesian(static_cast<double>(sample) / max_range, 0.0);
  }

  {
    using namespace filters;
    apply_filters<LowPass<0.1>>(samples);
  }

  WavData::write_wav("strings.wav", WavData::create_new(std::move(samples)));

  return 0;
}
