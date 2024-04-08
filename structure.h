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
}
