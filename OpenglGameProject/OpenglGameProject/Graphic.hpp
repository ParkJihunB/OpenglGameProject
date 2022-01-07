#pragma once
#include "System.hpp"
#include "Shader.hpp"
#include "ObjectManager.hpp"
#include "HudManager.hpp"
#include "Text.hpp"

struct VertexPosition2f
{
	vector2 position;
};

struct VertexPosition2fColor3f
{
	vector2 position;
	vector3 color;
};

struct VertexPosition2fTexture2f
{
	vector2 position;
	vector3 color;
	vector2 textureCoordinate;
};


class Graphic : public System
{
public:
	bool Init() override;
	bool Update(float dt) override;
	void Quit() override;

public:
	Graphic(unsigned int width, unsigned int height) : screen_x(width), screen_y(height) {}
	void Draw(ObjectManager* p_objectmanager);
	void Draw(HudManager* p_hudManager);

	void Draw(Object* p_object);
	void DrawTexture(Object* p_object);
	void DrawText(Text* text);
	void ChangeBackGroundColor(Color p_color) { m_backgroundColor = p_color; }

private:
	void CreateVertexArray();
	void DescribSolidVertexPosition_ToOpenGL(); //Set vao,vbo of solid color,non-texture
	void DescribVertexPositionTexture_ToOpenGL();
	void DescribVertexText_ToOpenGL();
	
	GLenum GetDrawMode(PointTypeList pointType);

private:
	Shader shader;
	Shader textureShader;
	Shader textShader;

	Transform currentTransform;
	float rotation = 0;

private:
	Color m_backgroundColor = Common::Peach;
	unsigned int handle_VertexAttributesArray[(int)(ShaderTypes::Count)] = { 0 };
	unsigned int handle_VertexBuffer[(int)(ShaderTypes::Count)] = { 0 };
	unsigned int handle_Texture;
	std::vector<VertexPosition2f> vertices_position;
	std::vector<VertexPosition2fTexture2f> positionTextureVertexes;

	int numberOfVertexType = (int)ShaderTypes::Count;

	unsigned int screen_x = 800;
	unsigned int screen_y = 600;
	Text* sampleText = nullptr;
};

