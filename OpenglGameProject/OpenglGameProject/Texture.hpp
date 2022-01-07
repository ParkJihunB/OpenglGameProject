#pragma once
#include "stb_image.h"
#include "glew.h"
#include <iostream>

enum TextureType
{
	JPG,
	PNG
};
class Texture
{
public:
	Texture(const char* path, TextureType type);
	~Texture();
	void LoadTexture();
	void BindOpenglTexture();
	void ChangeTexture(const char* path);

	unsigned int GetTextureHandle();

private:
	const char* texturePath;
	int width;
	int height;
	int nrChannels;
	unsigned int textureHandle;
	TextureType textureType;
	bool changedTexure;
};

