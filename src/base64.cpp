#include "../includes/base64.h"
base64::base64(const char* data, size_t size)
{
    this->data = data;
    this->size = size;
}

base64::~base64()
{
    delete[] data;
}

bool base64::isValidBase64()
{
    // If the data is not padded, it will reject
    if (this->size == 0 || this->size % 4 != 0)
    {
        return false;
    }

    for (size_t i = 0; i < this->size; ++i)
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

    std::vector<unsigned char> decoded;
    for (size_t i = 0; i < this->size; i += 4)
    {
        uint32_t data = 0;

        for (size_t j = 0; j < 4; j++)
        {
            if (base64::m_indexes[this->data[i + j]] != 64)
            {
                data += base64::m_indexes[this->data[i + j]] << (3 - j) * 6;
            }
        }
        decoded.push_back(static_cast<unsigned char>((data >> 16) & 0xFF));
        decoded.push_back(static_cast<unsigned char>((data >> 8) & 0xFF));
        decoded.push_back(static_cast<unsigned char>(data & 0xFF));
    }
    return decoded;
}