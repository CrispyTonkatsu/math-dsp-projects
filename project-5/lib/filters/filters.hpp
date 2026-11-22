#pragma once

#include <array>
#include <cmath>
#include "complex.hpp"

namespace filters {
  template<typename T, typename S> concept SampleStepper =
    requires(T& stepper, S sample) {
      { stepper.step(sample) } -> std::convertible_to<S>;
    };

  template<typename Sample, SampleStepper<Complex>... S>
  class ComposedFilter {
    std::tuple<S...> stages{};

  public:

    Sample step(Sample sample) {
      return std::apply(
        [&](auto&... stage) { return ((sample = stage.step(sample)), ...); },
        stages
      );
    }
  };

  template<double a>
  class LowPass {
    Complex prev_input{};

  public:

    Complex step(Complex sample) {
      const Complex out{sample + a * prev_input};
      prev_input = sample;

      return out;
    }
  };

  static_assert(
    SampleStepper<LowPass<2.0>, Complex>,
    "LowPass stepper doesn't work as a sample stepper"
  );

  template<double a>
  class AllPass {
    Complex prev_input{};
    Complex prev_output{};

  public:

    Complex step(Complex sample) {
      const Complex out{a * sample + prev_input - a * prev_output};
      prev_input = sample;
      prev_output = out;

      return out;
    }
  };

  static_assert(
    SampleStepper<AllPass<2.0>, Complex>,
    "AllPass stepper doesn't work as a sample stepper"
  );

  template<double R, std::size_t L>
  class Comb {
    const double coeff{std::pow(R, L)};
    std::size_t count{0};
    std::array<Complex, L> delayed_samples{};

  public:

    Complex step(Complex sample) {
      const std::size_t index{count % L};
      const Complex out{sample + coeff * delayed_samples[index]};

      delayed_samples[index] = out;
      count++;

      return out;
    }
  };

  static_assert(
    SampleStepper<Comb<0.0, 0>, Complex>,
    "Comb stepper doesn't work as a sample stepper"
  );

  template<SampleStepper<Complex>... Ts>
  void apply_filters(std::vector<Complex>& samples) {
    ComposedFilter<Complex, Ts...> filter{};

    for (Complex& sample: samples) {
      sample = filter.step(sample);
    }
  }

  void normalize(std::vector<Complex>& values, const double target_db);
} // namespace filters
