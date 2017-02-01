// Moxcel.cpp: implementation of the CMoxcel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Moxcel.h"
#include "Const.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//****************************************************
CRow::CRow()
{
	nColumnCount=0;
	aCell=NULL;
	nRowHeight=0;
}
CRow::~CRow()
{
	if(aCell)
		delete []aCell;
}

//универсальные функции
void GetText(char *buf,CString &Str,int &nPos,bool bBig=true)
{
	Str="";
	int nLength=0;
	if(((unsigned char)buf[nPos])==0xFF)//bBig&&
	{
		nPos++;
		memcpy(&nLength,&buf[nPos],2);
		nPos+=2;
	}
	else
	{
		nLength=(unsigned char)buf[nPos];
		nPos++;
	}

	if(nLength<0||nLength>0xFFFF)
	{
		AfxMessageBox("Ошибка загрузки длины текста!");
		throw;
	}

	char *p=Str.GetBuffer(nLength+1);
	p[nLength]=0;
	memcpy(p,&buf[nPos],nLength);
	Str.ReleaseBuffer();
	nPos+=nLength;
}

int GetNumberArray(char *buf,int* &pArray,int &nPos,int nMult=1)
{
	int nArrayCount=0;
	memcpy(&nArrayCount,&buf[nPos],2);
	if(nArrayCount>0)
	{
		if(nArrayCount>10000)
		{
			AfxMessageBox("Ошибка загрузки размера массива!");
			throw;
		}
		nArrayCount=nArrayCount*nMult;
		pArray=new int[nArrayCount];
		ZeroMemory(pArray,nArrayCount*sizeof(int));
		//загружаем список номеров колонок
		for(int i=0;i<nArrayCount;i++)
		{
			nPos+=2;
			memcpy(&pArray[i],&buf[nPos],2);
			pArray[i]++;
			nPos+=2;
		}
	}
	nPos=nPos+2;
	return nArrayCount;
}

void CRow::load(char *buf,int &nPos)
{
	int *aColumnNumber=NULL;
	nColumnCount=GetNumberArray(buf,aColumnNumber,nPos);
	nPos+=2;
	if(nColumnCount>0)
	{
		aCell=new CCell[nColumnCount];

		//загружаем данные колонок
		for(int i=0;i<nColumnCount;i++)
		{
			aCell[i].nColumn=aColumnNumber[i];

			//byte pArray[100];
			//memcpy(pArray,&buf[nPos],sizeof(pArray));

			byte mode=(unsigned char)buf[nPos+2];
			byte flag=(unsigned char)buf[nPos+3];

 			BOOL bExtend=mode&(1<<5);//расш. формат
			BOOL bFormula=flag&(1<<6);//Расшифровка или Формула
			BOOL bText=flag&(1<<7);//Текст

			//Рамка:
			aCell[i].nRamkaColor=(unsigned char)buf[nPos+23];//цвет (0-55 из палитры)
			aCell[i].nRamkaL=(unsigned char)buf[nPos+18];//слева
			aCell[i].nRamkaU=(unsigned char)buf[nPos+19];//сверху
			aCell[i].nRamkaR=(unsigned char)buf[nPos+20];//справа
			aCell[i].nRamkaD=(unsigned char)buf[nPos+21];//снизу

			//Узор:
			aCell[i].nBackgroundColor=(unsigned char)buf[nPos+25];//цвет (0-55 из палитры)
			aCell[i].nUzor=(unsigned char)buf[nPos+17];//Узор (0-15)
			aCell[i].nUzorColor=(unsigned char)buf[nPos+22];//цвет узора (0-55 из палитры)

			aCell[i].nHPosition=(unsigned char)buf[nPos+15];//Положение по горизонтали (0-лево,2-право,4-по ширине,6-центр) старшая половина слова - количество столбцов, по которому выравнивается ячейка
			aCell[i].nHPosition=aCell[i].nHPosition&31;
			aCell[i].nVPosition=(unsigned char)buf[nPos+16];//Положение по вертикали (0-верх,8-низ,0x18-центр)
			aCell[i].nControl=(unsigned char)buf[nPos+26];	//Контроль (0-Авто,1-обрезать,2-забивать...)
			aCell[i].bProtect=(unsigned char)buf[nPos+28];	//флаг Защиты
			aCell[i].bProtect=!aCell[i].bProtect;

			aCell[i].nFontNumber=(unsigned char)buf[nPos+8];//номер шрифта из списка шрифтов
			aCell[i].nBold=(unsigned char)buf[nPos+12];//жирность
			//4-не жирн
			//7-жирн
			if(aCell[i].nBold>4)
				aCell[i].nBold=1;
			else
				aCell[i].nBold=0;
			aCell[i].nItalic=(unsigned char)buf[nPos+13];//наклонность
			aCell[i].nUnderLine=(unsigned char)buf[nPos+14];//подчеркивание
			aCell[i].nFontColor=(unsigned char)buf[nPos+24];//цвет шрифта
			short nFontH=0;//размер шрифта
			memcpy(&nFontH,&buf[nPos+10],2);
			nFontH=-nFontH/4;
			aCell[i].nFontHeight=nFontH;

			nPos+=0x20-2;
			if(bText)//текст
				GetText(buf,aCell[i].csText,nPos);
			if(bFormula)//Формула (расшифровка)
				GetText(buf,aCell[i].csFormula,nPos);

			aCell[i].nType=0;
			if(bExtend)
			{
				aCell[i].nType=buf[nPos+6];//U(неопределенный),N(число),S(строка),B(справчоник),O(документ),T(счет),K(вид субконто)
				aCell[i].nLen=(unsigned char)buf[nPos+7];
				aCell[i].nPrec=(unsigned char)buf[nPos+11];

				//длина нижней части
				int nLength=0;
				memcpy(&nLength,&buf[nPos],2);
				nPos+=2;

				int nPos2=nPos;//независимое позиционирование
				nPos2+=0x10+3;
				GetText(buf,aCell[i].csFormat,nPos2);//формат
				nPos2+=6;
				GetText(buf,aCell[i].csMaska,nPos2);//маска

				nPos+=nLength;
			}

		}
		delete []aColumnNumber;
	}
}


//****************************************************
CMoxcel::CMoxcel()
{
	nAllColumnCount=0;
	nAllRowCount=0;

	nRowCount=0;
	aRowNumber=NULL;
	pRow=NULL;
	aWidth=NULL;
	aWidthNumber=NULL;
	nWidthCount=0;

	nFontCount=0;
	aFontNumber=NULL;
	aFont=NULL;

	nMergeCells=0;
	aMergeCells=NULL;
}
void CMoxcel::Clear(void)
{
	if(aRowNumber)
		delete []aRowNumber;
	if(aWidthNumber)
		delete []aWidthNumber;
	if(aWidth)
		delete []aWidth;

	if(aFontNumber)
		delete []aFontNumber;
	if(aFont)
		delete []aFont;

	if(pRow)
		delete []pRow;

	if(aMergeCells)
		delete []aMergeCells;
}
CMoxcel::~CMoxcel()
{
	Clear();
}
void CMoxcel::load(char *buf)
{
	Clear();
	int nPos;
	//загружаем
	nPos=13;
	memcpy(&nAllColumnCount,&buf[nPos],8);//количество колонок и строк всего

	nPos=0x37;
	//шрифты
	nFontCount=GetNumberArray(buf,aFontNumber,nPos);
	nPos+=2;
	if(nFontCount>0)
	{
		aFont=new CString[nFontCount];
		for(int i=0;i<nFontCount;i++)
		{
			nPos+=28;
			int nLength=0x20;
			memcpy(aFont[i].GetBuffer(nLength),&buf[nPos],nLength);
			aFont[i].ReleaseBuffer();
			nPos+=0x40-4-28;
		}
	}

	nPos+=0x40;



	//ширина столбцов
	nWidthCount=GetNumberArray(buf,aWidthNumber,nPos);
	nPos+=2;
	if(nWidthCount>0)
	{
		aWidth=new int[nWidthCount];
		for(int i=0;i<nWidthCount;i++)
		{
			nPos+=6;
			aWidth[i]=(unsigned char)buf[nPos];
			nPos+=24;
		}
	}

	//строки
	nRowCount=GetNumberArray(buf,aRowNumber,nPos);
	nPos+=2;
	if(nRowCount>0)
	{
		pRow=new CRow[nRowCount];
		for(int i=0;i<nRowCount;i++)
		{
			//byte pArray[100];
			//memcpy(pArray,&buf[nPos],sizeof(pArray));

			pRow[i].nRowHeight=0;
			memcpy(&pRow[i].nRowHeight,&buf[nPos+4],2);
			pRow[i].nRowHeight=pRow[i].nRowHeight/3;

			nPos+=0x20-2;
			pRow[i].load(buf,nPos);
		}
	}

	//byte pArray[100];
	//buf[nPos] - количество доп. объектов типа Прямоугольник, Картинка, Диаграмма, OLE-объект
	//загрузка доп объектов
	int nCount=0;
	memcpy(&nCount,&buf[nPos],2);

	nPos+=2;
	int nOLEDelta=18;//дельта только для первого ОЛЕ объекта (почему не знаю, но это так)
	for(int i=0;i<nCount;i++)
	{
		//memcpy(pArray,&buf[nPos],sizeof(pArray));
		int nType=(unsigned char)buf[nPos+2];//тип объекта
		//0-простой объект (линия, квадрат, блок с текстом)
		//8-сложный объект (картинка, диаграмма 1С, ОЛЕ обьект)
		BOOL bText=(unsigned char)buf[nPos+3]&0x80;//признак блока с текстом
		BOOL bFormula=(unsigned char)buf[nPos+3]&0x40;//признак блока с расшифровкой
		if(bText)
			bText=1;
		if(bFormula)
			bFormula=1;


		nPos+=30;
		CString csText;
		if(bText)
			GetText(buf,csText,nPos);//текст
		if(bFormula)
			GetText(buf,csText,nPos);//расшифровка
//		if(bText||bFormula)
//			nPos=-16;
		//memcpy(pArray,&buf[nPos],sizeof(pArray));
		int nKind=(unsigned char)buf[nPos];//вид объекта
		//1-линия
		//2-квадрат
		//3-блок текста (но без текста)
		//4-ОЛЕ обьект (в т.ч. диаграмма 1С)
		//5-картинка

		if(nKind<=3||nType==0)
			nPos+=40;
		else
		if(nKind==4)//ОЛЕ объект
		{
			int nLength=0;
			memcpy(&nLength,&buf[nPos+60+nOLEDelta],4);
			nPos+=64+nOLEDelta+nLength;
			nOLEDelta=0;
		}
		else//картинка
		if(nKind==5)
		{
			//memcpy(pArray,&buf[nPos],sizeof(pArray));
			int nPictureType=(unsigned char)buf[nPos+16];//тип картинки

			int nLength=0;
			memcpy(&nLength,&buf[nPos+44],4);
			nPos+=nLength+48;
/*
			if(nLength==0)
				nPos+=48;//пустая картинка
			else
			{
				int nLength=0;
				memcpy(&nLength,&buf[nPos+0x52],4);
				//memcpy(&nLength,&buf[nPos+44],4);

				int nLength2=0;
				memcpy(&nLength2,&buf[nPos+58],4);

				nPos+=nLength+nLength2+48;//0x52-34;//не пустая картинка

			}
//*/
		}
		else//неизвестный объект
		{
			CString Str;
			Str.Format("Встретился неизвестный объект N %d",nKind);
			AfxMessageBox(Str);
			return;

		}

	}

	//buf[nPos] - количество объединенных ячеек
	nCount=0;
	memcpy(&nCount,&buf[nPos],2);
	//загружаем объединенные ячейки
	nMergeCells=GetNumberArray(buf,aMergeCells,nPos,4)/4;

	//загружаем секции:
	//вертикальные
	//memcpy(pArray,&buf[nPos],sizeof(pArray));
	nCount=0;
	memcpy(&nCount,&buf[nPos],2);
	nPos+=2;
	for(i=0;i<nCount;i++)
	{
		CSection data;
		data.nRange1=0;
		data.nRange2=0;

		memcpy(&data.nRange1,&buf[nPos],4);
		nPos+=4;
		memcpy(&data.nRange2,&buf[nPos],4);
		nPos+=4;
		nPos+=4;
		GetText(buf,data.csName,nPos);
		VertSection.Add(data);
		//AfxMessageBox(data.csName);
	}
	//горизонтальные
	nCount=0;
	memcpy(&nCount,&buf[nPos],2);
	nPos+=2;
	for(i=0;i<nCount;i++)
	{
		CSection data;
		data.nRange1=0;
		data.nRange2=0;

		memcpy(&data.nRange1,&buf[nPos],4);
		nPos+=4;
		memcpy(&data.nRange2,&buf[nPos],4);
		nPos+=4;
		nPos+=4;
		GetText(buf,data.csName,nPos);
		HorizSection.Add(data);
		//AfxMessageBox(data.csName);
	}

	//загружаем именованные ячейки


}



//доп функции по работе с 1С форматом
//Палитра цветов 1С
UINT GetPallete(int nIndex)
{

	UINT a1CPallete[]=
	{
//		0xRRGGBB,
		0x000000,
		0xFFFFFF,
		0xFF0000,
		0x00FF00,
		0x0000FF,
		0xFFFF00,
		0xFF00FF,
		0x00FFFF,

		0x800000,
		0x008000,
		0x808000,
		0x000080,
		0x800080,
		0x008080,
		0x808080,
		0xC0C0C0,

		0x8080FF,
		0x802060,
		0xFFFFC0,
		0xA0E0E0,
		0x600080,
		0xFF8080,
		0x0080C0,
		0xC0C0FF,

		0x00CFFF,
		0x69FFFF,
		0xE0FFED,
		0xDD9CB3,
		0xB38FEE,
		0x2A6FF9,
		0x3FB8CD,
		0x488436,

		0x958C41,
		0x8E5E42,
		0xA0627A,
		0x624FAC,
		0x1D2FBE,
		0x286676,
		0x004500,
		0x453E01,

		0x6A2813,
		0x85396A,
		0x4A3285,
		0xC0DCC0,
		0xA6CAF0,
		0x800000,
		0x008000,
		0x000080,

		0x808000,
		0x800080,
		0x008080,
		0x808080,
		0xFFFBF0,
		0xA0A0A4,
		0x313900,
		0xD98534
	};

	if(nIndex<0||nIndex>=sizeof(a1CPallete))
		return 0;

	UINT nRes=a1CPallete[nIndex];
	return RGB(nRes>>16&0xFF,nRes>>8&0xFF,nRes&0xFF);
}


int GetRamka(int nIndex)
{
	nIndex=nIndex&15;
	int aRamka[]=
	{
		10+PS_NULL,//0
		10+PS_DOT,//1-точки1
		10+PS_SOLID,//2-тонкая линия
		20+PS_SOLID,//3-толстая линия
		20+PS_SOLID,//4-очень толстая линия
		10+PS_SOLID,//5-двойная линия
		10+PS_DASH,//6-пунктир1
		10+PS_DASHDOT,//7-пунктир2
		10+PS_DOT,//DOTDOT,//8-точки2
		20+PS_DASH,//9-толстый пунктир
	};

	if(nIndex<0||nIndex>=sizeof(aRamka))
		return PS_NULL;

//#define PS_SOLID            0
//#define PS_DASH             1       /* -------  */
//#define PS_DOT              2       /* .......  */
//#define PS_DASHDOT          3       /* _._._._  */
//#define PS_DASHDOTDOT       4       /* _.._.._  */
//#define PS_NULL             5


	return aRamka[nIndex];
}


CGXPen GetStyleRamka(int nIndex,int nColor)
{
//	return CGXPen();
	int nStyle=GetRamka(nIndex);
	return CGXPen().SetStyle(nStyle%10).SetWidth(nStyle/10).SetColor(GetPallete(nColor));//SetWidth
}

int GetUzor(int nIndex)
{

	nIndex=nIndex&15;
	int aUzor[]=
	{
		33,
		0,
		1,
		2,
		22,
		17,
		7,
		6,
		14,
		15,
		10,
		11,
		31,
		30,
		21,
		20
	};

	if(nIndex<=0||nIndex>=sizeof(aUzor))
		return 33;
	return aUzor[nIndex];
}
