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
	int nColumn;		//номер колонок
	CString csText;		//текст ячейки
	CString csFormula;	//расшифровка

	CString csFormat;
	CString csMaska;

	byte nType;		//тип данных ячейки U(неопределенный),N(число),S(строка),B(справчоник),O(документ),T(счет),K(вид субконто)
	int nLen;		//длина
	int nPrec;		//точность
	BOOL bProtect;	//флаг защиты ячейки
	int nControl;	//Контроль (0-Авто,1-обрезать,2-забивать...)
	int nHPosition;	//Положение по горизонтали (0-лево,2-право,4-по ширине,6-центр) старшая половина слова - количество столбцов, по которому выравнивается ячейка
	int nVPosition;	//Положение по вертикали (0-верх,8-низ,0x18-центр)
	//Рамка:
	int nRamkaColor;//цвет рамки (0-55 из палитры)
	int nRamkaL;//слева
	int nRamkaU;//сверху
	int nRamkaR;//справа
	int nRamkaD;//снизу
	//значения - стиль:
	//1-точки1
	//8-точки2
	//2-тонкая линия
	//3-толстая линия
	//4-очень толстая линия
	//5-двойная линия
	//6-пунктир1
	//7-пунктир2
	//9-толстый пунктир

	int nBackgroundColor;//цвет фона (0-55 из палитры)
	int nUzor;//Узор (0-15)
	int nUzorColor;//цвет узора (0-55 из палитры)


	int nFontNumber;//номер шрифта из списка
	int nBold;//жирность
	int nItalic;//наклонность
	int nUnderLine;//подчеркивание
	int nFontColor;//цвет шрифта
	int nFontHeight;//размер шрифта


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
	int nColumnCount;//число заполненных колонок
	CCell *aCell;
	int nRowHeight;//высота строки
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
	int nAllColumnCount;//всего колонок в таблице
	int nAllRowCount;//всего строк в таблице

	int nRowCount;//число заполненных строк
	int *aRowNumber;//номера строк
	CRow *pRow;//строки

	int nWidthCount;//размер массива задания ширины колонок
	int *aWidthNumber;//номера колонок у которых задается ширина
	int *aWidth;//ширина колонок

	int nFontCount;//количество шрифтов
	int *aFontNumber;//номера шрифтов
	CString *aFont;//шрифты

	int nMergeCells;//количество объединенных ячеек
	int *aMergeCells;//массив объединенных ячеек

	//секции:
	CArray <CSection,CSection> HorizSection;
	CArray <CSection,CSection> VertSection;

public:
	void load(char *buf);
};


//доп функции по работе с 1С форматом
UINT GetPallete(int nIndex);
int GetRamka(int nIndex);
CGXPen GetStyleRamka(int nIndex,int nColor);
int GetUzor(int nIndex);

#endif // !defined(AFX_MOXCEL_H__9B6E7324_0F0D_479C_9784_F89F58D96C8C__INCLUDED_)
