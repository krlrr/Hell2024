#pragma once
#include "recast/Recast.h"
#include "NavMesh.h"

struct Path {
    glm::vec3 start;
    glm::vec3 end;
    std::vector<glm::vec3> points;
    bool Found() {
        return points.size();
    }
};

namespace Pathfinding2 {
    void Init();
    void Update(float deltaTime);
    void UpdateNavMesh(std::vector<glm::vec3>& vertices);
    Path FindPath(glm::vec3 startPos, glm::vec3 endPos);
    std::vector<glm::vec3>& GetDebugVertices();
    rcContext* GetRecastContext();
}