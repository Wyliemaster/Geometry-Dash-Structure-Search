#pragma once
#include <zlib.h>
#include <string>
#include <stdexcept>
#include <functional>

#define GZIP_INITIAL_CHUNK_SIZE UINT16_MAX << 4 | 0xF
#define GZIP_BUFFER_FACTOR 2

struct Gzip {
    static std::string compress(std::string const& data, int compressionLevel = Z_DEFAULT_COMPRESSION);
    static std::string decompress(std::string const& data);
    static z_stream prepare(std::string const& data, unsigned char** output);
    static std::string read(
        z_stream& stream,
        std::string const& data,
        unsigned char** output,
        int flush,
        std::function<int(z_stream*, int)> reader,
        std::function<int(z_stream*)> ender
    );
};