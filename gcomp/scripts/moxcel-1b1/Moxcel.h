// Moxcel.h: interface for the CMoxcel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOXCEL_H__9B6E7324_0F0D_479C_9784_F89F58D96C8C__INCLUDED_)
#define AFX_MOXCEL_H__9B6E7324_0F0D_479C_9784_F89F58D96C8C__INCLUDED_
#include <afxtempl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCell
{
public:
	int nColumn;		//����� �������
	CString csText;		//����� ������
	CString csFormula;	//�����������

	CString csFormat;
	CString csMaska;

	byte nType;		//��� ������ ������ U(��������������),N(�����),S(������),B(����������),O(��������),T(����),K(��� ��������)
	int nLen;		//�����
	int nPrec;		//��������
	BOOL bProtect;	//���� ������ ������
	int nControl;	//�������� (0-����,1-��������,2-��������...)
	int nHPosition;	//��������� �� ����������� (0-����,2-�����,4-�� ������,6-�����) ������� �������� ����� - ���������� ��������, �� �������� ������������� ������
	int nVPosition;	//��������� �� ��������� (0-����,8-���,0x18-�����)
	//�����:
	int nRamkaColor;//���� ����� (0-55 �� �������)
	int nRamkaL;//�����
	int nRamkaU;//������
	int nRamkaR;//������
	int nRamkaD;//�����
	//�������� - �����:
	//1-�����1
	//8-�����2
	//2-������ �����
	//3-������� �����
	//4-����� ������� �����
	//5-������� �����
	//6-�������1
	//7-�������2
	//9-������� �������

	int nBackgroundColor;//���� ���� (0-55 �� �������)
	int nUzor;//���� (0-15)
	int nUzorColor;//���� ����� (0-55 �� �������)


	int nFontNumber;//����� ������ �� ������
	int nBold;//��������
	int nItalic;//�����������
	int nUnderLine;//�������������
	int nFontColor;//���� ������
	int nFontHeight;//������ ������


	CCell()
	{
		nColumn=0;
		nType=0;
		nLen=0;
		nPrec=0;
		bProtect=false;
		nControl=0;
		nHPosition=0;
		nVPosition=0;

		nRamkaColor=0;
		nRamkaL=0;
		nRamkaU=0;
		nRamkaR=0;
		nRamkaD=0;
		nBackgroundColor=0;
		nUzor=0;
		nUzorColor=0;

		nFontNumber=0;
		nBold=0;
		nItalic=0;
		nUnderLine=0;
		nFontColor=0;
		nFontHeight=0;


	};
};

class CRow
{
public:
	CRow();
	virtual ~CRow();
public:
	int nColumnCount;//����� ����������� �������
	CCell *aCell;
	int nRowHeight;//������ ������
public:
	void load(char *buf,int &nPos);
};

class CSection
{
public:
	CString csName;
	int nRange1;
	int nRange2;
};

class CMoxcel  
{
public:
	CMoxcel();
	virtual ~CMoxcel();
	void Clear(void);
public:
	int nAllColumnCount;//����� ������� � �������
	int nAllRowCount;//����� ����� � �������

	int nRowCount;//����� ����������� �����
	int *aRowNumber;//������ �����
	CRow *pRow;//������

	int nWidthCount;//������ ������� ������� ������ �������
	int *aWidthNumber;//������ ������� � ������� �������� ������
	int *aWidth;//������ �������

	int nFontCount;//���������� �������
	int *aFontNumber;//������ �������
	CString *aFont;//������

	int nMergeCells;//���������� ������������ �����
	int *aMergeCells;//������ ������������ �����

	//������:
	CArray <CSection,CSection> HorizSection;
	CArray <CSection,CSection> VertSection;

public:
	void load(char *buf);
};


//��� ������� �� ������ � 1� ��������
UINT GetPallete(int nIndex);
int GetRamka(int nIndex);
CGXPen GetStyleRamka(int nIndex,int nColor);
int GetUzor(int nIndex);

#endif // !defined(AFX_MOXCEL_H__9B6E7324_0F0D_479C_9784_F89F58D96C8C__INCLUDED_)
