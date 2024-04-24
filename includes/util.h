#ifndef __UTIL__
#define __UTIL__

#include <fstream>
#include <algorithm>
#include <filesystem>

#include "GJGameLevel.h"
#include "settings.h"

std::string ReadFile(const std::string& path)
{
    std::ifstream t(path);
    std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());

    t.close(); // Close file stream
    return str;
}

const std::vector<std::string>& getAllFilesInDirectory(const std::string& directoryPath) {
    size_t numFiles = std::distance(std::filesystem::directory_iterator(directoryPath),
        std::filesystem::directory_iterator());

    std::vector<std::string> filePaths;
    filePaths.reserve(numFiles);

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        filePaths.push_back(entry.path().string());
    }
    return filePaths;
}

bool DistanceSort(const Object& l, const Object& r)
{
    if (l.getposition_x() < r.getposition_x())
        return true;
    else if (l.getposition_x() > r.getposition_x())
        return false;
    else
        return l.getposition_y() < r.getposition_y(); // Secondary Sort by Y pos
}

bool FloatSort(float l, float r)
{
    return l < r;
}

void sortLevel(std::vector<Object>& level)
{
    std::sort(level.begin(), level.end(), DistanceSort);
}

void sortFloatVec(std::vector<float>& data)
{
    std::sort(data.begin(), data.end(), FloatSort);
}

bool isLevelCorrectVersion(const std::vector<Object>& level)
{
    if (!Settings::get()->VERSION_CHECK)
    {
        return true;
    }

    for (const Object& obj : level)
    {
        if (obj.getposition_x() > Settings::get()->LEVEL_LENGTH_LIMIT ||
            (obj.getrotation() % 90 != 0 && Settings::get()->CHECK_90_DEGREES))
        {
            return false; // Return false as soon as an incorrect version is found
        }
    }

    return true; // If all objects pass the checks
}

std::vector<Object> normalise(std::vector<Object>& obj)
{
    if (obj.empty())
    {
        return obj;
    }

    std::vector<Object> normalised;

    sortLevel(obj);

    int x = obj[0].getposition_x();
    int y = obj[0].getposition_y();

    for (const Object& o : obj)
    {
        x = std::min(x, o.getposition_x());
        y = std::min(y, o.getposition_y());
    }

    for (const Object& object : obj)
    {
        Object normalizedObject = object;
        normalizedObject.setposition_x(object.getposition_x() - x);
        normalizedObject.setposition_y(object.getposition_y() - y);

        normalised.emplace_back(normalizedObject);
    }

    return normalised;
}
#endif
