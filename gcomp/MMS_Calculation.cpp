
#include "CommonFunctions.h"
#include "Strings.h"
#include "NameTable.h"
#include "MMS_Filter.h"
#include "Storage.h"
#include "Container.h"
#include "MMS_Calculation.h"

///////////////////////////////////////////////////////////////////////
///////////  class CMMSCalcJournal methods  ///////////////////////////
///////////////////////////////////////////////////////////////////////
CCalcJournalFld* CCalcJournalFld::DefVal = new CCalcJournalFld;
CObjectProperty CCalcJournalFld::Props[] = {
	{"ID",                0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",     1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",       2, CObjectProperty::t_string, VAR_OFFSET(DefVal, Comment)},
	{"�������",           3, CObjectProperty::t_string, VAR_OFFSET(DefVal, Synonym)},
	{"���",               4, CObjectProperty::t_subobject, VAR_OFFSET(DefVal, Type)},
	{"���������������",   8, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, NonNegative)},
	{"��������� ������",  9, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, DivideTriades)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CCalcJournalFld::PropSet(Props, DefVal);

CCalcJournalFld::CCalcJournalFld()
{
	NonNegative = false;
	DivideTriades = false;
}


//--------------------------
CMMSCalcJournal* CMMSCalcJournal::DefVal = new CMMSCalcJournal;
CObjectProperty CMMSCalcJournal::Props[] = {
	{"ID",                  0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",       1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",         2, CObjectProperty::t_string, VAR_OFFSET(DefVal, Comment)},
	{"�������",             3, CObjectProperty::t_string, VAR_OFFSET(DefVal, Synonym)},
	{"����������",          4, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, Subconto)},
	{"�������������",       5, CObjectProperty::t_int,    VAR_OFFSET(DefVal, Period)},
	{"���� ������ �������", 6, CObjectProperty::t_int,    VAR_OFFSET(DefVal, StartDate)},
	{"��������� �������",   7, CObjectProperty::t_object, VAR_OFFSET(DefVal, FldList)},
	{"����� ����������",    8, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ResultLength)},
	{"�������� ����������", 9, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ResultPrec)},
	{"���������� ��",      10, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, WriteOn)},
	{"����� ������",       11, CObjectProperty::t_object, VAR_OFFSET(DefVal, Selections)},
	{"����� �������",      12, CObjectProperty::t_object, VAR_OFFSET(DefVal, Forms)},
	{"����� ������",       13, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, SelectionForm)},
	{"�������� �����",     14, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, MainForm)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CMMSCalcJournal::PropSet(Props, DefVal);

static CStoredSet::TSetPair CalcJournal_Period[] = {
	{0, "����"},
	{1, "������"},
	{2, "�����"},
	{3, "�������"},
	{4, "���"},
	{0, NULL}
};
static CStoredSet::TSetPair CalcJournal_WriteOn[] = {
	{0, "�� ����� ���������� �������"},
	{1, "�� ������ ���������� �������"},
	{0, NULL}
};

CMMSCalcJournal::CMMSCalcJournal()
{
	MMS_Type = MMS_CalcJournal;
	ToDestroyChildren = false;

	Period.SetTable(CalcJournal_Period);
	WriteOn.SetTable(CalcJournal_WriteOn);
}

CMMSObject* CMMSCalcJournal::CreateChild(const char* Name, const char* Value)
{
	if( _stricoll(Name, FldList.BeautyName()) == 0 )
		return &FldList;
	if( _stricoll(Name, Selections.BeautyName()) == 0 )
		return &Selections;
	if( _stricoll(Name, Forms.BeautyName()) == 0 )
		return &Forms;
	return NULL;
}

CMMSObject* CMMSCalcJournal::CreateChild(const char* Name, int MMS_Index)
{
	switch( MMS_Index )
	{
	case 7:
		return &FldList;
	case 11:
		return &Selections;
	case 12:
		return &Forms;
	}
	return NULL;
}

void CMMSCalcJournal::Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage)
{
	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		GCString JournalDir = GetObjectDir(Dir);
		CreateDirectory(JournalDir);

		ExtractMetadata(JournalDir, TypedTextStorage);
		ExtractDescriptions(JournalDir+"\\", TypedTextStorage, true);

		ExtractListForms(Forms, JournalDir, Storage, nt_rec->StorageName);
	}
	MMS_Filter.Up();
}

void CMMSCalcJournalList::Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage)
{
	int nChildren = GetNChildren();
	if( nChildren == 0 ) return;

	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		GCString JournalsDir = nt_rec->PrepareDirName(Dir);

		CreateDirectory(JournalsDir);

		CStorage JrStorage(Storage);
		JrStorage.Open(nt_rec->StorageName);
		for( int i = 0; i < nChildren; i++ )
		{
			CMMSCalcJournal* pJournal = (CMMSCalcJournal*)GetChild(i);
			pJournal->Decompile(JournalsDir, JrStorage, TypedTextStorage);
		}

		ExtractOrdering(Storage, JournalsDir);
	}
	MMS_Filter.Up();
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSCalcJournal methods  ///////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSCalcJournal::Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir)
{
	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);
	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		Msg(1, "INF: ��������������.%s", sID);
		GCString JournalDir = GetObjectDir(SrcDir);

		ImportDescriptions(TypedTextStorage, JournalDir+"\\", true);
		ImportListForms(Forms, Storage, JournalDir, nt_rec->StorageName);
	}
	MMS_Filter.Up();

	SendInfoMessage(InfoMsg_Progress, ++TotalObjectsProcessed);
}


///////////////////////////////////////////////////////////////////////
///////////  class CMMSCalcJournals methods  //////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSCalcJournalList::Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir)
{
	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);
	GCString JournalsDir = nt_rec->PrepareDirName(SrcDir);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		ImportOrdering(JournalsDir);

		Storage.Create(nt_rec->StorageName);
		for( int i = 0; i < GetNChildren(); i++ )
		{
			GetChild(i)->Compile(Storage, TypedTextStorage, JournalsDir);
		}
		Storage.Close();
	}
	MMS_Filter.Up();
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSCaclAlgorithm methods  /////////////////////////
///////////////////////////////////////////////////////////////////////
CMMSCaclAlgorithm* CMMSCaclAlgorithm::DefVal = new CMMSCaclAlgorithm;
CObjectProperty CMMSCaclAlgorithm::Props[] = {
	{"ID",                   0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",        1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",          2, CObjectProperty::t_string, VAR_OFFSET(DefVal, Comment)},
	{"�������",              3, CObjectProperty::t_string, VAR_OFFSET(DefVal, Synonym)},
	{"���������",            4, CObjectProperty::t_int,    VAR_OFFSET(DefVal, Priority)},
	{"Param6",               5, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param6)},
	{"Param7",               6, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param7)},
	{"��������� ����������", 7, CObjectProperty::t_object, VAR_OFFSET(DefVal, Exclusion)},
	{"�������� � ������",    8, CObjectProperty::t_object, VAR_OFFSET(DefVal, InGroups)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CMMSCaclAlgorithm::PropSet(Props, DefVal);

CMMSObject* CMMSCaclAlgorithm::CreateChild(const char* Name, const char* Value)
{
	if( _stricoll(Name, Exclusion.BeautyName()) == 0 )
		return &Exclusion;
	if( _stricoll(Name, InGroups.BeautyName()) == 0 )
		return &InGroups;
	return NULL;
}

CMMSObject* CMMSCaclAlgorithm::CreateChild(const char* Name, int MMS_Index)
{
	switch( MMS_Index )
	{
	case 7:
		return &Exclusion;
	case 8:
		return &InGroups;
	}
	return NULL;
}

void CMMSCaclAlgorithm::Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage)
{
	CNameTableRecord* nt_rec_stor = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec_stor) )
	{
		Msg(2, "�������� ������� %s", sID);
		GCString AlgDir = GetObjectDir(Dir);
		CreateDirectory(AlgDir);

		ExtractMetadata(AlgDir, TypedTextStorage);

		//����� ������
		CNameTableRecord* nt_rec = NameTable.Find(NT_CalcAlgorithm);
		MMS_Filter.Down();
		if( MMS_Filter.Test(NULL, nt_rec) )
		{
			if( TypedTextStorage.Open(nt_rec_stor->PrepareStorageName(ID)) )
			{
				TypedTextStorage.CopyToFile((GCString)(nt_rec->StorageName), (GCString)(nt_rec->PrepareFileName(AlgDir)));
				TypedTextStorage.Close();
			}
		}
		MMS_Filter.Up();

		//��������
		ExtractDescriptions(AlgDir+"\\", TypedTextStorage, true);
	}
	MMS_Filter.Up();
}

void CMMSCaclAlgorithmList::Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage)
{
	int nChildren = GetNChildren();
	if( nChildren == 0 ) return;

	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		GCString AlgsDir = nt_rec->PrepareDirName(Dir);

		CreateDirectory(AlgsDir);

		for( int i = 0; i < nChildren; i++ )
		{
			GetChild(i)->Decompile(AlgsDir, Storage, TypedTextStorage);
		}

		ExtractOrdering(Storage, AlgsDir);
	}
	MMS_Filter.Up();
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSCaclAlgorithm methods  /////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSCaclAlgorithm::Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir)
{
	CNameTableRecord* nt_rec_stor = NameTable.Find(MMS_Type);
	CNameTableRecord* nt_rec_file = NameTable.Find(NT_CalcAlgorithm);
	GCString AlgDir = GetObjectDir(SrcDir);
	GCString FileName;

	FileName = nt_rec_file->PrepareFileName(AlgDir);
	if( FileExist(FileName) )
	{
		Msg(1, "INF: ���������������.%s", sID);

		TypedTextStorage.Create(nt_rec_stor->PrepareStorageName(ID));
		TypedTextStorage.StreamFromFile(nt_rec_file->StorageName, FileName);
		
		CContainer CC;
		CC.CreateInTypedText(TypedTextStorage);

		TypedTextStorage.Close();
	}

	ImportDescriptions(TypedTextStorage, AlgDir+"\\", true);
	SendInfoMessage(InfoMsg_Progress, ++TotalObjectsProcessed);
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSCaclAlgorithms methods  ////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSCaclAlgorithmList::Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir)
{
	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		GCString AlgsDir = nt_rec->PrepareDirName(SrcDir);
		
		ImportOrdering(AlgsDir);

		for( int i = 0; i < GetNChildren(); i++ )
		{
			GetChild(i)->Compile(Storage, TypedTextStorage, AlgsDir);
		}
	}
	MMS_Filter.Up();
}

///////////////////////////////////////////////////////////
//////  �������  �����������  /////////////////////////////
///////////////////////////////////////////////////////////
CMMSRecalcRule* CMMSRecalcRule::DefVal = new CMMSRecalcRule;
CObjectProperty CMMSRecalcRule::Props[] = {
	{"ID",                     0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",          1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",            2, CObjectProperty::t_string, VAR_OFFSET(DefVal, Comment)},
	{"�������",                3, CObjectProperty::t_string, VAR_OFFSET(DefVal, Synonym)},
	{"������ ��� ���������",   4, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, When)},
	{"������������� ��������", 5, CObjectProperty::t_int,    VAR_OFFSET(DefVal, NumPeriods)},
	{"��� �������������",      6, CObjectProperty::t_object, VAR_OFFSET(DefVal, Dependent)},
	{"����� �������������",    7, CObjectProperty::t_object, VAR_OFFSET(DefVal, Base)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CMMSRecalcRule::PropSet(Props, DefVal);

static CStoredSet::TSetPair RecalcRule_When[] = {
	{0, "������ � ������� ������� ��"},
	{1, "� ��� �� ������� ��"},
	{2, "� ��������� N ��������"},
	{0, NULL}
};

CMMSRecalcRule::CMMSRecalcRule()
{
	ToDestroyChildren = false;

	When = -1;
	NumPeriods = -1;

	When.SetTable(RecalcRule_When);
}


CMMSObject* CMMSRecalcRule::CreateChild(const char* Name, const char* Value)
{
	if( _stricoll(Name, Dependent.BeautyName()) == 0 )
		return &Dependent;
	if( _stricoll(Name, Base.BeautyName()) == 0 )
		return &Base;
	return NULL;
}

CMMSObject* CMMSRecalcRule::CreateChild(const char* Name, int MMS_Index)
{
	switch( MMS_Index )
	{
	case 6:
		return &Dependent;
	case 7:
		return &Base;
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSCaclAlgGroup methods  //////////////////////////
///////////////////////////////////////////////////////////////////////
CMMSCaclAlgGroup* CMMSCaclAlgGroup::DefVal = new CMMSCaclAlgGroup;
CObjectProperty CMMSCaclAlgGroup::Props[] = {
	{"ID",            0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������", 1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",   2, CObjectProperty::t_string, VAR_OFFSET(DefVal, Comment)},
	{"�������",       3, CObjectProperty::t_string, VAR_OFFSET(DefVal, Synonym)},
	{"������ ������", 4, CObjectProperty::t_object, VAR_OFFSET(DefVal, Algs)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CMMSCaclAlgGroup::PropSet(Props, DefVal);

CMMSObject* CMMSCaclAlgGroup::CreateChild(const char* Name, int MMS_Index)
{
	switch( MMS_Index )
	{
	case 4:
		return &Algs;
	}
	return NULL;
}

CMMSObject* CMMSCaclAlgGroup::CreateChild(const char* Name, const char* Value)
{
	if( _stricoll(Name, Algs.BeautyName()) == 0 )
		return &Algs;
	return NULL;
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSCalendar methods  //////////////////////////////
///////////////////////////////////////////////////////////////////////
CMMSCalendar* CMMSCalendar::DefVal = new CMMSCalendar;
CObjectProperty CMMSCalendar::Props[] = {
	{"ID",               0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",    1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",      2, CObjectProperty::t_string, VAR_OFFSET(DefVal, Comment)},
	{"�������",          3, CObjectProperty::t_string, VAR_OFFSET(DefVal, Synonym)},
	{"��������� ����",   4, CObjectProperty::t_int,    VAR_OFFSET(DefVal, StartDate)},
	{"���",              5, CObjectProperty::t_object, VAR_OFFSET(DefVal, Days)},
	{"������� ��������", 6, CObjectProperty::t_object, VAR_OFFSET(DefVal, MigrationRules)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CMMSCalendar::PropSet(Props, DefVal);

CMMSCalendar* CMMSCalendar::HolydaysDefVal = new CMMSCalendar;
CObjectProperty CMMSCalendar::HolydaysProps[] = {
	{"�������������", 0, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"���������",     1, CObjectProperty::t_object, VAR_OFFSET(DefVal, Holydays)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CMMSCalendar::HolydaysPropSet(HolydaysProps, HolydaysDefVal);

bool CMMSCalendar::SetValue(int MMS_Index, GCString& Value)
{
	if( MMS_Index == 0 && Value == "HolidaysDef" )
	{
		MMS_Type = MMS_Holydays;
	}
	return CStoredObject::SetValue(MMS_Index, Value);
}

CPropertySet* CMMSCalendar::GetPropSet()
{
	if( MMS_Type == MMS_Holydays )
		return &HolydaysPropSet;
	else
		return &PropSet;
}

CMMSObject* CMMSCalendar::CreateChild(const char* Name, int MMS_Index)
{
	if( MMS_Type == MMS_Holydays )
	{
		return &Holydays;
	}

	if( Name != NULL )
	{
		if( _stricoll(Name, Days.BeautyName()) == 0 )
			return &Days;
		if( _stricoll(Name, MigrationRules.BeautyName()) == 0 )
			return &MigrationRules;
	}

	switch( MMS_Index )
	{
	case 5:
		return &Days;
	case 6:
		return &MigrationRules;
	}

	return NULL;
}

void CMMSCalendar::BeautyString(CBeautyString& String, int level)
{
	if( MMS_Type == MMS_Calendar )
	{
		CMMSObjectAttribute::BeautyString(String, level);
	}
	else
	{
		Holydays.BeautyString(String, level);
	}
}

void CMMSCalendar::ToString(CMMSString& String)
{
	if( MMS_Type == MMS_Holydays )
	{
		sID = "HolidaysDef";
		Holydays.ID = ID;
		Holydays.MigrationRules = MigrationRules;
	}
	CMMSObjectAttribute::ToString(String);
}

CMMSHolydays* CMMSHolydays::DefVal = new CMMSHolydays;
CObjectProperty CMMSHolydays::Props[] = {
	{"ID",               0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",    1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",      2, CObjectProperty::t_string, VAR_OFFSET(DefVal, Comment)},
	{"�������",          3, CObjectProperty::t_string, VAR_OFFSET(DefVal, Synonym)},
	{"������� ��������", 4, CObjectProperty::t_object, VAR_OFFSET(DefVal, MigrationRules)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CMMSHolydays::PropSet(Props, DefVal);

void CMMSHolydays::BeautyString(CBeautyString& String, int level)
{
	sID = "���������";
	CMMSObjectAttribute::BeautyString(String, level, false);
}

void CMMSHolydays::ToString(CMMSString& String)
{
	CMMSObjectAttribute::ToString(String);
}


void CMMSCalendarList::ToString(CMMSString& String)
{
	if( GetNChildren() > 0 )
		GetChild(GetNChildren()-1)->MMS_Type = MMS_Holydays;
	CMMSAttributes::ToString(String);
}
