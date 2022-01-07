#pragma once
#include "vector3.hpp"
#include <vector>
#include "vector2.hpp"
#include "Color.hpp"
#include "Texture.hpp"

enum class PointTypeList
{
	Lines,
	LineLoop,
	LineStrip,
	Triangles,
	TriangleStrip,
	TriangleFan,
	Polygon,
	Quad
};

enum class MeshPolygonType
{
	Box,
	Circle,
	Line
};

enum class ColorType
{
	Solid,
	Texture,
	Interpolated
};

class Mesh
{
public:
	unsigned GetPointCount() const;
	unsigned GetPointSize();

	vector2 GetPoint(std::size_t index) const;
	Color GetColor(std::size_t index) const;
	vector2 GetTextureCoordinate(std::size_t index) const;
	PointTypeList GetPointListType() const;
	void SetPointListType(PointTypeList type);

	void AddPoint(vector2 point);
	void AddColor(Color color);
	void ChangeColor(Color color);
	void AddTextureCoordinate(vector2 texture_coordinate);
	void CreateTexture(const char* path, TextureType type) { texture = new Texture(path, type); }

	void ClearColors();
	void ClearTextureCoordinates();
	void Clear();

	void ChangeColors(Color color);

public:
	PointTypeList point_list_type = PointTypeList::Lines;
	std::vector<vector2> points{};
	std::vector<Color> colors{};
	std::vector<vector2> textureCoordinates{};

	MeshPolygonType mesh_polygon_type = MeshPolygonType::Box;
	ColorType colorType = ColorType::Solid;
	Texture* texture = nullptr;

public:
    vector2 GetMin() { return min; }
    vector2 GetMax() { return max; }

private:
    vector2 min;
    vector2 max;
	
};

namespace mesh
{
	Mesh CreateCircle(float radius = 1, std::size_t pointCount = 60);
	Mesh CreateWireCircle(float radius = 1, std::size_t pointCount = 60);
	Mesh CreateBox(float dimension = 1);
	//Mesh CreateBoxi(float dimension = 1, Color color = { 255, 255, 255, 255 });
	Mesh CreateWireBox(float dimension = 1);
	Mesh CreateLine(vector2 a = { 0, 0 }, vector2 b = { 1, 0 });
	Mesh CreateLine(vector2 a, vector2 b, Color color);
	Mesh CreateTriangle(float scale = 1);
	Mesh CreatePolygon(float radius = 1, int pointCount = 5);

	Mesh CreateTextureBox(float dimension = 1);
}