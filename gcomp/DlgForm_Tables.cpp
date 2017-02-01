
#include "DialogForm.h"


CHotKey::VK_Pair CHotKey::virtual_keys[] = {
	{0x01, "LButton"},
	{0x02, "RButton"},
	{0x08, "BackSpase"},
	{0x09, "Tab"},
	//{0x10, "Shift"},
	//{0x11, "Ctrl"},
	//{0x12, "Alt"},
	{0x0d, "Enter"},
	{0x13, "Pause"},
	{0x14, "CapsLock"},
	{0x1b, "Esc"},
	{0x20, "Space"},
	{0x21, "PgUp"},
	{0x22, "PgDn"},
	{0x23, "End"},
	{0x24, "Home"},
	{0x25, "Left"},
	{0x26, "Up"},
	{0x27, "Right"},
	{0x28, "Down"},
	{0x2c, "PrintScreen"},
	{0x2d, "Ins"},
	{0x2e, "Del"},
	{0x5d, "Apps"},
	{0x60, "Gray0"},
	{0x61, "Gray1"},
	{0x62, "Gray2"},
	{0x63, "Gray3"},
	{0x64, "Gray4"},
	{0x65, "Gray5"},
	{0x66, "Gray6"},
	{0x67, "Gray7"},
	{0x68, "Gray8"},
	{0x69, "Gray9"},
	{0x6a, "Gray*"},
	{0x6b, "Gray+"},
	{0x6c, "Separator"},
	{0x6d, "Gray-"},
	{0x6e, "GrayDecimal"},
	{0x6f, "Gray/"},
	{0x70, "F1"},
	{0x71, "F2"},
	{0x72, "F3"},
	{0x73, "F4"},
	{0x74, "F5"},
	{0x75, "F6"},
	{0x76, "F7"},
	{0x77, "F8"},
	{0x78, "F9"},
	{0x79, "F10"},
	{0x7a, "F11"},
	{0x7b, "F12"},
	{0x90, "NumLock"},
	{0x91, "ScrollLock"},
	{0xa0, "LShift"},
	{0xa1, "RShift"},
	{0xa2, "LControl"},
	{0xa3, "RControl"},
	{0x90, "NumLock"},
	{0, ""}
};

//===============================================================================
//======  CFormFont  ============================================================
//===============================================================================
CFormFont* CFormFont::DefVal = new CFormFont;
CObjectProperty CFormFont::Props[] = {
	{"�����",   13, CObjectProperty::t_string, VAR_OFFSET(DefVal, FontName)},
	{"������",  0,  CObjectProperty::t_prop, VAR_OFFSET(DefVal, FontSize)},
	{"Param2",  1,  CObjectProperty::t_int,  VAR_OFFSET(DefVal, Param2)},
	{"Param3",  2,  CObjectProperty::t_int,  VAR_OFFSET(DefVal, Param3)},
	{"Param4",  3,  CObjectProperty::t_int,  VAR_OFFSET(DefVal, Param4)},
	{"������",  4,  CObjectProperty::t_prop, VAR_OFFSET(DefVal, FontBold)},
	{"������",  5,  CObjectProperty::t_prop, VAR_OFFSET(DefVal, FontItalic)},
	{"�������������", 6, CObjectProperty::t_prop, VAR_OFFSET(DefVal, FontUnderline)},
	{"Param8",  7,  CObjectProperty::t_int, VAR_OFFSET(DefVal, Param8)},
	{"Param9",  8,  CObjectProperty::t_int, VAR_OFFSET(DefVal, Param9)},
	{"Param10", 9,  CObjectProperty::t_int, VAR_OFFSET(DefVal, Param10)},
	{"Param11", 10, CObjectProperty::t_int, VAR_OFFSET(DefVal, Param11)},
	{"Param12", 11, CObjectProperty::t_int, VAR_OFFSET(DefVal, Param12)},
	{"Param13", 12, CObjectProperty::t_int, VAR_OFFSET(DefVal, Param13)},
	{NULL, 0, CObjectProperty::t_int, 0}
};
CPropertySet CFormFont::PropSet(Props, DefVal);


//===============================================================================
//======  CFormControlBase  =====================================================
//===============================================================================
char* CFormControlBase::FlagList[] = {
	"Flag0",				//0
	"Flag1",				//1
	"Flag2",				//2
	"����������������",		//3
	"Flag4",				//4
	"�����������������",	//5 (CHECKBOX - �����������������; 1CEDIT - ��� ����� ������)
	"�����������������",	//6
	"Flag7",				//7
	"Flag8",				//8
	"Flag9",				//9
	"Flag10",				//10
	"Flag11",				//11
	"�����������������",	//12
	"Flag13",				//13
	"Flag14",				//14
	"Flag15",				//15
	"Flag16",				//16
	"�������������",		//17
	"Flag18",				//18
	"Flag19",				//19
	"Flag20",				//20
	"Flag21",				//21
	"Flag22",				//22
	"Flag23",				//23
	"Flag24",				//24
	"Flag25",				//25
	"Flag26",				//26
	"Flag27",				//27
	"Flag28",				//28
	"Flag29",				//29
	"Flag30",				//30
	"Flag31"				//31
};

char* CFormControlBase::BasicFlagList[] = {
	"Flag0",						//0
	"Flag1",						//1
	"������������������",			//2
	"Flag3",						//3
	"��������������������",			//4
	"��������",						//5 // ����� ������� ���������. ������ ������. �� �� ������.
	"����������������",				//6
	"��������������",				//7
	"�����������������",			//8
	"�������������",				//9
	"����������������",				//10
	"�����������������������",		//11
	"�������������",				//12
	"��������",						//13
	"����������",					//14
	"Flag15",						//15
	"�������������",				//16
	"������������",					//17
	"�������������",				//18
	"�������������",				//19
	"���������",					//20
	"Flag21",						//21
	"������������",					//22
	"�������������",				//23
	"�����������",					//24
	"����������",					//25
	"��������������������",			//26
	"���������������������",		//27
	"�����������������������",		//28
	"Flag29",						//29
	"Flag30",						//30
	"Flag31"						//31
};

char* CFormControlBase::ValueFlagList[] = {
	"���������������",
	"���������������",
	"Bit2", //�� ������ ������ ������� �����
	"Bit3",
	"Bit4",
	"Bit5",
	"Bit6",
	"Bit7"
};

//===============================================================================
//======  CFormControl  =========================================================
//===============================================================================
CFormControl* CFormControl::DefVal = new CFormControl;
CObjectProperty CFormControl::Props[] = {
	{"�����",          1, CObjectProperty::t_string, VAR_OFFSET(DefVal, Class)},
	{"�������������", 12, CObjectProperty::t_string, VAR_OFFSET(DefVal, Identifier)},
	{"���������",      0, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Caption)},
	{"�����������������������", 13, CObjectProperty::t_prop, VAR_OFFSET(DefVal, ObjectID)},
	{"���",           14, CObjectProperty::t_subobject, VAR_OFFSET(DefVal, Type)},
	{"�������������", 18, CObjectProperty::t_prop, VAR_OFFSET(DefVal, ValueFlags)},
	{"��������",       2, CObjectProperty::t_prop, VAR_OFFSET(DefVal, Flags)},
	{"X",              3, CObjectProperty::t_int, VAR_OFFSET(DefVal, PosX)},
	{"Y",              4, CObjectProperty::t_int, VAR_OFFSET(DefVal, PosY)},
	{"������",         5, CObjectProperty::t_int, VAR_OFFSET(DefVal, Width)},
	{"������",         6, CObjectProperty::t_int, VAR_OFFSET(DefVal, Height)},
	{"�������",        7, CObjectProperty::t_bool, VAR_OFFSET(DefVal, IsObjectAttribute)},
	{"Param9",         8, CObjectProperty::t_int, VAR_OFFSET(DefVal, Param9)},
	{"�������������",  9,  CObjectProperty::t_int, VAR_OFFSET(DefVal, TabOrder)},
	{"Param11",       10, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param11)},
	{"�������",       11, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Formula)},
	{"��������",      19, CObjectProperty::t_prop, VAR_OFFSET(DefVal, BasicFlags)},
	{"�����",         20, CObjectProperty::t_string, VAR_OFFSET(DefVal, Mask)},
	{"Hint",          21, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, LongHint)},
	{"ShortHint",     22, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, ShortHint)},
	{"Param24",       23, CObjectProperty::t_int, VAR_OFFSET(DefVal, Param24)},
	{"�����",         24, CObjectProperty::t_subobject, VAR_OFFSET(DefVal, Font)},
	{"����������",    38, CObjectProperty::t_int, VAR_OFFSET(DefVal, FontColor)},
	{"Param40",       39, CObjectProperty::t_int, VAR_OFFSET(DefVal, Param40)},
	{"�����������",   40, CObjectProperty::t_uint, VAR_OFFSET(DefVal, PictureID)},
	{"����",          41, CObjectProperty::t_string, VAR_OFFSET(DefVal, Layer)},
	{"HotKey",        42, CObjectProperty::t_object, VAR_OFFSET(DefVal, HotKey)},
	{NULL, 0, CObjectProperty::t_int, 0}
};
CPropertySet CFormControl::PropSet(Props, DefVal);

//===============================================================================
//======  CFormColumn  ==========================================================
//===============================================================================
CFormColumn* CFormColumn::DefVal = new CFormColumn;
CObjectProperty CFormColumn::Props[] = {
	{"�����",           3, CObjectProperty::t_string, VAR_OFFSET(DefVal, Class)},
	{"�������������",   7, CObjectProperty::t_string, VAR_OFFSET(DefVal, Identifier)},
	{"���������",       1, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Caption)},
	{"�����������������������", 8,  CObjectProperty::t_prop, VAR_OFFSET(DefVal, ObjectID)},
	{"���",             9, CObjectProperty::t_subobject, VAR_OFFSET(DefVal, Type)},
	{"�������������",  13, CObjectProperty::t_prop, VAR_OFFSET(DefVal, ValueFlags)},
	{"����������",      0, CObjectProperty::t_int, VAR_OFFSET(DefVal, ColumnType)},
	{"������",          2, CObjectProperty::t_int, VAR_OFFSET(DefVal, Width)},
	{"�������������",   4, CObjectProperty::t_int, VAR_OFFSET(DefVal, TabOrder)},
	{"Param6",          5, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param6)},
	{"�������",         6, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Formula)},
	{"Param15",        14, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param15)},
	{"Param16",        15, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param16)},
	{"������������",   16, CObjectProperty::t_int, VAR_OFFSET(DefVal, TextAlignment)},
	{"��������",       17, CObjectProperty::t_prop, VAR_OFFSET(DefVal, BasicFlags)},
	{"�����",          18, CObjectProperty::t_string, VAR_OFFSET(DefVal, Mask)},
	{"Hint",           19, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, LongHint)},
	{"ShortHint",      20, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, ShortHint)},
	{"Param22",        21, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param22)},
	{NULL, 0, CObjectProperty::t_int, 0}
};
CPropertySet CFormColumn::PropSet(Props, DefVal);


//===============================================================================
//======  CFormBrowser  =========================================================
//===============================================================================
CFormBrowser* CFormBrowser::DefVal = new CFormBrowser;
CObjectProperty CFormBrowser::Props[] = {
	//{"sID",         0, CObjectProperty::t_string,  VAR_OFFSET(DefVal, sID)},
	{"Param1",      0, CObjectProperty::t_int,  VAR_OFFSET(DefVal, Param1)},
	{"Param2",      1, CObjectProperty::t_int,  VAR_OFFSET(DefVal, Param2)},
	{"Multicolumn", 2, CObjectProperty::t_object,  VAR_OFFSET(DefVal, Multicolumn)},
	{"Fixed",       3, CObjectProperty::t_object,  VAR_OFFSET(DefVal, Fixed)},
	{NULL, 0, CObjectProperty::t_int, 0}
};
CPropertySet CFormBrowser::PropSet(Props, DefVal);



char* CDialogFrameContent::FlagList[] = {
	"FormFlag0",				//0
	"FormFlag1",				//1
	"FormFlag2",				//2
	"FormFlag3",				//3
	"FormFlag4",				//4
	"FormFlag5",				//5
	"FormFlag6",				//6
	"��������",					//7
	"�����������������",		//8
	"FormFlag9",				//9
	"����������������",			//10
	"�����������������������",	//11
	"FormFlag12",				//12
	"FormFlag13",				//13
	"FormFlag14",				//14
	"FormFlag15",				//15
	"FormFlag16",				//16
	"FormFlag17",				//17
	"FormFlag18",				//18
	"FormFlag19",				//19
	"��������������������",		//20
	"FormFlag21",				//21
	"FormFlag22",				//22
	"FormFlag23",				//23
	"FormFlag24",				//24
	"FormFlag25",				//25
	"FormFlag26",				//26
	"FormFlag27",				//27
	"FormFlag28",				//28
	"FormFlag29",				//29
	"FormFlag30",				//30
	"FormFlag31"				//31
};

//===============================================================================
//======  CFormLayer  ===========================================================
//===============================================================================
CFormLayer* CFormLayer::DefVal = new CFormLayer;
CObjectProperty CFormLayer::Props[] = {
	{"sID",       0, CObjectProperty::t_string,  VAR_OFFSET(DefVal, sID)},
	{"���������", 1, CObjectProperty::t_prop,  VAR_OFFSET(DefVal, IsVisible)},
	{NULL, 0, CObjectProperty::t_int, 0}
};
CPropertySet CFormLayer::PropSet(Props, DefVal);

//===============================================================================
//======  CDialogFrameContent  ==================================================
//===============================================================================
CDialogFrameContent* CDialogFrameContent::DefVal = new CDialogFrameContent;
CObjectProperty CDialogFrameContent::Props[] = {
	{"�����",               0, CObjectProperty::t_subobject,  VAR_OFFSET(DefVal, Font)},
	{"������",              14, CObjectProperty::t_int,    VAR_OFFSET(DefVal, Width)},
	{"������",              15, CObjectProperty::t_int,    VAR_OFFSET(DefVal, Height)},
	{"���������",           16, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Caption)},
	{"Param18",             17, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param18)},
	{"Param19",             18, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param19)},
	{"�����",               19, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, Flags1)},
	{"Param21",             20, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param21)},
	{"����������������",    21, CObjectProperty::t_bool,   VAR_OFFSET(DefVal, FontDefault)},
	{"�����������������",   22, CObjectProperty::t_bool,   VAR_OFFSET(DefVal, AutoTabOrder)},
	{"Param24",             23, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param24)},
	{"Param25",             24, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param25)},
	{"��������",            25, CObjectProperty::t_int,    VAR_OFFSET(DefVal, BackgroundColor)},
	{"���������������������", 26, CObjectProperty::t_uint, VAR_OFFSET(DefVal, PictureID)},
	{"�����2",              27, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, Flags2)},
	{"����",                28, CObjectProperty::t_object, VAR_OFFSET(DefVal, Layers)},
	{"������������������",  29, CObjectProperty::t_bool,   VAR_OFFSET(DefVal, ShowPanel)},
	{"��������������",      30, CObjectProperty::t_bool,   VAR_OFFSET(DefVal, AllowResize)},
	{NULL, 0, CObjectProperty::t_int, 0}
};
CPropertySet CDialogFrameContent::PropSet(Props, DefVal);
