#pragma once
#include "Object.hpp"

class CollisionChecker
{
public:
    CollisionChecker();
    ~CollisionChecker();

    bool CollisionCheck(Object* p_obj1, Object* p_obj2);
    void ComputeMinMaxAABB(Object* p_obj, vector2& min, vector2& max);

private:
    bool ComputeAABBCollision(Object* p_obj1, Object* p_obj2); //Box-Box
    bool ComputeCircleCollision(Object* p_obj1, Object* p_obj2); //Circle-Circle
    bool ComputeCircleAABBCollision(Object* p_obj1, Object* p_obj2); //Circle-box
  
};

