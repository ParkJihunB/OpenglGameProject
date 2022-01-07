#include "Texture.hpp"

Texture::Texture(const char * path, TextureType type)
{
	texturePath = path; 
	textureType = type;
	glGenTextures(1, &textureHandle);
	BindOpenglTexture();
}

void Texture::LoadTexture()
{
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true);
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		if(textureType == TextureType::JPG)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if(textureType == TextureType::PNG)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}



void Texture::BindOpenglTexture()
{
	// load and create a texture 
	// -------------------------
	
	glBindTexture(GL_TEXTURE_2D, textureHandle); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//padding/alignment issue: loading a format which has a different padding requirement to GL
	//GL: Default expects rows of pixels to be padded to a multiple of 4 bytes
	//Tell GL how your texture is packed
	//pixel rectangle의 각 pixel row의 시작 주소의 alignment를 정한다
	//GL_UNPACK_ALIGNMENT: 읽어들일 각 row의 시작 주소의 alignment를 정한다
	//몰라 이거 안 해주면 이상하게 나옴
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	LoadTexture();
}

void Texture::ChangeTexture(const char * path)
{
	texturePath = path;
	changedTexure = true;
}

unsigned int Texture::GetTextureHandle()
{
	if (changedTexure)
	{
		changedTexure = false;
		BindOpenglTexture();
	}
	return textureHandle;
}
