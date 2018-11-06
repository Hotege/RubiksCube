//
// Created by dl on 2018/11/5.
//

#include "RCButton.h"
#include <algorithm>
#include <numeric>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>

struct TYPE_RENDER
{
	unsigned int W, H;
	unsigned int w, h;
	unsigned int dx, base, sy;
	unsigned char* data = nullptr;
};

RCButton::RCButton(
		const char* pFont, const unsigned int& wFont, const unsigned int& hFont,
		const float& xPos, const float& yPos,
		const wchar_t* pwText
)
{
	m_nTexture = 0;

	m_fXPos = xPos;
	m_fYPos = yPos;

	m_pTextBuffer = nullptr;
	FT_Library ftLibrary = nullptr;
	FT_Face ftFace = nullptr;
	FT_Init_FreeType(&ftLibrary);
	FT_New_Face(ftLibrary, pFont, 0, &ftFace);
	FT_Set_Pixel_Sizes(ftFace, wFont, hFont);

//	std::vector<unsigned char*> vWcharBuffer; // 8-bits
	std::vector<TYPE_RENDER> vTypeRender;
//	std::vector<unsigned int> vWcharWidth;
//	std::vector<unsigned int> vWcharHeight;
	size_t nSize = wcslen(pwText);
	for (size_t i = 0; i < nSize; i++)
	{
		FT_Load_Char(ftFace, (FT_ULong)pwText[i], FT_LOAD_RENDER);
		TYPE_RENDER type = { 0 };
		type.W = (unsigned int)ftFace->glyph->metrics.horiAdvance / 64;
		type.H = (unsigned int)ftFace->glyph->metrics.vertAdvance / 64;
		type.w = ftFace->glyph->bitmap.width;
		type.h = ftFace->glyph->bitmap.rows;
		type.dx = (unsigned int)ftFace->glyph->metrics.horiBearingX / 64;
		type.base = (unsigned int)ftFace->size->metrics.ascender / 64;
		type.sy = (unsigned int)ftFace->glyph->metrics.horiBearingY / 64;
		type.data = new unsigned char[type.w * type.h];
		memcpy(type.data, ftFace->glyph->bitmap.buffer, type.w * type.h);
		vTypeRender.push_back(type);
	}
	m_nWidth = std::accumulate(vTypeRender.begin(), vTypeRender.end(), (unsigned int)0, [](unsigned int a, TYPE_RENDER t) { return a + t.W; });
	m_nHeight = std::max_element(vTypeRender.begin(), vTypeRender.end(), [](TYPE_RENDER a, TYPE_RENDER b) { return a.H < b.H; })->H;
	m_pTextBuffer = new unsigned char[m_nWidth * m_nHeight * 4];
	memset(m_pTextBuffer, 0, m_nWidth * m_nHeight * 4);
	unsigned int wOffset = 0;
	for (auto p : vTypeRender)
	{
		int xOffset = p.dx, yOffset = p.base - p.sy;
		for (int j = 0; j < p.h; j++)
		{
			int cy = yOffset + j;
			for (int i = 0; i < p.w; i++)
			{
				int cx = wOffset + xOffset + i;
				m_pTextBuffer[(cy * m_nWidth + cx) * 4 + 0] = p.data[j * p.w + i];
				m_pTextBuffer[(cy * m_nWidth + cx) * 4 + 1] = p.data[j * p.w + i];
				m_pTextBuffer[(cy * m_nWidth + cx) * 4 + 2] = p.data[j * p.w + i];
				m_pTextBuffer[(cy * m_nWidth + cx) * 4 + 3] = p.data[j * p.w + i];
			}
		}
		wOffset += p.W;
	}

	static bool ff = true;
	for (auto p : vTypeRender)
	{
		delete[] p.data;
		p.data = nullptr;
	}

	glGenTextures(1, &m_nTexture);
	glBindTexture(GL_TEXTURE_2D, m_nTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_pTextBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FT_Done_Face(ftFace);
	FT_Done_FreeType(ftLibrary);
}

RCButton::~RCButton()
{
	if (m_pTextBuffer)
	{
		delete[] m_pTextBuffer;
		m_pTextBuffer = nullptr;
	}
}

unsigned int RCButton::GetWidth()
{
	return m_nWidth;
}

unsigned int RCButton::GetHeight()
{
	return m_nHeight;
}

float RCButton::GetXPos()
{
	return m_fXPos;
}

float RCButton::GetYPos()
{
	return m_fYPos;
}

void RCButton::SetXPos(float x)
{
	m_fXPos = x;
}

void RCButton::SetYPos(float y)
{
	m_fYPos = y;
}

unsigned int RCButton::GetTexture()
{
	return m_nTexture;
}

std::vector<float> RCButton::GetTriangles(const int& nWidth, const int& nHeight)
{
	GLfloat vertices[] = {
			m_fXPos, m_fYPos,
			m_fXPos, m_fYPos - float(m_nHeight) / nHeight * 2,
			m_fXPos + float(m_nWidth) / nWidth * 2, m_fYPos - float(m_nHeight) / nHeight * 2,
			m_fXPos, m_fYPos,
			m_fXPos + float(m_nWidth) / nWidth * 2, m_fYPos - float(m_nHeight) / nHeight * 2,
			m_fXPos + float(m_nWidth) / nWidth * 2, m_fYPos,
	};
	std::vector<float> result(vertices, vertices + sizeof(vertices) / sizeof(GLfloat));
	return result;
}

std::vector<float> RCButton::GetTexcoords()
{
	float coords[] = { 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0 };
	std::vector<float> result(coords, coords + sizeof(coords) / sizeof(float));
	return result;
}

std::vector<unsigned int> RCButton::GetIndices()
{
	unsigned int id[] = { 0, 1, 2, 3, 4, 5 };
	std::vector<unsigned int> result(id, id + sizeof(id) / sizeof(unsigned int));
	return result;
}