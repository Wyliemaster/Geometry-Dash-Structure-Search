#ifndef __LEVEL_PARSER__
#define __LEVEL_PARSER__

#include <iostream>
#include <sstream>
#include <vector>
#include "GJGameLevel.h"
#include "lib/Include/GDCrypto.hpp"

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

Level getObject(std::vector<std::string> obj)
{


    Level object = {};
    for (size_t i = 0; i < obj.size() && obj.size() % 2 == 0; i++)
    {


        auto p_id = atoi(obj[i].c_str());
        auto p_value = atoi(obj[i + 1].c_str());

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
        case 4:
            object.setflip_x(p_value == 1);
            break;
        case 5:
            object.setflip_y(p_value == 1);
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

std::vector<Level> parseLevel(std::string level)
{
    std::vector<Level> v;
    auto objs = split(level, ";");

    for (std::string obj : objs)
    {
        if (obj.substr(0, 1) == "k") continue;

        auto properties = split(obj, ",");

        if (properties.size() == 1) continue;

        v.push_back(getObject(properties));
    }

    return v;
}

std::vector<Level> parseLevelCompressed(std::string level)
{
    auto c = new gdcrypto::LevelDataCipher;
    auto d = c->decode(level);

    auto decompressed = std::string(d.begin(), d.end());

    return parseLevel(decompressed);
}

#endif