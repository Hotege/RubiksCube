//
// Created by dl on 2018/11/5.
//

#ifndef RUBIK_SCUBE_RCBUTTON_H
#define RUBIK_SCUBE_RCBUTTON_H


#include <vector>

class RCButton
{
public:
	// must called after glew init.
	explicit RCButton(
			const char* pFont, const unsigned int& wFont, const unsigned int& hFont,
			const float& xPos, const float& yPos,
			const wchar_t* pwText = L"None"
	);
	virtual ~RCButton();

	unsigned int GetWidth();
	unsigned int GetHeight();
	float GetXPos();
	float GetYPos();
	void SetXPos(float x);
	void SetYPos(float y);
	unsigned int GetTexture();
	std::vector<float> GetTriangles(const int& nWidth, const int& nHeight);
	std::vector<float> GetTexcoords();
	std::vector<unsigned int> GetIndices();

private:
	unsigned char* m_pTextBuffer;
	unsigned int m_nWidth, m_nHeight;
	float m_fXPos, m_fYPos;
	unsigned int m_nTexture;
};


#endif //RUBIK_SCUBE_RCBUTTON_H
