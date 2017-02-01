
#ifndef STREAM_INHO_H
#define STREAM_INHO_H

#include "Declarations.h"
#include "Strings.h"

class CStreamInfo
{
public:
	bool Packed; //����� �������� zLibEngine
	bool HaveSize; //� ������ ������ ����������� ��� �����

	bool IsText; // ��� ����� --unix-eol

	bool MainMetadataStream;
	
	bool Picture;
	bool PictureGallery;
	GCString PictureType;

	unsigned long SizeOffset; //� ������ ������� � �������� �����-�� ���������� ����� 0xFF
	unsigned long SizeBytes;  //����� ������� ����� ���� ������
	unsigned long ContentOffset; //������ ���������� ������
	unsigned long FullSize;
	unsigned long Size; //������ ������ ��� ��������� ����������

public:
	CStreamInfo();

	void UpdateInfo(LPCSTR StreamName);
	//void UpdateInfo(const wchar_t* wStreamName); // TODO remove this comment, if all will be working fine: 2008-05-12

	unsigned long ReadSize(IStream* pStream); //������ ������ ������ (���� �� � ��������) ��� ��������� ���
	unsigned long ReadSize(GCString& String); //��������� ������ �� ������
	unsigned long ReadSizeOfCleanStream(IStream* pStream); //������ ������ ���������� ������
	unsigned long ReadFileSize(FILE *File); //������ ������ �����

	//���� ��������� ����� ��� ��� �������
	void DeterminePictureType(IStream* pStream);
	//��� �������� � ����� ����� ���������� �� ����������
	void DeterminePictureType(GCString& FileName);

protected:
	void DetermineSizeFormat(unsigned long FullSize);
	void DetermineFileSizeFormat(unsigned long FullSize);
	
private:
	void Reset();
};

#endif
