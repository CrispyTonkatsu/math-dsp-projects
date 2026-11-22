#include "utils.hpp"
#include "parser.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <optional>

std::optional<std::vector<Complex>>
utils::read_file(std::string_view file_path,
                 std::optional<std::size_t> read_until) {
  std::ifstream file{file_path.data()};

  if (!file.is_open()) {
    std::cerr << "File not found: " << file_path << "\n";
    return std::nullopt;
  }

  std::vector<Complex> output;
  std::size_t lines_read{0};

  while (!file.eof()) {
    std::string buffer{};
    std::getline(file, buffer);

    const std::optional<Complex> number_opt{parse_cartesian(buffer)};
    if (!number_opt) {
      std::cerr << "Invalid Number: " << buffer << "\n";
      return std::nullopt;
    }

    output.push_back(number_opt.value());
    lines_read++;

    if (read_until && lines_read == *read_until) {
      break;
    }
  }

  if (read_until && output.size() != *read_until) {
    std::cerr << "Not enough numbers: " << *read_until << "\n";
    return std::nullopt;
  }

  return output;
}

template <typename T>
std::optional<T> skip_until_chunk(std::fstream &stream, std::string_view type,
                                  bool copy_data = false) {
  WavData::ChunkHeader header{};

  while (stream.read(reinterpret_cast<char *>(&header),
                     sizeof(WavData::ChunkHeader))) {
    if (std::memcmp(&header.type, type.data(), 4) == 0) {
      T output;

      memcpy(reinterpret_cast<std::byte *>(&output),
             reinterpret_cast<std::byte *>(&header), sizeof(header));

      if (copy_data) {
        char *chunk_data{new char[header.size]};
        stream.read(chunk_data, header.size);

        memcpy(reinterpret_cast<std::byte *>(&output) + sizeof(header),
               chunk_data, header.size);

        delete[] chunk_data;
      }

      return output;
    }

    stream.seekg(header.size, std::ios::cur);
  }

  return std::nullopt;
}

std::optional<WavData> WavData::read_wav(std::string_view file_path) {
  std::fstream file{
      file_path.data(),
      std::ios_base::binary | std::ios_base::in,
  };

  if (!file.is_open()) {
    std::cerr << "Wav file not found: " << file_path << "\n";
    return std::nullopt;
  }

  WavData output{};

  file.read(reinterpret_cast<char *>(&output.riff), 12);
  if (std::memcmp(&output.riff.header.type, "RIFF", 4) != 0 ||
      std::memcmp(&output.riff.file_format, "WAVE", 4) != 0) {
    std::cerr << "Invalid RIFF for file: " << file_path << "\n";
    return std::nullopt;
  }

  std::optional<FormatChunk> fmt_opt{
      skip_until_chunk<FormatChunk>(file, "fmt ", true)};
  if (!fmt_opt.has_value()) {
    std::cerr << "Could not find the FMT for the file: " << file_path << "\n";
    return std::nullopt;
  }

  output.fmt = fmt_opt.value();

  if (output.fmt.audio_format != 1) {
    std::cerr << "The audio needs samples of 16bit PCM mono";
    return std::nullopt;
  }

  if (output.fmt.channel_count != 1) {
    std::cerr << "The audio needs samples of 16bit mono";
    return std::nullopt;
  }

  if (output.fmt.bytes_per_block != 2) {
    std::cerr << "The audio needs samples of 16bit PCM mono";
    return std::nullopt;
  }

  if (output.fmt.bits_per_sample != 16) {
    std::cerr << "The audio needs samples of 16bit PCM mono";
    return std::nullopt;
  }

  std::optional<DataChunk> data_opt{skip_until_chunk<DataChunk>(file, "data")};
  if (!data_opt.has_value()) {
    std::cerr << "Could not find the data for the audio: " << file_path << "\n";
    return std::nullopt;
  }

  output.data_info = data_opt.value();

  constexpr double max_amplitude{1 << 15};

  const std::size_t short_count{output.data_info.header.size / 2};
  output.samples.reserve(short_count);

  for (std::size_t i{0}; i < short_count; i++) {
    std::int16_t sample{0};
    file.read(reinterpret_cast<char *>(&sample), sizeof(std::int16_t));

    output.samples.push_back(Complex::from_cartesian(
        static_cast<double>(sample) / max_amplitude, 0.0f));
  }

  return output;
}

void WavData::write_wav(std::string_view file_name, const WavData &wav_data) {
  std::fstream file{
      file_name.data(),
      std::ios_base::binary | std::ios_base::out,
  };

  file.write(reinterpret_cast<const char *>(&wav_data.riff),
             sizeof(wav_data.riff));
  file.write(reinterpret_cast<const char *>(&wav_data.fmt),
             sizeof(wav_data.fmt));

  file.write(reinterpret_cast<const char *>(&wav_data.data_info),
             sizeof(wav_data.data_info));

  constexpr double max_amplitude{1 << 15};

  const std::size_t short_count{wav_data.samples.size()};
  for (std::size_t i{0}; i < short_count; i++) {
    const double safe_sample{
        std::clamp(wav_data.samples[i].get_real(), -1.0, 1.0)};

    const std::int16_t output_sample{
        static_cast<std::int16_t>(safe_sample * max_amplitude)};

    file.write(reinterpret_cast<const char *>(&output_sample), sizeof(output_sample));
  }
}
