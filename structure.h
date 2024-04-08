#include <vector>
#include <cmath>

#include "GJGameLevel.h"
#include "settings.h"

typedef std::vector<Object> ObjectCollection;

namespace structure
{
    void exploreNeighbors(const std::vector<Object>& objects, std::vector<Object>& currentStruct, std::vector<bool>& visited, int index)
    {
        visited[index] = true;
        const Object& obj = objects[index];
        currentStruct.push_back(obj);

        int x1 = obj.getposition_x();
        int y1 = obj.getposition_y();

        for (size_t j = 0; j < objects.size(); j++)
        {
            if (!visited[j])
            {
                const Object& nextObj = objects[j];
                int x2 = nextObj.getposition_x();
                int y2 = nextObj.getposition_y();
                float distance = std::sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                if (distance <= Settings::get()->OBJECT_SIZE)
                {
                    exploreNeighbors(objects, currentStruct, visited, j);
                }
            }
        }
    }

    std::vector<ObjectCollection> getStructures(std::vector<Object> objects)
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
                    structures.push_back(currentStruct);
                }
            }
        }

        return structures;
    }



    float calculateDistance(const Object& obj1, const Object& obj2) {
        return std::sqrt(std::pow(obj1.getposition_x() - obj2.getposition_x(), 2) + std::pow(obj1.getposition_y() - obj2.getposition_y(), 2));
    }

    float compareStructures(const std::vector<Object>& structure1, const std::vector<Object>& structure2) 
    {
        const std::vector<Object>& biggest = structure1.size() >= structure2.size() ? structure1 : structure2;
        const std::vector<Object>& smallest = structure1.size() < structure2.size() ? structure1 : structure2;

        std::vector<float> matched;

        for (Object obj1 : biggest)
        {
            for (Object obj2 : smallest)
            {
                if (obj1.getobjectId() == obj2.getobjectId() && calculateDistance(obj1, obj2) < Settings::get()->OBJECT_SIZE)
                {
                    auto o = obj1.getobjectId(), o2 = obj2.getobjectId();

                        float simularity_score = (1.0f - (calculateDistance(obj1, obj2) / Settings::get()->OBJECT_SIZE));
                        matched.push_back(simularity_score);
                }
            }
        }

        int size = matched.size();

        if (size == 0) return 0.0f;

        float final_score = 0.0f;

        for (size_t i = 0; i < size; i++)
        {
            final_score += matched[i];
        }

        return final_score / size;

    }
}
