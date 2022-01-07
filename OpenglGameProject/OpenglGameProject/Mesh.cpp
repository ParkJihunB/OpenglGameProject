#include "Mesh.hpp"

void Mesh::AddPoint(vector2 point)
{
    if (points.size() == 0)
    {
        min = point;
        max = point;
    }
    else
    {
        if (point.x < min.x) min.x = point.x;
        if (point.y < min.y) min.y = point.y;
        if (point.x > max.x) max.x = point.x;
        if (point.y > max.y) max.y = point.y;
    }
	points.push_back(point);
}

void Mesh::AddColor(Color color)
{
	for (unsigned i = 0; i < GetPointCount(); i++)
		colors.push_back(color);
}

void Mesh::ChangeColor(Color color)
{
	ClearColors();
	AddColor(color);
}

void Mesh::AddTextureCoordinate(vector2 texture_coordinate)
{
	textureCoordinates.push_back(texture_coordinate);
}

vector2 Mesh::GetPoint(std::size_t index) const
{
	vector2 temp{ points.at(index).x,points.at(index).y };
	return temp;
}

Color Mesh::GetColor(std::size_t index) const
{
	return colors.at(index);
}

vector2 Mesh::GetTextureCoordinate(std::size_t index) const
{
	return textureCoordinates[index];
}

PointTypeList Mesh::GetPointListType() const { return point_list_type; }
void Mesh::SetPointListType(PointTypeList type)
{
	point_list_type = type;
}

unsigned Mesh::GetPointCount() const
{
	return (unsigned)points.size();
}

unsigned Mesh::GetPointSize()
{
	return (unsigned)(points.size() * 3 * sizeof(float));
}

void Mesh::ClearColors()
{
	colors.clear();
}

void Mesh::ClearTextureCoordinates()
{
	textureCoordinates.clear();
}

void Mesh::Clear()
{
	points.clear();
	colors.clear();
	textureCoordinates.clear();
}

void Mesh::ChangeColors(Color color)
{
	for (unsigned i = 0; i < GetPointCount(); i++)
		colors.at(i) = color;
}

namespace mesh
{
	const float PI = 4.0f * std::atan(1.0f);

	Mesh CreateCircle(float radius, std::size_t pointCount)
	{
		Mesh mesh;

		for (int i = 1; i <= static_cast<int>(pointCount); i++)
		{
			mesh.AddPoint(vector2{ 0.f, 0.f });
			mesh.AddPoint(vector2{ radius*cos((i)*(2 * PI / pointCount)),
				radius*sin((i)*(2 * PI / pointCount)) });

			mesh.AddPoint(vector2{ radius*cos((i + 1)*(2 * PI / pointCount)),
				radius*sin((i + 1)*(2 * PI / pointCount)) });
		}
		mesh.AddPoint(vector2{ 0.f, 0.f });

		mesh.SetPointListType(PointTypeList::TriangleFan);
		return mesh;
	}


	Mesh CreateWireCircle(float radius, std::size_t pointCount)
	{
		Mesh mesh;
		for (int i = 0; i <= (int)pointCount; i++)
		{
			mesh.AddPoint(vector2{ radius*cos((i)*(2 * PI / pointCount)),
				radius*sin((i)*(2 * PI / pointCount)) });
		}
		mesh.SetPointListType(PointTypeList::LineStrip);
		return mesh;
	}

	Mesh CreateBox(float dimension)
	{
		Mesh mesh;
		mesh.AddPoint(0.5f*dimension*vector2{ -1,-1 });
		mesh.AddPoint(0.5f*dimension*vector2{ 1,-1 });
		mesh.AddPoint(0.5f*dimension*vector2{ 1,1 });
		mesh.AddPoint(0.5f*dimension*vector2{ -1,1 });
		mesh.AddPoint(0.5f*dimension*vector2{ -1,-1 });

		mesh.SetPointListType(PointTypeList::TriangleStrip);

		return mesh;
	}

	//Mesh CreateBoxi(float dimension, Color color)
	//{
	//	Mesh mesh;

	//	mesh.AddPoint(0.5f*dimension*vector2{ -1,1 });
	//	mesh.AddPoint(0.5f*dimension*vector2{ 1,1 });
	//	mesh.AddPoint(0.5f*dimension*vector2{ 1,-1 });
	//	mesh.AddPoint(0.5f*dimension*vector2{ -1,-1 });
	//	mesh.AddPoint(0.5f*dimension*vector2{ -1,1 });

	//	mesh.AddTextureCoordinate(dimension*vector2{ 0,0 });
	//	mesh.AddTextureCoordinate(dimension*vector2{ 1,0 });
	//	mesh.AddTextureCoordinate(dimension*vector2{ 1,1 });
	//	mesh.AddTextureCoordinate(dimension*vector2{ 0,1 });
	//	mesh.AddTextureCoordinate(dimension*vector2{ 0,0 });

	//	mesh.SetPointListType(PointTypeList::TriangleStrip);
	//	mesh.AddColor(color);

	//	return mesh;
	//}

	Mesh CreateWireBox(float dimension)
	{
		Mesh mesh;
		mesh.AddPoint(dimension* vector2{ 1.f, 1.f });
		mesh.AddPoint(dimension* vector2{ -1.f, 1.f });
		mesh.AddPoint(dimension* vector2{ -1.f,-1.f });
		mesh.AddPoint(dimension* vector2{ 1.f,-1.f });
		mesh.AddPoint(dimension* vector2{ 1.f, 1.f });

		mesh.SetPointListType(PointTypeList::LineStrip);
		return mesh;
	}

	Mesh CreateLine(vector2 a, vector2 b)
	{
		Mesh mesh;
		mesh.AddPoint(a);
		mesh.AddPoint(b);
		mesh.SetPointListType(PointTypeList::Lines);
		return mesh;
	}

	Mesh CreateLine(vector2 a, vector2 b, Color color)
	{
		Mesh mesh;
		mesh.AddPoint(a);
		mesh.AddPoint(b);
		mesh.SetPointListType(PointTypeList::Lines);
		mesh.AddColor(color);
		return mesh;
	}

	Mesh CreateTriangle(float scale)
	{
		Mesh mesh;
		mesh.AddPoint(scale * vector2{ 0.f,0.5f });
		mesh.AddPoint(scale* vector2{ 0.5f,0.f });
		mesh.AddPoint(scale * vector2{ -0.5f,0.f });
		mesh.SetPointListType(PointTypeList::Triangles);
		return mesh;
	}

	Mesh CreatePolygon(float radius, int pointCount)
	{
		Mesh mesh;
		for (int i = 0; i < pointCount; i++)
		{
			float a = 2 * PI * (i / (float)pointCount);
			mesh.AddPoint(vector2{ radius * cosf(a), radius * sinf(a) });
		}

		mesh.SetPointListType(PointTypeList::TriangleFan);
		return mesh;
	}
	Mesh CreateTextureBox(float dimension)
	{
		Mesh mesh;
		mesh.AddPoint(0.5f*dimension*vector2{ 1,1 });
		mesh.AddPoint(0.5f*dimension*vector2{ 1,-1 });
		mesh.AddPoint(0.5f*dimension*vector2{ -1,1 });
		mesh.AddPoint(0.5f*dimension*vector2{ 1,-1 });
		mesh.AddPoint(0.5f*dimension*vector2{ -1,-1 });
		mesh.AddPoint(0.5f*dimension*vector2{ -1,1 });

		mesh.AddTextureCoordinate(vector2{ 1, 1 });
		mesh.AddTextureCoordinate(vector2{ 1, 0 });
		mesh.AddTextureCoordinate(vector2{ 0, 1 });
		mesh.AddTextureCoordinate(vector2{ 1, 0 });
		mesh.AddTextureCoordinate(vector2{ 0, 0 });
		mesh.AddTextureCoordinate(vector2{ 0, 1 });

		mesh.SetPointListType(PointTypeList::Triangles);
		mesh.colorType = ColorType::Texture;
		return mesh;
	}
}