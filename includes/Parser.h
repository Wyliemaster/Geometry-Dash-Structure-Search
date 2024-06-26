#ifndef __LEVEL_PARSER__
#define __LEVEL_PARSER__

#include <iostream>
#include <sstream>
#include <vector>
#include <memory.h>

#include "GJGameLevel.h"
#include "base64.h"
#include "Gzip.hpp"
#include "settings.h"

// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

Object getObject(std::vector<std::string> obj)
{


    Object object;
    for (size_t i = 0; i < obj.size() && obj.size() % 2 == 0; i++)
    {
        int p_id = atoi(obj[i].c_str());
        int p_value = atoi(obj[i + 1].c_str());

        switch (p_id)
        {
        case 1:
            object.setobjectId(p_value);
            break;
        case 2:
            object.setposition_x(p_value);
            break;
        case 3:
            object.setposition_y(p_value);
            break;
        case 6:
            object.setrotation(p_value);
            break;
        default:
            break;
        }

        i++;
    }
    return object;
}

std::vector<Object> parseLevel(std::string level)
{
    std::vector<Object> v;
    auto objs = split(level, ";");

    for (std::string &obj : objs)
    {
        if (obj.substr(0, 1) == "k") continue;

        auto properties = split(obj, ",");

        if (properties.size() == 1) continue;

        auto object = getObject(properties);

        v.push_back(std::move(object));
    }

    return v;
}

#include <fstream>
#include <chrono>
#include <sstream>
#include <ctime>
#include <vector>
#include <string>
#include <stdexcept>

std::vector<Object> parseLevelCompressed(std::string level)
{
    try {
        std::vector<unsigned char> data(level.begin(), level.end());
        std::unique_ptr<base64> decoder = std::make_unique<base64>(data);

        auto decoded = decoder->decode();

        std::string str(decoded.begin(), decoded.end());
        std::string decompressed = Gzip::decompress(str);

        decoded.clear();

        return parseLevel(decompressed);
    }
    catch(const std::exception& err)
    {
        // Write error to file
        std::ostringstream filenameStream;
        filenameStream << std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch()).count();
        std::string filename = "DECOMPRESSION_ERROR_" + filenameStream.str() + ".GD";

        std::ofstream errorFile(filename);
        if (errorFile.is_open()) {
            errorFile << level << std::endl;
            errorFile.close();
        }

        printf("%s", LOG_DIVIDER);
        printf("ERROR: Failed to decompress level!\nSaving level data inside of: %s\n", filename.c_str());
        printf("%s", LOG_DIVIDER);

        return {};
    }
}


#endif