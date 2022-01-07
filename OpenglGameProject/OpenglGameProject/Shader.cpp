#include "Shader.hpp"
#include <iostream>
#include "Color.hpp"

Shader::Shader()
{

}


Shader::~Shader()
{
}

//void Shader::SendColor()
//{
//	int vertexColorLocation = glGetUniformLocation(shaderProgram, "vec4Color");
//	//glUniform4f(vertexColorLocation, 
//	//	White_Pastels::Honeydew.r, White_Pastels::Honeydew.g,
//	//	White_Pastels::Honeydew.b, White_Pastels::Honeydew.a);
//	glUniform4f(vertexColorLocation,
//		Common::Green.r, Common::Green.g,
//		Common::Green.b, Common::Green.a);
//	//1	0.854902	0.72549
//}

//int Shader::GetUniformLocation(const std::string& name)
//{
//	const auto pair_of_name_and_location = uniformNameToLocation.find(name);
//	if (pair_of_name_and_location != uniformNameToLocation.end())
//		return pair_of_name_and_location->second;
//
//	int location = -1;
//	// TODO get the uniform variables layout location
//	std::string str = name;
//	const char *ch = str.c_str();
//	location = glGetUniformLocation(handleToShader, ch);
//
//	uniformNameToLocation.insert(std::make_pair(name, location));
//	return location;
//}


void Shader::SendUniformVariable_color(vector3 color)
{
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "vec4Color");
	glUniform4f(vertexColorLocation, color.x, color.y, color.z, 1.0f);
}

void Shader::SendUniformVariable(const std::string & variable_name, int value)
{
	std::string str = variable_name;
	const char* ch = str.c_str();
	int location = glGetUniformLocation(shaderProgram, ch);
	if (location == -1)
		return;
	// TODO send a single int to the shader variable
	glUniform1i(location, value);
}

void Shader::SendUniformVariable(const std::string & variable_name, float value)
{
	std::string str = variable_name;
	const char* ch = str.c_str();
	int location = glGetUniformLocation(shaderProgram, ch);
	if (location == -1)
		return;
	// TODO send a single int to the shader variable
	glUniform1f(location, value);
}

void Shader::SendUniformVariable(vector3 color)
{
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "vec4Color");
	glUniform4f(vertexColorLocation, color.x, color.y, color.z, 1.0f);
}

void Shader::SendUniformVariable(const std::string & variable_name, vector3 value)
{
	std::string str = variable_name;
	const char* ch = str.c_str();
	int location = glGetUniformLocation(shaderProgram, ch);
	if (location == -1) return;
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SendUniformVariable(const std::string & variable_name, Color value)
{
	std::string str = variable_name;
	const char* ch = str.c_str();
	int location = glGetUniformLocation(shaderProgram, ch);
	if (location == -1) return;
	glUniform3f(location, value.r, value.g, value.b);
}

void Shader::SendUniformVariable(const std::string & variable_name, affine2d value)
{
	std::string str = variable_name;
	const char* ch = str.c_str();
	int location = glGetUniformLocation(shaderProgram, ch);
	if (location == -1) return;
	glUniformMatrix3fv(location, 1, GL_FALSE, &value.elements[0][0]);
}

void Shader::SendTransform(affine2d transform)
{
	int location = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix3fv(location, 1, GL_FALSE, &transform.elements[0][0]);
}

int Shader::GetVertexAttributeLocation(const std::string& vertex_field_name) const
{
	auto attriblocation = glGetAttribLocation(shaderProgram, vertex_field_name.c_str());

	return attriblocation;
}


void Shader::BuildCompileShader(int shaderType)
{
	switch (shaderType)
	{
	case (int)(ShaderTypes::SolidColor):
		BuildCompileShader(vertexShaderSource, fragmentShaderSource);
		break;
	case (int)(ShaderTypes::TextureWithColor) :
		BuildCompileShader(vertexTextureShaderSource, fragmentTextureShaderSource);
		break;
	case (int)(ShaderTypes::Text) :
		BuildCompileShader(vertexTextShaderSource, fragmentTextShaderSource);
		break;
	}
}

void Shader::BuildCompileShader(const char * vertex, const char * fragment)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::UseShader()
{
	glUseProgram(shaderProgram);
}
