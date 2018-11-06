//
// Created by dl on 2018/11/5.
//

#include "FileLoader.h"
#include <cstdio>
#include <cstring>

#define pFile (FILE*)m_pFile
#define DELETE_ARRAY(x) { delete[] x; x = nullptr; }

FileLoader::FileLoader()
{
	m_nFileSize = 0;
	m_pFile = nullptr;
	m_pData = nullptr;
}

FileLoader::FileLoader(const char* pFileName)
{
	m_pFile = nullptr;
	m_pData = nullptr;
	LoadFile(pFileName);
}

FileLoader::~FileLoader()
{
	if (m_pFile)
		fclose(pFile);
	if (m_pData)
	DELETE_ARRAY(m_pData);
}

bool FileLoader::LoadFile(const char* pFileName)
{
	if (m_pFile)
		fclose(pFile);
	if (m_pData)
		DELETE_ARRAY(m_pData);
	m_pFile = fopen(pFileName, "rb");
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		m_nFileSize = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);
		m_pData = new unsigned char[m_nFileSize + 1];
		memset(m_pData, 0, (size_t)m_nFileSize + 1);
		fread(m_pData, (size_t)m_nFileSize, sizeof(unsigned char), pFile);
		return true;
	}
	else
		return false;
}

bool FileLoader::IsFileValid()
{
	return pFile != nullptr;
}

const long FileLoader::GetSize()
{
	return m_nFileSize;
}

const unsigned char* FileLoader::GetData()
{
	return m_pData;
}