#pragma once

struct Color
{
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 255;
	//vector3 GetColorToVec3() { return vector3(r / 255.f, g / 255.f, b / 255.f); }
};

//namespace White_Pastels
//{
//	Color PeachPuff		{ 1.f,	0.854902f,	0.72549f };
//	Color Ivory			{ 1.f,	1.f,	0.941176f };
//	Color Lemon_Chiffon	{ 1.f, 0.980392f, 0.803922f };
//	Color Seashell		{ 1.f, 0.960784f, 0.933333f };
//	Color Honeydew		{ 0.941176f, 1.f, 0.941176f };
//	Color Mint_Cream	{ 0.941176f, 1.f, 1.f };
//	Color Alice_Blue	{ 0.941176f, 0.972549f, 1.f };
//	Color Misty_Rose	{ 1.f	, 0.894118f , 0.882353f };
//	Color White			{ 1.f, 1.f, 1.f };
//}

namespace Common
{
	const Color Black	{ 0, 0, 0 };
	const Color White	{ 255, 255, 255 };
	const Color Red		{255, 0, 0 };
	const Color Green	{0, 255, 0 };
	const Color Blue	{0, 0, 255 };
	const Color Yellow	{255, 255, 0 };
	const Color Magenta	{255, 0, 255 };
	const Color Cyan	{0, 255, 255 };

	const Color Transparent{ 0, 0, 0, 0 };

	const Color Peach{ 1.f,	0.854902f,	0.72549f };
	const Color Dark_Slate_Green{ 23.f / 255, 84.f / 255, 81.f / 255 };

	const Color sunset = { static_cast<int>(255 * 0.984f),static_cast<int>(255 * 0.396f), static_cast<int>(255 * 0.259f) };
	const Color sunflower = { 255 * 1, static_cast<int>(255 * 0.733f), 255 * 0 };
	const Color grass = { static_cast<int>(255 * 0.247f), static_cast<int>(255 * 0.408f), static_cast<int>(255 * 0.11f) };
	const Color pink{ static_cast<int>(255 * 0.9f), static_cast<int>(255 * 0.5f), static_cast<int>(255 * 0.5f) };
}