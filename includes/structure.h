#include <vector>
#include <cmath>
#include <queue>

#include "GJGameLevel.h"
#include "settings.h"

typedef std::vector<Object> ObjectCollection;

namespace structure
{
    float calculateDistance(const Object& obj1, const Object& obj2) {
        return std::sqrt(std::pow(obj1.getposition_x() - obj2.getposition_x(), 2) + std::pow(obj1.getposition_y() - obj2.getposition_y(), 2));
    }

    void exploreNeighbors(const std::vector<Object>& objects, ObjectCollection& currentStruct, std::vector<bool>& visited, int index)
    {
        std::queue<int> toVisit;
        toVisit.push(index);

        while (!toVisit.empty()) {
            int currentIdx = toVisit.front();
            toVisit.pop();

            if (visited[currentIdx]) {
                continue;
            }

            visited[currentIdx] = true;
            const Object& obj = objects[currentIdx];
            currentStruct.push_back(obj);

            for (size_t j = 0; j < objects.size(); ++j) {
                if (!visited[j]) {
                    const Object& nextObj = objects[j];
                    float distance = calculateDistance(obj, nextObj);
                    if (distance <= Settings::get()->OBJECT_SIZE) {
                        toVisit.push(j);
                    }
                }
            }
        }
    }

    std::vector<ObjectCollection> getStructures(std::vector<Object>& objects)
    {
        std::vector<ObjectCollection> structures;
        std::vector<bool> visited(objects.size(), false);

        for (size_t i = 0; i < objects.size(); i++)
        {
            if (!visited[i])
            {
                ObjectCollection currentStruct;
                exploreNeighbors(objects, currentStruct, visited, i);
                if (!currentStruct.empty())
                {
                    structures.push_back(std::move(currentStruct)); // Move instead of copy
                }
                currentStruct.clear();
            }
        }

        visited.clear();

        return structures;
    }

    float compareStructures(const std::vector<Object>& structure1, const std::vector<Object>& structure2)
    {
        const std::vector<Object>& biggest = structure1.size() >= structure2.size() ? structure1 : structure2;
        const std::vector<Object>& smallest = structure1.size() < structure2.size() ? structure1 : structure2;

        std::vector<float> matched;
        matched.reserve(biggest.size());

        for (const Object& obj1 : biggest)
        {
            // If no match is found, it will add 0
            float bestMatch = 0.0f;
            for (const Object& obj2 : smallest)
            {
                if (obj1.getobjectId() == obj2.getobjectId()) 
                {
                    // Check if the object is in the correct grid square
                    float distance = calculateDistance(obj1, obj2);
                    if (distance <= Settings::get()->OBJECT_SIZE)
                    {
                        bestMatch = std::max(bestMatch, 1.0f - (distance / Settings::get()->OBJECT_SIZE));
                    }
                }
            }
            matched.push_back(bestMatch);
        }

        // If there object count differs then it shouldn't
        // return a 100% match. adding 0 to deduct accuracy
        // should reduce false positives
        int diff = biggest.size() - smallest.size();

        for (size_t i = 0; i < diff; i++)
        {
            matched.push_back(0);
        }

        // Avoid a divide by 0 error
        if (matched.size() == 0) return 0.0f;

        float final_score = 0.0f;
        for (size_t i = 0; i < matched.size(); i++)
        {
            final_score += matched[i];
        }

        return final_score / matched.size();
    }
}
