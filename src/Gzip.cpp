#include "../includes/Gzip.hpp"

std::string Gzip::compress(std::string const& data, int compressionLevel) {
    unsigned char* output = nullptr;
    z_stream stream = Gzip::prepare(data, &output);

    if (deflateInit2(&stream, compressionLevel, Z_DEFLATED, MAX_WBITS | 0x10, 8, Z_DEFAULT_STRATEGY) == Z_OK) {
        return Gzip::read(stream, data, &output, Z_FINISH, deflate, deflateEnd);
    }
    else {
        throw std::runtime_error("Failed to initialize Gzip stream");
    }
}

std::string Gzip::decompress(const std::string& data) {
    if (data.empty()) {
        return "";
    }
    else {
        unsigned char* output = nullptr;
        z_stream stream = Gzip::prepare(data, &output);

        if (inflateInit2(&stream, 15 + 32) == Z_OK) {
            return Gzip::read(stream, data, &output, Z_NO_FLUSH, inflate, inflateEnd);
        }
        else {
            throw std::runtime_error("Failed to initialize Gzip stream");
        }
    }
}

z_stream Gzip::prepare(std::string const& data, unsigned char** output) {
    z_stream stream;

    stream.zalloc = Z_NULL;
    stream.opaque = Z_NULL;
    stream.zfree = Z_NULL;

    stream.next_in = (unsigned char*)data.data();
    stream.avail_in = data.size();
    stream.next_out = *output = (unsigned char*)malloc(GZIP_INITIAL_CHUNK_SIZE);
    stream.avail_out = GZIP_INITIAL_CHUNK_SIZE;

    return stream;
}

std::string Gzip::read(
    z_stream& stream,
    std::string const& data,
    unsigned char** output,
    int flush,
    std::function<int(z_stream*, int)> reader,
    std::function<int(z_stream*)> ender
) {
    size_t buffer = GZIP_INITIAL_CHUNK_SIZE;
    int status;

    do {
        status = reader(&stream, flush);

        if (status == Z_OK) {
            *output = (unsigned char*)realloc(*output, buffer * GZIP_BUFFER_FACTOR);
            stream.next_out = *output + buffer;
            stream.avail_out = buffer;
            buffer *= GZIP_BUFFER_FACTOR;
        }
        else {
            break;
        }
    } while (1);

    std::string result((char*)*output, stream.total_out);

    free(*output);

    if (ender(&stream) == Z_OK && status == Z_STREAM_END) {
        return result;
    }
    else {
        throw std::runtime_error("Unexpected end of Gzip stream");
    }
}