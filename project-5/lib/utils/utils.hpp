#pragma once

#include <cstdint>
#include <optional>
#include <string_view>
#include <vector>

#include "complex.hpp"

namespace utils {
std::optional<std::vector<Complex>>
read_file(std::string_view file_path, std::optional<std::size_t> read_until);
} // namespace utils

struct WavData {
  struct ChunkHeader{
    std::uint32_t type{0};
    std::uint32_t size{0};
  };
  static_assert(sizeof(ChunkHeader) == 8, "ChunkHeader must be 8 bytes");

  struct RiffChunk{
    ChunkHeader header;

    std::uint32_t file_format{0};
  };
  static_assert(sizeof(RiffChunk) == 12, "RiffChunk must be 12 bytes");

  struct FormatChunk{
    ChunkHeader header;

    std::uint16_t audio_format{0};
    std::uint16_t channel_count{0};

    std::uint32_t sample_rate{0};
    std::uint32_t bytes_per_second{0};

    std::uint16_t bytes_per_block{0}; // Bytes per "frame"
    std::uint16_t bits_per_sample{0};
  };
  static_assert(sizeof(FormatChunk) == 24, "FormatChunk must be 24 bytes");

  struct DataChunk{
    ChunkHeader header;
  };

  static std::optional<WavData> read_wav(std::string_view file_path);
  static void write_wav(std::string_view file_name, const WavData &wav_data);

  RiffChunk riff{};
  FormatChunk fmt{};
  DataChunk data_info{};

  std::vector<Complex> samples{};
};
