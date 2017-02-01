
#include "CommonFunctions.h"
#include "Strings.h"
#include "Storage.h"
#include "NameTable.h"
#include "MMS_Filter.h"
#include "MMS_Subconto.h"


CSbCntParam* CSbCntParam::DefVal = new CSbCntParam;
CObjectProperty CSbCntParam::Props[] = {
	{"ID",               0, CObjectProperty::t_int,  VAR_OFFSET(DefVal, ID)},
	{"sID",              1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",      2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",          3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"��� ��������",    11, CObjectProperty::t_prop, VAR_OFFSET(DefVal, ForElement)},
	{"��� ������",      12, CObjectProperty::t_prop, VAR_OFFSET(DefVal, ForGroup)},
	{"���",              4, CObjectProperty::t_subobject, VAR_OFFSET(DefVal, Type)},
	{"���������������",  8, CObjectProperty::t_prop, VAR_OFFSET(DefVal, NotNegative)},
	{"��������� ������", 9, CObjectProperty::t_prop, VAR_OFFSET(DefVal, DivideTriades)},
	{"�������������",   10, CObjectProperty::t_prop, VAR_OFFSET(DefVal, Periodical)},
	{"��������� ������� �����������", 15, CObjectProperty::t_prop, VAR_OFFSET(DefVal, HistChangedByDocs)},
	{"������ ��������� �������", 14, CObjectProperty::t_prop, VAR_OFFSET(DefVal, HistManualChanged)},
	{"����������",      13, CObjectProperty::t_prop, VAR_OFFSET(DefVal, Sorting)},
	{"�����",           16, CObjectProperty::t_prop, VAR_OFFSET(DefVal, Selection)},
	{NULL, -1, CObjectProperty::t_int, 0}
};

CPropertySet CSbCntParam::PropSet(Props, DefVal);


//============= CMMSSbCnt ====================================
CMMSSbCnt* CMMSSbCnt::DefVal = new CMMSSbCnt;
CObjectProperty CMMSSbCnt::Props[] = {
	{"ID",                      0, CObjectProperty::t_int,   VAR_OFFSET(DefVal, ID)},
	{"�������������",           1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",             2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",                 3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"��������",                4, CObjectProperty::t_prop,	VAR_OFFSET(DefVal, Owner)},
	{"����� ����",              5, CObjectProperty::t_int,	VAR_OFFSET(DefVal, CodeLength)},
	{"����� �����",             6, CObjectProperty::t_prop,	VAR_OFFSET(DefVal, CodeSeries)},
	{"��� ����",                7, CObjectProperty::t_prop,	VAR_OFFSET(DefVal, CodeType)},
	{"������������",            8, CObjectProperty::t_prop,	VAR_OFFSET(DefVal, AutoNumeration)},
	{"����� ������������",      9, CObjectProperty::t_int,	VAR_OFFSET(DefVal, NameLength)},
	{"�������� �������������", 10, CObjectProperty::t_prop,	VAR_OFFSET(DefVal, BasicRepresentation)},
	{"������ ��������������",  11, CObjectProperty::t_prop,	VAR_OFFSET(DefVal, EditWay)},
	{"���������� �������",     12, CObjectProperty::t_int,	VAR_OFFSET(DefVal, Levels)},
	{"����� ��� ������",       13, CObjectProperty::t_prop,	VAR_OFFSET(DefVal, ChoosingListForm)},
	{"�������� �����",         14, CObjectProperty::t_prop,	VAR_OFFSET(DefVal, MainListForm)},
	{"���� ����� ��� �������� � ������", 15, CObjectProperty::t_prop, VAR_OFFSET(DefVal, OneForm)},
	{"������������ �����",     16, CObjectProperty::t_prop,	VAR_OFFSET(DefVal, UniqueCodes)},
	{"������ ������",          17, CObjectProperty::t_prop,	VAR_OFFSET(DefVal, GroupsOnTop)},
	{"���������",              18, CObjectProperty::t_object,	VAR_OFFSET(DefVal, Parameters)},
	{"�����",                  19, CObjectProperty::t_object,	VAR_OFFSET(DefVal, Forms)},
	{"������� ��������",       20, CObjectProperty::t_object,	VAR_OFFSET(DefVal, MigrationRules)},
	{NULL, 0, CObjectProperty::t_int}
};

CPropertySet CMMSSbCnt::PropSet(Props, DefVal);

//������� ��� �������
static CStoredSet::TSetPair SbCntCodeSeries[] = {
	{1, "�� ��� �����������"},
	{2, "� �������� ����������"},
	{0, NULL}
};
static CStoredSet::TSetPair SbCntCodeTypes[] = {
	{1, "���������"},
	{2, "��������"},
	{0, NULL}
};
static CStoredSet::TSetPair SbCntAutoNumeration[] = {
	{1, "���"},
	{2, "��"},
	{0, NULL}
};
static CStoredSet::TSetPair SbCntBasicRepr[] = {
	{1, "� ���� ����"},
	{2, "� ���� ������������"},
	{0, NULL}
};
static CStoredSet::TSetPair SbCntEditWays[] = {
	{0, "� ������"},
	{1, "� �������"},
	{2, "������ ���������"},
	{0, NULL}
};
//�������� ������ ������� � ��������-������
void CMMSSbCnt::SetUpTables()
{
	CodeLength = 0;
	CodeSeries = 2;
	CodeType = 1;
	AutoNumeration = 2;
	NameLength = 0;
	BasicRepresentation = 2;
	EditWay = 2;
	Levels = 0;
	OneForm = false;
	UniqueCodes = true;
	GroupsOnTop = true;

	CodeSeries.SetTable(SbCntCodeSeries);
	CodeType.SetTable(SbCntCodeTypes);
	AutoNumeration.SetTable(SbCntAutoNumeration);
	BasicRepresentation.SetTable(SbCntBasicRepr);
	EditWay.SetTable(SbCntEditWays);
}

CMMSSbCnt::CMMSSbCnt()
{
	MMS_Type = MMS_SbCnt;
	ID_Type = IDT_BothIDs;
	ToDestroyChildren = false;

	SetUpTables();
}

CMMSObject* CMMSSbCnt::CreateChild(const char* Name, const char* Value)
{
	if( _stricoll(Name, Parameters.BeautyName()) == 0 )
		return &Parameters;
	if( _stricoll(Name, Forms.BeautyName()) == 0 )
		return &Forms;
	if( _stricoll(Name, MigrationRules.BeautyName()) == 0 )
		return &MigrationRules;

	return NULL;
}

CMMSObject* CMMSSbCnt::CreateChild(const char* Name, int MMS_Index)
{
	switch( MMS_Index )
	{
	case 18:
		return &Parameters;
	case 19:
		return &Forms;
	case 20:
		return &MigrationRules;
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////
///////////  ������ ������������  /////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSSbCnt::Decompile(GCString& BaseDir, CStorage& Storage, CStorage& TypedTextStorage, CStorage& SubFolderStorage, CStorage& SubListStorage)
{
	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);
	
	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		CStorage ScStorage(Storage);
		GCString ScDir = GetObjectDir(BaseDir);
		GCString StorName;
		CMMSObject* Params = FindChild( GCString("Params") );

		CreateDirectory(ScDir);

		Msg(2, "���������� %s", sID);

		//����������
		ExtractMetadata(ScDir, TypedTextStorage);
		//��������
		ExtractDescriptions(ScDir+"\\", TypedTextStorage, true);

		//����� ��������
		if( ScStorage.Open(nt_rec->PrepareStorageName(ID)) ) //�������� ����� � �� ����, ���� � ����������� ��� �����
		{
			ExtractWorkBook(ScDir, ScStorage, this);
		}

		//����� ������
		nt_rec = NameTable.Find(NT_SubcontoFolder);
		MMS_Filter.Down();
		if( MMS_Filter.Test(NULL, nt_rec) )
		{
			CStorage GroupStorage(SubFolderStorage);
			if( GroupStorage.Open(nt_rec->PrepareStorageName(ID)) != NULL )
			{
				GCString SubFldDir = nt_rec->PrepareDirName(ScDir);
				CreateDirectory(SubFldDir);
				ExtractWorkBook(SubFldDir, GroupStorage, this);
			}
		}
		MMS_Filter.Up();

		//����� �������
		nt_rec = NameTable.Find(NT_SubcontoListForm);
		ExtractListForms(Forms, ScDir, SubListStorage, nt_rec->StorageName);
	}

	MMS_Filter.Up();

	SendInfoMessage(InfoMsg_Progress, ++TotalObjectsProcessed);
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSSbCnts methods  ////////////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSSbCnts::Decompile(GCString& BaseDir, CStorage& Storage, CStorage& TypedTextStorage)
{
	int nChildren = GetNChildren();
	if( nChildren == 0 ) return;

	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		CStorage ScsStorage(Storage,       nt_rec->StorageName);
		CStorage SubFolderStorage(Storage, "SubFolder");
		CStorage SubListStorage(Storage,   "SubList");
		GCString  ScsDir = nt_rec->PrepareDirName(BaseDir);

		CreateDirectory(ScsDir);

		for( int i = 0; i < nChildren; i++ )
		{
			CMMSSbCnt* pSc = (CMMSSbCnt*)GetChild(i);
			pSc->Decompile(ScsDir, ScsStorage, TypedTextStorage, SubFolderStorage, SubListStorage);
		}

		ExtractOrdering(Storage, ScsDir);
	}
	MMS_Filter.Up();
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSSbCnt methods  /////////////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSSbCnt::Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& Dir, CStorage& SubFolderStorage, CStorage& SubListStorage)
{
	CNameTableRecord* nt_rec_sc = NameTable.Find(MMS_Type);
	CNameTableRecord* nt_rec;
	GCString ScDir = GetObjectDir(Dir);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec_sc) )
	{
		Msg(1, "INF: ����������.%s", sID);
		Storage.Create(nt_rec_sc->PrepareStorageName(ID));

		//����� ��������
		bool NotEmpty = ImportWorkBook(Storage, ScDir);
		Storage.Close();
		if( !NotEmpty )
			Storage.Delete(nt_rec_sc->PrepareStorageName(ID));

		//��������
		ImportDescriptions(TypedTextStorage, ScDir+"\\", true);
		
		//����� ������
		nt_rec = NameTable.Find(NT_SubcontoFolder);
		MMS_Filter.Down();
		if( MMS_Filter.Test(NULL, nt_rec) )
		{
			GCString SubFldDir = nt_rec->PrepareDirName(ScDir);
			if( DirectoryExist(SubFldDir) )
			{
				SubFolderStorage.Create(nt_rec->PrepareStorageName(ID));
				ImportWorkBook(SubFolderStorage, SubFldDir);
				SubFolderStorage.Close();
			}
		}
		MMS_Filter.Up();

		//����� �������
		nt_rec = NameTable.Find(NT_SubcontoListForm);
		ImportListForms(Forms, SubListStorage, ScDir, nt_rec->StorageName);
	}
	MMS_Filter.Up();

	SendInfoMessage(InfoMsg_Progress, ++TotalObjectsProcessed);
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSSbCnts methods  ////////////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSSbCnts::Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& Dir)
{
	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);
	CStorage SubFolderStorage(Storage);
	CStorage SubListStorage(Storage);
	GCString ScsDir;
	
	ScsDir.Format("%s\\%s", Dir, nt_rec->Dir);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		ImportOrdering(ScsDir);

		SubFolderStorage.Create(GCString("SubFolder"));
		SubListStorage.Create(GCString("SubList"));

		Storage.Create(nt_rec->StorageName);
		for( int i = 0; i < GetNChildren(); i++ )
		{
			CMMSSbCnt* Sc = (CMMSSbCnt*)GetChild(i);
			Sc->Compile(Storage, TypedTextStorage, ScsDir, SubFolderStorage, SubListStorage);
		}

		Storage.Close();
	}
	MMS_Filter.Up();
}
