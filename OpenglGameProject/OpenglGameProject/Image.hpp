#pragma once
#include "Color.hpp"
#include <vector>

enum ImageType
{
	PNG,
	ELSE
};
class Image
{
public:
	Image(const char* path, ImageType type);
	void LoadImage();
private:
	ImageType imageType = ImageType::ELSE;
};