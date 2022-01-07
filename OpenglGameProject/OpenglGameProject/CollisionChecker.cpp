#include "CollisionChecker.hpp"



CollisionChecker::CollisionChecker()
{
}


CollisionChecker::~CollisionChecker()
{
}


bool CollisionChecker::CollisionCheck(Object* p_obj1, Object* p_obj2)
{
    if (p_obj1->GetMesh().mesh_polygon_type == MeshPolygonType::Circle &&
        p_obj2->GetMesh().mesh_polygon_type == MeshPolygonType::Circle)
        return ComputeCircleCollision(p_obj1, p_obj2);

    if (p_obj1->GetMesh().mesh_polygon_type == MeshPolygonType::Box &&
        p_obj2->GetMesh().mesh_polygon_type == MeshPolygonType::Box)
        return ComputeAABBCollision(p_obj1, p_obj2);

    if (p_obj1->GetMesh().mesh_polygon_type == MeshPolygonType::Circle &&
        p_obj2->GetMesh().mesh_polygon_type == MeshPolygonType::Box)
        return ComputeCircleAABBCollision(p_obj1, p_obj2);

    if (p_obj1->GetMesh().mesh_polygon_type == MeshPolygonType::Box &&
        p_obj2->GetMesh().mesh_polygon_type == MeshPolygonType::Circle)
        return ComputeCircleAABBCollision(p_obj1, p_obj2);
    return false;
}

//회전한 박스 충돌 만들고 싶으면 OBB만들어야함....
bool CollisionChecker::ComputeAABBCollision(Object * p_obj1, Object * p_obj2)
{
    vector2 obj1_min, obj1_max;
    vector2 obj2_min, obj2_max;
    ComputeMinMaxAABB(p_obj1, obj1_min, obj1_max);
    ComputeMinMaxAABB(p_obj2, obj2_min, obj2_max);

    if (obj1_max.x < obj2_min.x || obj1_min.x > obj2_max.x) return false;
    if (obj1_max.y < obj2_min.y || obj1_min.y > obj2_max.y) return false;
    return true;
}

bool CollisionChecker::ComputeCircleAABBCollision(Object* p_obj1, Object* p_obj2)
{
    vector2 boxmin, boxmax;
    vector2 circlepos, boxpos;
    float radius;
    if (p_obj1->GetMesh().mesh_polygon_type == MeshPolygonType::Circle)
    {
        circlepos = p_obj1->GetTransform().GetTranslation();
        radius = p_obj1->GetTransform().GetScale().x;
        ComputeMinMaxAABB(p_obj2, boxmin, boxmax);
        boxpos = p_obj2->GetTransform().GetTranslation();
    }
    else
    {
        circlepos = p_obj2->GetTransform().GetTranslation();
        radius = p_obj2->GetTransform().GetScale().x;
        ComputeMinMaxAABB(p_obj1, boxmin, boxmax);
        boxpos = p_obj1->GetTransform().GetTranslation();
    }

    //원의 반지름만큼 사각형을 확장한다//몰라 이렇게 하래
    vector2 scaledboxmin, scaledboxmax;
    scaledboxmin = boxmin - radius; scaledboxmax = boxmax + radius;

    //확장한 사각형 안에 원의 중심이 들어있는 지 파악
    if (circlepos.x > scaledboxmin.x && circlepos.x < scaledboxmax.x &&
        circlepos.y>scaledboxmin.y && circlepos.y < scaledboxmax.y)
        return true;

    //사각형 각각의 꼭짓점들이 원 안에 있는지(이거는 딱 최대 길이밖에 안댐 이해 안되면 그려보셈)
    if (distance_between(circlepos, boxmin) < radius) return true;
    if (distance_between(circlepos, boxmax) < radius) return true;
    if (distance_between(circlepos, vector2(boxmin.x, boxmax.y)) < radius) return true;
    if (distance_between(circlepos, vector2(boxmax.x, boxmin.y)) < radius) return true;

    return false;
}

bool CollisionChecker::ComputeCircleCollision(Object * p_obj1, Object * p_obj2)
{
    vector2 trans1 = p_obj1->GetTransform().GetTranslation();
    vector2 trans2 = p_obj2->GetTransform().GetTranslation();
    float distance = sqrt((trans2.y - trans1.y)*(trans2.y - trans1.y) +
        (trans2.x - trans1.x)*(trans2.x - trans1.x));
    float standard = p_obj1->GetTransform().GetScale().x + p_obj2->GetTransform().GetScale().x;

    if (distance > standard) //touch really doesnt mean collide.. dont be tough
        return false;
    else
        return true;
}

void CollisionChecker::ComputeMinMaxAABB(Object* p_obj, vector2& min, vector2& max)
{
    //엄청 야매로 해놨으니 나중에 고칠 것..
    //vector2 maxpos, minpos = p_obj->GetTransform().GetTranslation();//p_obj->GetMesh().GetPoint(0);
    //min = p_obj->GetTransform().GetTranslation() - p_obj->GetTransform().GetScale() / 2;
    //max = p_obj->GetTransform().GetTranslation() + p_obj->GetTransform().GetScale() / 2;
    //아니 왜 안되냑오ㅠㅠㅠㅠㅠㅠ
    //getModelToWorld * min을 해도 위의 결과대로 안 나옴.....//affine2d*vector3 가 문제였음 고쳤음
    vector2 minTemp = p_obj->GetMesh().GetMin();
    vector2 maxTemp = p_obj->GetMesh().GetMax();
    min = p_obj->GetTransform().GetModelToWorld() * minTemp;
    max = p_obj->GetTransform().GetModelToWorld() * maxTemp;
}