#pragma once
#include "../Common.h"
#include "../Physics/Physics.h"

struct BulletCasing {

    //Weapon type;
    PxRigidBody* rigidBody = NULL;
    float audioDelay = 0.0f;
    float lifeTime = 0.0f;
    glm::mat4 modelMatrix = glm::mat4(1);

    void CleanUp();
    glm::mat4 GetModelMatrix();
    void Update(float deltaTime);
    void CollisionResponse();
    bool HasActivePhysics();
    bool collisionsEnabled = false;
    int modelIndex;
    int materialIndex;
};
