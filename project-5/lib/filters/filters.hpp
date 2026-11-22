#pragma once

#include <cmath>
#include <cstddef>
#include <queue>
#include <tuple>
#include <utility>
#include "complex.hpp"

namespace filters {
  // Trait that defines what a filter needs to be defined as a filter
  template<typename T, typename S> concept SampleStepper =
    requires(T& stepper, S sample) {
      typename T::Config;
      { stepper.apply_config(std::declval<typename T::Config>()) };
      { stepper.step(sample) } -> std::convertible_to<S>;
    };

  template<typename Sample, SampleStepper<Complex>... S>
  class ComposedFilter {
  public:

    std::tuple<S...> stages{};

    Sample step(Sample sample) {
      return std::apply(
        [&](auto&... stage) { return ((sample = stage.step(sample)), ...); },
        stages
      );
    }
  };

  class LowPass {
    Complex prev_input{};
    double a{};

  public:

    struct Config {
      double a{};
    };

    void apply_config(const Config config) { a = config.a; }

    Complex step(Complex sample) {
      const Complex out{sample + a * prev_input};
      prev_input = sample;

      return out;
    }
  };

  static_assert(
    SampleStepper<LowPass, Complex>,
    "LowPass stepper doesn't work as a sample stepper"
  );

  class AllPass {
    Complex prev_input{};
    Complex prev_output{};
    double a{};

  public:

    struct Config {
      double a{};
    };

    void apply_config(const Config config) { a = config.a; }

    Complex step(Complex sample) {
      const Complex out{a * sample + prev_input - a * prev_output};
      prev_input = sample;
      prev_output = out;

      return out;
    }
  };

  static_assert(
    SampleStepper<AllPass, Complex>,
    "AllPass stepper doesn't work as a sample stepper"
  );

  class Comb {
    double coeff{};
    std::size_t count{0};
    std::queue<Complex> delayed_samples{};
    double R{};
    double L{};

  public:

    struct Config {
      double R{};
      double L{};
    };

    void apply_config(const Config config) {
      count = 0;
      R = config.R;
      L = config.L;
      coeff = std::pow(R, L);

      for (std::size_t i{0}; i < L; i++) {
        delayed_samples.push(Complex::zero());
      }
    }

    Complex step(Complex sample) {
      const Complex out{sample + coeff * delayed_samples.front()};
      delayed_samples.pop();

      delayed_samples.push(out);
      count++;

      return out;
    }
  };

  static_assert(
    SampleStepper<Comb, Complex>,
    "Comb stepper doesn't work as a sample stepper"
  );

  template<SampleStepper<Complex>... Ts, typename... C>
  void apply_filters(std::tuple<C...> configs, std::vector<Complex>& samples) {
    ComposedFilter<Complex, Ts...> filter{};

    // Applying the config for each filter
    std::apply(
      [&](auto&... stage) {
        [&]<std::size_t... Is>(std::index_sequence<Is...>) {
          (stage.apply_config(std::get<Is>(configs)), ...);
        }(std::make_index_sequence<sizeof...(stage)>{});
      },
      filter.stages
    );

    for (Complex& sample: samples) {
      sample = filter.step(sample);
    }
  }

  void normalize(std::vector<Complex>& values, const double target_db);
} // namespace filters
