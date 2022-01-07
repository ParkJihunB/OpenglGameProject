#pragma once
#include "Include/GL/glew.h"
#include "Include/GLFW/glfw3.h"
#include "vector3.hpp"
#include "affine2d.hpp"
#include "Color.hpp"

enum class ShaderTypes : int
{
	SolidColor,            // Used to display a mesh with one solid color
	TextureWithColor, // Used to display a mesh with a texture and multiply the texel by a uniform color
	Text,     // Used to display a mesh with a color at each point
	Count
};

class Shader
{
public:
	Shader();
	~Shader();

	void BuildCompileShader(int shaderType);
	void BuildCompileShader(const char* vertex, const char* fragment);
	void UseShader();
	//void SendColor();

	void SendUniformVariable(vector3 color);
	void SendUniformVariable_color(vector3 color);
	void SendUniformVariable(const std::string& variable_name, int number);
	void SendUniformVariable(const std::string& variable_name, float value);
	void SendUniformVariable(const std::string& variable_name, vector3 value);
	void SendUniformVariable(const std::string& variable_name, Color value);
	void SendUniformVariable(const std::string& variable_name, affine2d value);
	
	void SendTransform(affine2d transform);

	int GetVertexAttributeLocation(const std::string& vertex_field_name) const;
	int shaderProgram = 0;
private:
	//int shaderProgram = 0;

	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec2 position;\n"

		"uniform mat3 transform;\n"
		"uniform float depth = 0;\n"

		"void main()\n"
		"{\n"
		"	vec3 position = transform * vec3(position, 1.0);\n"
		"   gl_Position = vec4(position.xy, depth, 1.0);\n"
		"}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 vec4Color;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4Color;\n"
		"}\n";

	//////////////////////////////////////////////////////////////

	const char *vertexTextureShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec2 position;\n"
		"layout(location = 1) in vec3 color;\n"
		"layout(location = 2) in vec2 texture_coordinate;\n"

		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"

		"uniform mat3 transform;\n"

		"uniform float depth = 0;\n"

		"void main()\n"
		"{\n"
		"	vec3 position = transform * vec3(position, 1.0);\n"
		"	gl_Position = vec4(position.xy, depth, 1.0);\n"
		"	ourColor = color;\n"
		"	TexCoord = texture_coordinate;\n"
		"}\n";
	const char *fragmentTextureShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"

		"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"

		"uniform sampler2D ourTexture;\n"

		"void main()\n"
		"{\n"
		"	FragColor = texture(ourTexture, TexCoord)* vec4(ourColor, 1.0);\n"
		"}\n";
	//////////////////////////////////////////////////////////////
	const char* vertexTextShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec4 vertex;\n"// // <vec2 pos, vec2 tex>
		"out vec2 TexCoords;\n"

		"uniform mat4 projection;\n"
		"uniform float depth = 0;\n"

		"void main()\n"
		"{\n"
		"	//gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
		"	gl_Position = vec4(vertex.xy, depth, 1.0);\n"
		"	TexCoords = vertex.zw;\n"
		"}\n";
	const char* fragmentTextShaderSource =
		"#version 330 core\n"
		"in vec2 TexCoords;\n"
		"out vec4 color;\n"

		"uniform sampler2D text;\n"
		"uniform vec3 textColor;\n"

		"void main()\n"
		"{\n"
		"	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
		"	color = vec4(textColor, 1.0) * sampled;\n"
		"};\n";
};

