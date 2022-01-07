#include "Graphic.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool Graphic::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shader.BuildCompileShader(int(ShaderTypes::SolidColor));
	textureShader.BuildCompileShader(int(ShaderTypes::TextureWithColor));
	textShader.BuildCompileShader(int(ShaderTypes::Text));

	CreateVertexArray();
	DescribSolidVertexPosition_ToOpenGL();
	DescribVertexPositionTexture_ToOpenGL();
	DescribVertexText_ToOpenGL();

	return true;
}

bool Graphic::Update(float dt)
{
	glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

void Graphic::Quit()
{
	glDeleteVertexArrays(numberOfVertexType, handle_VertexAttributesArray);
	glDeleteBuffers(numberOfVertexType, handle_VertexBuffer);
}

void Graphic::CreateVertexArray()
{
	//Opengl draw 시작..
	//numberofVertexType은 셰이더의 종류의 개수이다.
	//셰이더는 그냥 컬러/그라데이션/텍스쳐에 따라 따로 만들어야하기 때문에
	//지금은 그냥 일단 하나만 만들었다. 셰이더가 여러개이면 VAO,VBO도 배열로 만들어야 한다.
	glGenVertexArrays(numberOfVertexType, handle_VertexAttributesArray);
	glGenBuffers(numberOfVertexType, handle_VertexBuffer);
}

void Graphic::DescribSolidVertexPosition_ToOpenGL()
{
	//지금은 VAO를 하나만 만들었지만 셰이더가 여러개일경우 어떤 셰이더를 쓰느냐에 따라
	//handle_VertexAttributesArray[?] 를 골라 사용해야한다.
	//[0] = 단색셰이더 [1] = 그라데이션 셰이더.... 에 따라서.
	//이 함수는 단색셰이더이므로 첫번째를 사용해야한다... 지금은 일단 하나만 만들었다는 사실을 상기하자.
	glBindVertexArray(handle_VertexAttributesArray[int(ShaderTypes::SolidColor)]);
	glBindBuffer(GL_ARRAY_BUFFER, handle_VertexBuffer[int(ShaderTypes::SolidColor)]);

	int position_attribute_location = shader.GetVertexAttributeLocation("position");
	constexpr int two_components_in_vertex_position = 2;
	constexpr GLenum float_element_type = GL_FLOAT;
	constexpr GLboolean not_fixedpoint = GL_FALSE;
	const void* offset_in_struct = (const void*)offsetof(VertexPosition2f, position);

	glVertexAttribPointer(position_attribute_location, two_components_in_vertex_position,
		float_element_type, not_fixedpoint,
		sizeof(VertexPosition2f), offset_in_struct);
	glEnableVertexAttribArray(position_attribute_location);
}

void Graphic::DescribVertexPositionTexture_ToOpenGL()
{
	glBindVertexArray(handle_VertexAttributesArray[int(ShaderTypes::TextureWithColor)]);
	glBindBuffer(GL_ARRAY_BUFFER, handle_VertexBuffer[int(ShaderTypes::TextureWithColor)]);//

	int position_attribute_location = textureShader.GetVertexAttributeLocation("position");
	int color_attribute_location = textureShader.GetVertexAttributeLocation("color");
	int texture_attribute_location = textureShader.GetVertexAttributeLocation("texture_coordinate");
	constexpr int two_components_in_vertex_position = 2;
	constexpr int three_components_in_vertex_color = 3;
	constexpr int two_components_in_texture_coord = 2;
	constexpr GLenum float_element_type = GL_FLOAT;
	constexpr GLboolean not_fixedpoint = GL_FALSE;
	const void* offset_in_struct = reinterpret_cast<const void*>(offsetof(VertexPosition2fTexture2f, position));
	// position attribute
	glVertexAttribPointer(position_attribute_location, two_components_in_vertex_position, float_element_type, not_fixedpoint, sizeof(VertexPosition2fTexture2f), offset_in_struct);
	glEnableVertexAttribArray(position_attribute_location);
	// color attribute
	offset_in_struct = reinterpret_cast<const void*>(offsetof(VertexPosition2fTexture2f, color));
	glVertexAttribPointer(color_attribute_location, three_components_in_vertex_color, float_element_type, not_fixedpoint, sizeof(VertexPosition2fTexture2f), offset_in_struct);
	glEnableVertexAttribArray(color_attribute_location);
	// texture coord attribute
	offset_in_struct = reinterpret_cast<const void*>(offsetof(VertexPosition2fTexture2f, textureCoordinate));
	glVertexAttribPointer(texture_attribute_location, two_components_in_texture_coord, float_element_type, not_fixedpoint, sizeof(VertexPosition2fTexture2f), offset_in_struct);
	glEnableVertexAttribArray(texture_attribute_location);
}

void Graphic::DescribVertexText_ToOpenGL()
{
	// configure VAO/VBO for texture quads
// -----------------------------------
	glBindVertexArray(handle_VertexAttributesArray[int(ShaderTypes::Text)]);
	glBindBuffer(GL_ARRAY_BUFFER, handle_VertexBuffer[int(ShaderTypes::Text)]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Graphic::Draw(ObjectManager* p_objectManager)
{
	if (p_objectManager != nullptr)
	{
		for (std::map<std::string, Object*>::iterator it = p_objectManager->GetObjectMap().begin();
			it != p_objectManager->GetObjectMap().end(); ++it)
		{
			if (it->second->GetMesh().colorType == ColorType::Solid)
				Draw(it->second);
			else if (it->second->GetMesh().colorType == ColorType::Texture)
				DrawTexture(it->second);
		}
	}

}

void Graphic::Draw(HudManager * p_hudManager)
{
	if (p_hudManager != nullptr)
	{
		for (std::map<std::string, Text*>::iterator it = p_hudManager->GetHudListPointer()->begin();
			it != p_hudManager->GetHudListPointer()->end(); ++it)
		{
			DrawText(it->second);
		}
	}
}

void Graphic::Draw(Object* p_object)
{
	shader.UseShader();
	int count = p_object->mesh.GetPointCount();

	vertices_position.clear(); //오브젝트의 포지션을 모아놓은 벡터집합
	vertices_position.reserve(count); //벡터집합에 포지션의 개수를 충분히 넣을 수 있는지 미리 확인

	for (int i = 0; i < count; i++) //벡터집합 안에 포지션들을 넣는다.
		vertices_position.push_back({ p_object->mesh.GetPoint(i) });

	//오브젝트 정보 보내기!
	currentTransform = p_object->transform;
	unsigned int displaysize_x = screen_x;
	unsigned int displaysize_y = screen_y;
	affine2d projection = { (20.0f / displaysize_x), 0, 0,
							0, (20.0f / displaysize_y), 0,
							0, 0, 1 };
	//affine2d projection = { 1, 0, 0, 0, 1, 0, 0, 0, 1 }; //일단 임시로 지정해놓은것들
	affine2d cameraToNDC = { 1, 0, 0, 0, 1, 0, 0, 0, 1 }; //나중에 카메라 만들려면 고쳐야함
	affine2d to_ndc = projection * cameraToNDC *  currentTransform.GetModelToWorld();
	shader.SendTransform(to_ndc);
	shader.SendUniformVariable("depth", p_object->GetTransform().GetDepth());

	Color obj_color = p_object->GetMesh().GetColor(0);
	//shader.SendUniformVariable_color(vector3{ obj_color.r,obj_color.g,obj_color.b });
	vector3 col = vector3(obj_color.r / 255.f, obj_color.g / 255.f, obj_color.b / 255.f);
	shader.SendUniformVariable_color(col);

	glBindVertexArray(handle_VertexAttributesArray[int(ShaderTypes::SolidColor)]);
	glBindBuffer(GL_ARRAY_BUFFER, handle_VertexBuffer[int(ShaderTypes::SolidColor)]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPosition2f)*vertices_position.size(),
		&vertices_position[0], GL_STATIC_DRAW);

	glDrawArrays(GetDrawMode(p_object->GetMesh().point_list_type), 0, (GLsizei)(vertices_position.size()));
}

void Graphic::DrawTexture(Object* p_object)
{
	textureShader.UseShader();
	glBindTexture(GL_TEXTURE_2D, p_object->GetMesh().texture->GetTextureHandle());
	glBindVertexArray(handle_VertexAttributesArray[int(ShaderTypes::TextureWithColor)]);
	glBindBuffer(GL_ARRAY_BUFFER, handle_VertexBuffer[int(ShaderTypes::TextureWithColor)]);
	int count = p_object->GetMesh().GetPointCount();
	positionTextureVertexes.clear();
	positionTextureVertexes.reserve(count);
	Mesh mesh = p_object->GetMesh();
	for (int i = 0; i < count; i++)
	{
		Color color = mesh.GetColor(i);
		vector3 col = vector3(color.r / 255.f, color.g / 255.f, color.b / 255.f);
		positionTextureVertexes.push_back({ mesh.GetPoint(i), col , mesh.GetTextureCoordinate(i) });
	}
	currentTransform = p_object->transform;
	unsigned int displaysize_x = screen_x;
	unsigned int displaysize_y = screen_y;
	affine2d projection = { (20.0f / displaysize_x), 0, 0,
							0, (20.0f / displaysize_y), 0,
							0, 0, 1 };
	affine2d cameraToNDC = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	affine2d to_ndc = projection * cameraToNDC *  currentTransform.GetModelToWorld();
	textureShader.SendTransform(to_ndc);

	glBufferData(GL_ARRAY_BUFFER, positionTextureVertexes.size() * sizeof(positionTextureVertexes), &positionTextureVertexes[0], GL_STATIC_DRAW);//
	glDrawArrays(GetDrawMode(p_object->GetMesh().point_list_type), 0, (GLsizei)(positionTextureVertexes.size()));
}

void Graphic::DrawText(Text * text)
{
	// activate corresponding render state	
	textShader.UseShader();
	textShader.SendUniformVariable("depth", text->depth);
	textShader.SendUniformVariable("textColor", text->color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(handle_VertexAttributesArray[(int)(ShaderTypes::Text)]);
	

	float sx = 2.0 / screen_x;
	float sy = 2.0 / screen_y;
	// iterate through all characters
	std::string::const_iterator c;
	vector2 temp_transform = text->transform;

	for (c = text->textData.begin(); c != text->textData.end(); c++)
	{
		Character ch = text->Characters[*c];

		float xpos = temp_transform.x + ch.Bearing.x * text->scale * sx;
		float ypos = temp_transform.y - (ch.Size.y - ch.Bearing.y) * text->scale * sy;

		float w = ch.Size.x * text->scale * sx;
		float h = ch.Size.y * text->scale * sy;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, handle_VertexBuffer[(int)(ShaderTypes::Text)]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		temp_transform.x += (ch.Advance >> 6) * text->scale * sx; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLenum Graphic::GetDrawMode(PointTypeList pointType)
{
	switch (pointType)
	{
	case PointTypeList::Lines:
		return GL_LINES;
	case PointTypeList::LineLoop:
		return GL_LINE_LOOP;
	case PointTypeList::LineStrip:
		return GL_LINE_STRIP;
	case PointTypeList::Triangles:
		return GL_TRIANGLES;
	case PointTypeList::TriangleStrip:
		return GL_TRIANGLE_STRIP;
	case PointTypeList::TriangleFan:
		return GL_TRIANGLE_FAN;
	case PointTypeList::Polygon:
		return GL_POLYGON;
	case PointTypeList::Quad:
		return GL_QUADS;
	default:
		return GL_TRIANGLE_STRIP;
	}
}
