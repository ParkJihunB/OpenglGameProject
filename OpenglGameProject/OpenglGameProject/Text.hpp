#pragma once
//https://github.com/ubawurinna/freetype-windows-binaries
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Shader.hpp"
#include "Color.hpp"
#include <map>
//http://lancekun.com/tc/37
/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	vector2   Size;      // Size of glyph
	vector2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Text
{
public:
	Text(std::string data);
	~Text();
	bool Update() { return true; }
	void ChangeText(std::string text) { textData = text; }

	void SetTransform(vector2 trans) { transform = trans; }
	void SetScale(float s) { scale = s; }
	void SetColor(Color c) { color = c; }
	void SetDepth(float d) { depth = d; }


public:
	vector2 transform = vector2(0.f,0.f);
	Color color = Common::Black;
	std::string textData;
	std::map<GLchar, Character> Characters;
	float scale = 1.f;
	float depth = 0.f;

private:
	FT_Library ft;
	FT_Face face;
};

