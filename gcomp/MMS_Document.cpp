
#include "CommonFunctions.h"
#include "Storage.h"
#include "Container.h"
#include "NameTable.h"
#include "MMS_Filter.h"
#include "MMS_Document.h"

///////////////////////////////////////////////////////////////////////
///////////  class �GenJrnlFldDef tables and methods  //////////////////
///////////////////////////////////////////////////////////////////////
CGenJrnlFldDef* CGenJrnlFldDef::DefVal = new CGenJrnlFldDef;
CObjectProperty CGenJrnlFldDef::Props[] = {
	{"ID",                0, CObjectProperty::t_int, VAR_OFFSET(DefVal, ID)},
	{"�������������",     1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",       2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",           3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"���",               4, CObjectProperty::t_subobject, VAR_OFFSET(DefVal, Type)},
	{"���������������",   8, CObjectProperty::t_prop, VAR_OFFSET(DefVal, NonNegative)},
	{"��������� ������",  9, CObjectProperty::t_prop, VAR_OFFSET(DefVal, DivideTriades)},
	{"�����",            10, CObjectProperty::t_prop, VAR_OFFSET(DefVal, Selection)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CGenJrnlFldDef::PropSet(Props, DefVal);

CGenJrnlFldDef::CGenJrnlFldDef()
{
	NonNegative = false;
	DivideTriades = false;
	Selection = false;
}

///////////////////////////////////////////////////////////////////////
///////////  class CDocSelRefObj tables and methods  //////////////////
///////////////////////////////////////////////////////////////////////
CDocSelRefObj* CDocSelRefObj::DefVal = new CDocSelRefObj;
CObjectProperty CDocSelRefObj::Props[] = {
	{"ID",               0, CObjectProperty::t_int, VAR_OFFSET(DefVal, ID)},
	{"�������������",    1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",      2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",          3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"����� ������ ��������",  4, CObjectProperty::t_prop, VAR_OFFSET(DefVal, SelectEmpty)},
	{"���",              5, CObjectProperty::t_prop, VAR_OFFSET(DefVal, Type.TypeLetter)},
	{"���������� ���",   6, CObjectProperty::t_prop, VAR_OFFSET(DefVal, Type.TypeObjectID)},
	{"Refers",           7, CObjectProperty::t_object, VAR_OFFSET(DefVal, Refers)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CDocSelRefObj::PropSet(Props, DefVal);

CDocSelRefObj::CDocSelRefObj()
{
	SelectEmpty = false;
	ToDestroyChildren = false;
}

CMMSObject* CDocSelRefObj::CreateChild(const char* Name, const char* Value)
{
	if( _stricoll(Name, Refers.BeautyName()) == 0 )
		return &Refers;
	return NULL;
}

CMMSObject* CDocSelRefObj::CreateChild(const char* Name, int MMS_Index)
{
	if( MMS_Index == 7 )
		return &Refers;
	return NULL;
}

///////////////////////////////////////////////////////////////////////
///////////  class CDocNumDef tables and methods  /////////////////////
///////////////////////////////////////////////////////////////////////
CDocNumDef* CDocNumDef::DefVal = new CDocNumDef;
CObjectProperty CDocNumDef::Props[] = {
	{"ID",            0, CObjectProperty::t_int, VAR_OFFSET(DefVal, ID)},
	{"�������������", 1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",   2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",       3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"����� ������",  4, CObjectProperty::t_int, VAR_OFFSET(DefVal, Length)},
	{"�������������", 5, CObjectProperty::t_prop, VAR_OFFSET(DefVal, Period)},
	{"��� ������",    6, CObjectProperty::t_prop, VAR_OFFSET(DefVal, Type)},
	{"�������������", 7, CObjectProperty::t_prop, VAR_OFFSET(DefVal, AutoNumeration)},
	{"�������� ������������", 8, CObjectProperty::t_prop, VAR_OFFSET(DefVal, Unique)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CDocNumDef::PropSet(Props, DefVal);

static CStoredSet::TSetPair DocNumDef_Period[] = {
	{0, "�� ���� ������� ����"},
	{1, "� �������� ����"},
	{2, "� �������� ��������"},
	{3, "� �������� ������"},
	{4, "� �������� ���"},
	{0, NULL}
};
static CStoredSet::TSetPair DocNumDef_Type[] = {
	{1, "���������"},
	{2, "��������"},
	{0, NULL}
};
static CStoredSet::TSetPair DocNumDef_AutoNumeration[] = {
	{1, "���"},
	{2, "��"},
	{0, NULL}
};

CDocNumDef::CDocNumDef()
{
	Length = 5;
	Period = 0;
	Type = 2;
	Unique = false;

	Period.SetTable(DocNumDef_Period);
	Type.SetTable(DocNumDef_Type);
	AutoNumeration.SetTable(DocNumDef_AutoNumeration);
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSDocuments methods  /////////////////////////////
///////////////////////////////////////////////////////////////////////
//======== CDocHeadField ====================================================
CDocHeadField* CDocHeadField::DefVal = new CDocHeadField;
CObjectProperty CDocHeadField::Props[] = {
	{"ID",                0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",     1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",       2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",           3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"���",               4, CObjectProperty::t_subobject,    VAR_OFFSET(DefVal, Type)},
	{"���������������",   8, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, NonNegative)},
	{"��������� ������",  9, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, DivideTriades)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CDocHeadField::PropSet(Props, DefVal);

CDocHeadField::CDocHeadField()
{
	NonNegative   = false;
	DivideTriades = false;
}
//======== CDocTableField ====================================================
CDocTableField* CDocTableField::DefVal = new CDocTableField;
CObjectProperty CDocTableField::Props[] = {
	{"ID",                0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",     1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",       2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",           3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"���",               4, CObjectProperty::t_subobject, VAR_OFFSET(DefVal, Type)},
	{"���������������",   8, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, NonNegative)},
	{"��������� ������",  9, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, DivideTriades)},
	{"���� �� �������",  10, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, ColumnSum)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CDocTableField::PropSet(Props, DefVal);

CDocTableField::CDocTableField()
{
	NonNegative   = false;
	DivideTriades = false;
	ColumnSum     = false;
}


//======== CMMSDocument ====================================================
CMMSDocument* CMMSDocument::DefVal = new CMMSDocument;
CObjectProperty CMMSDocument::Props[] = {
	{"ID",                      0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",           1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",             2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",                 3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"����� ������",            4, CObjectProperty::t_int,    VAR_OFFSET(DefVal, NumberLength)},
	{"�������������",           5, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, NumberPeriod)},
	{"��� ������",              6, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, NumberType)},
	{"�������������� ���������", 7, CObjectProperty::t_prop,  VAR_OFFSET(DefVal, AutoNumeration)},
	{"������ ����������",       8, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, Journal)},
	{"Param10",                 9, CObjectProperty::t_int,    VAR_OFFSET(DefVal, Param10)},
	{"�������� ������������ �������", 10, CObjectProperty::t_prop, VAR_OFFSET(DefVal, UniqueNumbers)},
	{"���������",              11, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, Numerator)},
	{"����������� ����",       12, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, Trade)},
	{"������",                 13, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, Salary)},
	{"������������� ����",     14, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, Account)},
	{"��������� ��������",     17, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, CreateOperation)},
	{"������������� �����",    18, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, AutoNumberLines)},
	{"������������ ��������",  19, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, AutoDelActions)},
	{"������������� ��������", 20, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, EditOperation)},
	{"��������� ����������",   21, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, EnableActions)},
	{"��������� ��� ������",   16, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, BaseForAny)},
	{"���� �� ���������",      15, CObjectProperty::t_object, VAR_OFFSET(DefVal, BaseParams)},
	{"�������� �����",         22, CObjectProperty::t_object,   VAR_OFFSET(DefVal, HeadFields)},
	{"�������� ��������� �����", 23, CObjectProperty::t_object,   VAR_OFFSET(DefVal, TableFields)},
	{"������� ��������",       24, CObjectProperty::t_object,   VAR_OFFSET(DefVal, MigrationRules)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CMMSDocument::PropSet(Props, DefVal);


static CStoredSet::TSetPair Document_CreateOperation[] = {
	{0, "������"},
	{1, "���������"},
	{2, "������ ��� ����������"},
	{0, NULL}
};

CMMSDocument::CMMSDocument()
{
	MMS_Type = MMS_Document;
	ID_Type = IDT_BothIDs;
	
	NumberLength = 5;
	NumberPeriod = 0;
	NumberType = 2;
	AutoNumeration = 2;
	UniqueNumbers = false;
	Param10 = -1;

	NumberPeriod.SetTable(DocNumDef_Period);
	NumberType.SetTable(DocNumDef_Type);
	AutoNumeration.SetTable(DocNumDef_AutoNumeration);
	CreateOperation.SetTable(Document_CreateOperation);

	ToDestroyChildren = false;
}

CMMSObject* CMMSDocument::CreateChild(const char* Name, const char* Value)
{
	if( _stricoll(Name, BaseParams.BeautyName()) == 0 )
		return &BaseParams;
	if( _stricoll(Name, HeadFields.BeautyName()) == 0 )
		return &HeadFields;
	if( _stricoll(Name, TableFields.BeautyName()) == 0 )
		return &TableFields;
	if( _stricoll(Name, MigrationRules.BeautyName()) == 0 )
		return &MigrationRules;
	return NULL;
}

CMMSObject* CMMSDocument::CreateChild(const char* Name, int MMS_Index)
{
	switch( MMS_Index )
	{
	case 15:
		return &BaseParams;
	case 22:
		return &HeadFields;
	case 23:
		return &TableFields;
	case 24:
		return &MigrationRules;
	}
	return NULL;
}

CMMSDocuments::CMMSDocuments()
{
	MMS_Type = MMS_Documents;
	ID_Type = CMMSObject::IDT_OnlyTextual;
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSDocument methods  //////////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSDocument::Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage)
{
	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		CStorage TransactStorage(TypedTextStorage);
		
		Msg(2, "�������� %s", sID);
		// �������� ����� ���������
		GCString DocDir = GetObjectDir(Dir);	
		CreateDirectory(DocDir);

		//�������� ���, ����� ������ ����������
		if( Storage.Open(nt_rec->PrepareStorageName(ID)) ) //�������� ����� � �� ����, ���� � ��������� ��� �����
		{
			ExtractWorkBook(DocDir, Storage, this);
			Storage.Close();
		}

		//������ ����������
		nt_rec = NameTable.Find(NT_TransactModule);
		MMS_Filter.Down();
		if( MMS_Filter.Test(NULL, nt_rec) )
		{
			CNameTableRecord* nt_rec_stor = NameTable.Find(NT_TransModuleStor);
			if( TransactStorage.Open(nt_rec_stor->PrepareStorageName(ID)) )
			{
				TransactStorage.CopyToFile((GCString)(nt_rec->StorageName), (GCString)(nt_rec->PrepareFileName(DocDir)));
			}
		}
		MMS_Filter.Up();

		ExtractMetadata(DocDir, TypedTextStorage);
		ExtractDescriptions(DocDir+"\\", TypedTextStorage, true);

		SendInfoMessage(InfoMsg_Progress, ++TotalObjectsProcessed);
	}
	MMS_Filter.Up();
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSDocuments methods  /////////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSDocuments::Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage)
{
	int nChildren = GetNChildren();
	if( nChildren == 0 ) return;

	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		GCString DocsDir = nt_rec->PrepareDirName(Dir);

		CreateDirectory(DocsDir);

		CStorage DocStorage(Storage);
		DocStorage.Open(nt_rec->PrepareStorageName(ID));
		for( int i = 0; i < nChildren; i++ )
		{
			CMMSDocument* pDoc = (CMMSDocument*)GetChild(i);
			pDoc->Decompile(DocsDir, DocStorage, TypedTextStorage);
		}

		ExtractOrdering(Storage, DocsDir);
	}
	MMS_Filter.Up();
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSDocument methods  //////////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSDocument::Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir)
{
	CNameTableRecord* nt_rec_stor = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec_stor) )
	{
		Msg(1, "INF: ��������.%s", sID);
		CStorage TransactStorage(TypedTextStorage);

		GCString DocDir = GetObjectDir(SrcDir);
		Storage.Create(nt_rec_stor->PrepareStorageName(ID));
		bool NotEmpty = ImportWorkBook(Storage, DocDir);
		Storage.Close();
		if( !NotEmpty )
			Storage.Delete(nt_rec_stor->PrepareStorageName(ID));

		//������ ����������
		CNameTableRecord* nt_rec_file = NameTable.Find(NT_TransactModule);
		MMS_Filter.Down();
		if( MMS_Filter.Test(NULL, nt_rec_file) )
		{
			nt_rec_stor = NameTable.Find(NT_TransModuleStor);
			GCString FileName = nt_rec_file->PrepareFileName(DocDir);
			if( FileExist(FileName) )
			{
				TransactStorage.Create(nt_rec_stor->PrepareStorageName(ID));
				ImportStreamByType(TransactStorage, NT_TransactModule, DocDir);
				CContainer CC;
				CC.CreateInTypedText(TransactStorage);
			}
		}
		MMS_Filter.Up();

		//��������
		ImportDescriptions(TypedTextStorage, DocDir+"\\", true);
	}
	MMS_Filter.Up();

	SendInfoMessage(InfoMsg_Progress, ++TotalObjectsProcessed);
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSDocuments methods  /////////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSDocuments::Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir)
{
	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);
	GCString DocsDir = nt_rec->PrepareDirName(SrcDir);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		ImportOrdering(DocsDir);

		Storage.Create(nt_rec->PrepareStorageName(ID));
		for( int i = 0; i < GetNChildren(); i++ )
		{
			GetChild(i)->Compile(Storage, TypedTextStorage, DocsDir);
		}
		Storage.Close();
	}
	MMS_Filter.Up();
}


///////////////////////////////////////////////////////////////////////
///////////  class CMMSDocStream methods  /////////////////////////////
///////////////////////////////////////////////////////////////////////
CMMSDocStream* CMMSDocStream::DefVal = new CMMSDocStream;
CObjectProperty CMMSDocStream::Props[] = {
	{"ID",                 0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",      1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",        2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",            3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"Param5",             4, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param5)},
	{"��������� ��� ����", 5, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, Migration)},
	{"��������",           6, CObjectProperty::t_object, VAR_OFFSET(DefVal, Registers)},
	{"���������",          7, CObjectProperty::t_object, VAR_OFFSET(DefVal, Documents)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CMMSDocStream::PropSet(Props, DefVal);


static CStoredSet::TSetPair DocStream_Migration[] = {
	{0, "������ ������������������ � ����������� ��"},
	{1, "��������� ������������������ � ����� ��"},
	{0, NULL}
};

CMMSDocStream::CMMSDocStream()
{
	MMS_Type = MMS_DocumentStream;
	ToDestroyChildren = false;

	Migration.SetTable(DocStream_Migration);
}

CMMSObject* CMMSDocStream::CreateChild(const char* Name, const char* Value)
{
	if( _stricoll(Name, Registers.BeautyName()) == 0 )
		return &Registers;
	if( _stricoll(Name, Documents.BeautyName()) == 0 )
		return &Documents;
	return NULL;
}
CMMSObject* CMMSDocStream::CreateChild(const char* Name, int MMS_Index)
{
	switch( MMS_Index )
	{
	case 6:
		return &Registers;
	case 7:
		return &Documents;
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSJournal methods  ///////////////////////////////
///////////////////////////////////////////////////////////////////////
CJournalFld* CJournalFld::DefVal = new CJournalFld;
CObjectProperty CJournalFld::Props[] = {
	{"ID",               0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",    1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",      2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",          3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"���� ����������",  4, CObjectProperty::t_object, VAR_OFFSET(DefVal, DocumentFields)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CJournalFld::PropSet(Props, DefVal);

//--------------------
CMMSJournal* CMMSJournal::DefVal = new CMMSJournal;
CObjectProperty CMMSJournal::Props[] = {
	{"ID",                0, CObjectProperty::t_int,    VAR_OFFSET(DefVal, ID)},
	{"�������������",     1, CObjectProperty::t_string, VAR_OFFSET(DefVal, sID)},
	{"�����������",       2, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Comment)},
	{"�������",           3, CObjectProperty::t_quotstring, VAR_OFFSET(DefVal, Synonym)},
	{"Param5",            4, CObjectProperty::t_string, VAR_OFFSET(DefVal, Param5)},
	{"������ �����",      5, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, IsCommon)},
	{"����� ������",      6, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, SelectionForm)},
	{"�������� �����",    7, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, MainForm)},
	{"�� ��������������", 8, CObjectProperty::t_prop,   VAR_OFFSET(DefVal, NonAditional)},
	{"������ �������",    9, CObjectProperty::t_object, VAR_OFFSET(DefVal, Documents)},
	{"����� �������",    10, CObjectProperty::t_object, VAR_OFFSET(DefVal, Fields)},
	{"����� �������",    11, CObjectProperty::t_object, VAR_OFFSET(DefVal, Forms)},
	{NULL, -1, CObjectProperty::t_int}
};
CPropertySet CMMSJournal::PropSet(Props, DefVal);

CMMSJournal::CMMSJournal()
{
	MMS_Type = MMS_Journalister;
	ToDestroyChildren = false;
}

CMMSObject* CMMSJournal::CreateChild(const char* Name, const char* Value)
{
	if( _stricoll(Name, Documents.BeautyName()) == 0 )
		return &Documents;
	if( _stricoll(Name, Fields.BeautyName()) == 0 )
		return &Fields;
	if( _stricoll(Name, Forms.BeautyName()) == 0 )
		return &Forms;
	return NULL;
}

CMMSObject* CMMSJournal::CreateChild(const char* Name, int MMS_Index)
{
	switch( MMS_Index )
	{
	case 9:
		return &Documents;
	case 10:
		return &Fields;
	case 11:
		return &Forms;
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSJournalister methods  //////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSJournal::Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage)
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

	SendInfoMessage(InfoMsg_Progress, ++TotalObjectsProcessed);
}


///////////////////////////////////////////////////////////////////////
///////////  class CMMSJournalisters methods  /////////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSJournalList::Decompile(GCString& SrcDir, CStorage& Storage, CStorage& TypedTextStorage)
{
	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		GCString JournalsDir = nt_rec->PrepareDirName(SrcDir);

		CreateDirectory(JournalsDir);

		CStorage JrStorage(Storage);
		JrStorage.Open(nt_rec->StorageName);
		int nChildren = GetNChildren();
		for( int i = 0; i < nChildren; i++ )
		{
			GetChild(i)->Decompile(JournalsDir, JrStorage, TypedTextStorage);
		}

		ExtractOrdering(Storage, JournalsDir);
	}
	MMS_Filter.Up();
}

///////////////////////////////////////////////////////////////////////
///////////  class CMMSJournalister methods  //////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSJournal::Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir)
{
	CNameTableRecord* nt_rec = NameTable.Find(MMS_Type);

	MMS_Filter.Down();
	if( MMS_Filter.Test(this, nt_rec) )
	{
		Msg(1, "INF: ����������������.%s", sID);
		GCString JournalDir = GetObjectDir(SrcDir);
		ImportDescriptions(TypedTextStorage, JournalDir+"\\", true);
		ImportListForms(Forms, Storage, JournalDir, nt_rec->StorageName);
	}
	MMS_Filter.Up();

	SendInfoMessage(InfoMsg_Progress, ++TotalObjectsProcessed);
}


///////////////////////////////////////////////////////////////////////
///////////  class CMMSJournalisters methods  /////////////////////////////
///////////////////////////////////////////////////////////////////////
void CMMSJournalList::Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir)
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

