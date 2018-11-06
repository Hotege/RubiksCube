//
// Created by dl on 2018/11/5.
//

#ifndef RUBIK_SCUBE_FILELOADER_H
#define RUBIK_SCUBE_FILELOADER_H


class FileLoader
{
public:
	FileLoader();
	explicit FileLoader(const char* pFileName);
	virtual ~FileLoader();

	bool LoadFile(const char* pFileName);
	bool IsFileValid();
	const long GetSize();
	const unsigned char* GetData();

private:
	long m_nFileSize;
	void* m_pFile;
	unsigned char* m_pData;
};


#endif //RUBIK_SCUBE_FILELOADER_H
