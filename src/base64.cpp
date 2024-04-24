#include "../includes/base64.h"
base64::base64(std::vector<unsigned char> data)
{
    this->data = data;
}

base64::~base64()
{
    this->data.clear();
}

bool base64::isValidBase64()
{
    size_t size = this->data.size();

    // If the data is not padded, it will reject
    if (size == 0 || size % 4 != 0)
    {
        return false;
    }

    for (size_t i = 0; i < size; ++i)
    {
        unsigned char c = this->data[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '='))
        {
            return false;
        }
    }

    return true;
}

std::vector<unsigned char> base64::decode()
{
    if (!this->isValidBase64())
    {
        return {};
    }

    size_t size = this->data.size();

    std::vector<unsigned char> decoded;
    decoded.reserve(size * 0.75);
    for (size_t i = 0; i < size; i += 4)
    {
        uint32_t data = 0;

        for (size_t j = 0; j < 4; j++)
        {
            if (base64::m_indexes[this->data[i + j]] != 64)
            {
                // base64 only uses 6 bits so we are shifting it left by 6j
                data += base64::m_indexes[this->data[i + j]] << (3 - j) * 6;
            }
        }

        decoded.emplace_back(static_cast<unsigned char>((data >> 16) & 0xFF));
        decoded.emplace_back(static_cast<unsigned char>((data >> 8) & 0xFF));
        decoded.emplace_back(static_cast<unsigned char>(data & 0xFF));
    }
    return decoded;
}