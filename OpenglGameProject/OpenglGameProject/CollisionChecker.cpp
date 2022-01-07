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

//ȸ���� �ڽ� �浹 ����� ������ OBB��������....
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

    //���� ��������ŭ �簢���� Ȯ���Ѵ�//���� �̷��� �Ϸ�
    vector2 scaledboxmin, scaledboxmax;
    scaledboxmin = boxmin - radius; scaledboxmax = boxmax + radius;

    //Ȯ���� �簢�� �ȿ� ���� �߽��� ����ִ� �� �ľ�
    if (circlepos.x > scaledboxmin.x && circlepos.x < scaledboxmax.x &&
        circlepos.y>scaledboxmin.y && circlepos.y < scaledboxmax.y)
        return true;

    //�簢�� ������ ���������� �� �ȿ� �ִ���(�̰Ŵ� �� �ִ� ���̹ۿ� �ȴ� ���� �ȵǸ� �׷�����)
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
    //��û �߸ŷ� �س����� ���߿� ��ĥ ��..
    //vector2 maxpos, minpos = p_obj->GetTransform().GetTranslation();//p_obj->GetMesh().GetPoint(0);
    //min = p_obj->GetTransform().GetTranslation() - p_obj->GetTransform().GetScale() / 2;
    //max = p_obj->GetTransform().GetTranslation() + p_obj->GetTransform().GetScale() / 2;
    //�ƴ� �� �ȵǳſ��ФФФФФ�
    //getModelToWorld * min�� �ص� ���� ������ �� ����.....//affine2d*vector3 �� �������� ������
    vector2 minTemp = p_obj->GetMesh().GetMin();
    vector2 maxTemp = p_obj->GetMesh().GetMax();
    min = p_obj->GetTransform().GetModelToWorld() * minTemp;
    max = p_obj->GetTransform().GetModelToWorld() * maxTemp;
}