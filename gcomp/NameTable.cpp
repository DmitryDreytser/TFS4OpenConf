
#include "NameTable.h"
#include "CommonFunctions.h"
#include "MMS.h"


void CNameTable::RusConstructor()
{
	nRecords = 0;
	NameTable.SetSize(100);

	AddRecord(MMS_MainDataContDef, NULL,                     "MainDataContDef",  NULL, false, NULL, "��������������������������", "mdp");
	AddRecord(MMS_TaskItem,        NULL,                     "TaskItem",         NULL, false, NULL, "��������������������", "mdp");
	AddRecord(MMS_TaskItemContent, "������",                 NULL,               NULL, false, NULL, "��������������������", "mdp");
	AddRecord(MMS_GenJrnlFldDef,   "����������������������", "GenJrnlFldDef",    NULL, false, "�������������������", "�������������������", "mdp");
	AddRecord(MMS_DocSelRefObj,    "�����������",            "DocSelRefObj",     NULL, false, "���������������������", "���������������������", "mdp");
	AddRecord(MMS_DocNumDef,       "���������",              "DocNumDef",        NULL, false, "����������", "����������", "mdp");
	AddRecord(MMS_Consts,          "���������",              "Consts",           NULL, false, "���������", "���������", "mdp");
	AddRecord(MMS_Registers,       "�������",                "Registers",        NULL, false, "��������", "��������", "mdp");
	AddRecord(MMS_EnumList,        "������������",           "EnumList",         NULL, false, "������������", "������������", "mdp");
	AddRecord(MMS_Calendars,       "���������",              "Calendars",        NULL, false, "���������", "���������", "mdp");
	AddRecord(MMS_RecalcRules,     "������������������",     "RecalcRules",      NULL, false, "������������������", "������������������", "mdp");
	AddRecord(MMS_Groups,          "��������������",         "Groups",           NULL, false, "��������������", "��������������", "mdp");
	AddRecord(MMS_DocumentStreams, "������������������",     "Document Streams", NULL, false, "����������������������������", "����������������������������", "mdp");
	AddRecord(MMS_Buh,             "�����������",            NULL,               NULL, false, "��������������������", "����������", "mdp");
	
	AddRecord(MMS_AccParams,       "�������������",          "AccParams",        NULL, false, "�����",    "��������������", "mdp");
	AddRecord(MMS_Plans,           "����������",             "Plans",            NULL, false, "�����",    NULL, NULL);
	AddRecord(MMS_Plan,            "sID",                     "Plan",            NULL, false, "%sID%",    NULL, "pln");
	AddRecord(MMS_Account,         "sID",                     NULL,              NULL, false, NULL,       "%Code%", "acc");
	AddRecord(MMS_ProvParams,      "��������",               "ProvParams",       NULL, false, "��������", "�����������������", "mdp");
	AddRecord(MMS_OperParams,      "��������",               "OperParams",       NULL, false, "��������", "�����������������", "mdp");
	AddRecord(MMS_SbKind,          "�����������",            "SbKind",           NULL, false, "�����",    "������������", "mdp");
	AddRecord(MMS_TypOpersDef,     "���������������",        "TypOpersDef",      NULL, false, "��������", "TypOpersDef", "mdp");
	AddRecord(MMS_CorrProvsDef,    "������������������",     "CorrProvsDef",     NULL, false, "��������", "CorrProvsDef", "mdp");
	AddRecord(MMS_ProvHardFldDef,  NULL,                     "ProvHardFldDef",   NULL, false, "��������", "�������������������", "mdp");
	AddRecord(MMS_OperJournal,     "��������",               "OperJournal",      "OperationList", false, "��������������", "��������������", "mdp");

	AddRecord(MMS_SbCnts,          "����������",             "SbCnts",           "Subconto", false, "�����������");
	AddRecord(MMS_Documents,       "��������",               "Documents",        "Document", false, "���������");
	AddRecord(MMS_Journalisters,   "������",                 "Journalisters",    "Journal", false, "�����������������");
	AddRecord(MMS_ReportList,      "�����",                  "ReportList",       "Report", false, "������");
	AddRecord(MMS_CalcJournals,    "��������������",         "CJ",               "CalcJournal", false, "���������������");
	AddRecord(MMS_CalcAlgorithms,  "����������",             "Algorithms",       "TypedText", false, "����������������");
	AddRecord(MMS_CalcVars,        "���������",              "CalcVars",         "CalcVar", false, "���������");

	AddRecord(MMS_TaskItemDescr,   "��������", NULL,        NULL,               false, NULL);
	AddRecord(MMS_Enum,            "sID", NULL,             NULL,               false, NULL);
	AddRecord(MMS_EnumVal,         NULL, "EnumVal",         NULL,               false, NULL);
	AddRecord(MMS_Const,           "sID", NULL,             NULL,               false, "%sID%", NULL, "mdp");
	AddRecord(MMS_SbCnt,           "sID", NULL,             "Subconto_Number",  true,  "%sID%");
	AddRecord(MMS_SbCntParams,     NULL, "Params",          NULL,               false, NULL, "����������", "mdp");
	AddRecord(MMS_Document,        "sID", NULL,             "Document_Number",  true,  NULL);
	AddRecord(MMS_Report,          "sID", NULL,             "Report_Number",    true,  NULL);
	AddRecord(MMS_DocHeadFields,   NULL, "Head Fields",     NULL,               false, NULL);
	AddRecord(MMS_DocTableFields,  NULL, "Table Fields",    NULL,               false, NULL);
	AddRecord(MMS_Register,        "sID", NULL,             NULL,               false, NULL);
	AddRecord(MMS_RegisterProps,   NULL, "Props",           NULL,               false, NULL);
	AddRecord(MMS_RegisterFigures, NULL, "Figures",         NULL,               false, NULL);
	AddRecord(MMS_RegisterFlds,    NULL, "Flds",            NULL,               false, NULL);
	AddRecord(MMS_Journalister,    "sID", NULL,             "Journal_Number",   false, NULL);
	AddRecord(MMS_JournalFlds,     NULL, "JournalFld",       NULL,               false, NULL);
	AddRecord(MMS_CalcJournal,     "sID", NULL,             "CalcJournal_Number", false, NULL);
	AddRecord(MMS_CJParams,        NULL, "CJParams",        NULL,               false, NULL);
	AddRecord(MMS_CalcAlgorithm,   "sID", NULL,             "CalcAlg_Number",   true,  NULL);
	
	AddRecord(MMS_DistributionRuler, NULL, "Distribution ruler", NULL,  false,  NULL);

	AddRecord(NT_ObjNameTable,     NULL, NULL,   NULL,                  false, NULL, "�����������������", "txt");
	AddRecord(NT_MainMetadataStream, NULL, NULL, "Main MetaData Stream", false, NULL, "���������", "mdp");
	AddRecord(NT_MetadataPart,     NULL, NULL,   NULL,                  false, NULL, "���������", "mdp");
	AddRecord(NT_Workbook,         NULL, NULL,   "WorkBook",            false, NULL);
	AddRecord(NT_FormModule,       NULL, NULL,   "MD Programm text",    false, NULL, "�����������", "1s");
	AddRecord(NT_DialogForm,       NULL, NULL,   "Dialog Stream",       false, NULL, "�����", "frm");
	AddRecord(NT_MoxelSheet,       NULL, NULL,   "Page",                false, NULL, "%sID%", "mxl");
	AddRecord(NT_ListForm,         "�����", NULL, NULL,                 false, "%sID%", NULL, "fls");
	AddRecord(NT_GlobalModuleStor, NULL, NULL,   "ModuleText_Number1",  false, NULL);
	AddRecord(NT_GlobalModule,     NULL, NULL,   "ModuleText_Number1\\MD Programm text", false, NULL, "����������������", "1s");
	AddRecord(NT_TransModuleStor,  NULL, NULL,   "Transact_Number",     true,  NULL);
	AddRecord(NT_TransactModule,   NULL, NULL,   "MD Programm text",    false, NULL, "����������������", "1s");
	AddRecord(NT_UserHelpStor,     NULL, NULL,   "UserHelp_Number",     true,  NULL); //"��������");
	AddRecord(NT_UserHelp,         "��������", NULL,   "MD Programm text",    false, NULL, "��������", "txt");
	AddRecord(NT_ErtUserHelp,      "��������", NULL,   "Inplace description", false, NULL, "��������", "txt");
	AddRecord(NT_SubcontoFolder,   NULL, NULL,   "SubFolder_Number",    true,  "�����������");
	AddRecord(NT_SubcontoListForm, "�����������", NULL,   "SubList_Number",      true, "%sID%", NULL, "fls");
	AddRecord(NT_CalcAlgorithm,    "������", NULL,   "MD Programm text",    false, NULL, "�������������", "1s");
	AddRecord(NT_AccFormStor,      NULL, NULL,   "AccountChart",        false, "�����");
	AddRecord(NT_AccForm,          NULL, NULL,   "AccountChart_Number", true,  "����������");
	AddRecord(NT_OperFormStor,     NULL, NULL,   "Operation",           false, "��������");
	AddRecord(NT_OperForm,         NULL, NULL,   "Operation_Number",    true,  "�������������");
	AddRecord(NT_AccListForm,      "����������.�����������", NULL, "AccountChartList", false, "�����", "�����������", "mdp");
	AddRecord(NT_OperListForm,     "�����������", NULL, "OperationList", false, "��������", "������������", "mdp");
	AddRecord(NT_ProvListForm,     "��������.�����������", NULL, "ProvList", false, "��������", "������������", "mdp");
	AddRecord(NT_UnknownListForm,  NULL, NULL,   NULL,                  false,  NULL, "����������������", "mdp");
	AddRecord(NT_GlobalData,       NULL, NULL,   "GlobalData",          false,  NULL);
	AddRecord(NT_CommonMXL,        NULL, NULL,   "GlobalData_Number1",  false,  "������������");
	AddRecord(NT_PictureGallery,   NULL, NULL,   "Picture",             false,  "PictureGallery");
	AddRecord(NT_GUIDData,         NULL, NULL,   "Metadata\\GUIDData",  false,  NULL, "GUIDData");
	AddRecord(NT_TagStream,        NULL, NULL,   "Metadata\\TagStream", false,  NULL, "TagStream");
	AddRecord(NT_UserInterface,    NULL, NULL,   "UserDef\\Page.1",     false,  "����������");
	AddRecord(NT_UserRights,       NULL, NULL,   "UserDef\\Page.2",     false,  "�����", "%sID%", "txt");
	AddRecord(NT_UserRightsOneFile,NULL, NULL,   "UserDef\\Page.2",     false,  "�����", "����������������������", "csv");
	AddRecord(NT_ObjectOrdering,   NULL, NULL,   NULL,                  false,  NULL, "���������������", "ord");

	AddRecord(NT_UICommands,       NULL, NULL,   "Commands",            false,  NULL, "�������", "txt");
	AddRecord(NT_UIMenu,           NULL, NULL,   "Page.1",              false,  NULL, "����", "txt");
	AddRecord(NT_UIPanels,         NULL, NULL,   "Page.2",              false,  NULL, "������", "txt");
	AddRecord(NT_UIPanelsBMP,      NULL, NULL,   "Page.2",              false,  NULL, "������", "bmp");
}


void CNameTable::EngConstructor()
{
	nRecords = 0;
	NameTable.SetSize(100);

	AddRecord(MMS_MainDataContDef, NULL,                     "MainDataContDef",  NULL, false, NULL, "ConfigIdentifiers", "mdp");
	AddRecord(MMS_TaskItem,        "������",                 "TaskItem",         NULL, false, NULL, "ConfigDescription", "mdp");
	AddRecord(MMS_TaskItemContent, "������",                 NULL,               NULL, false, NULL, "ConfigDescription", "mdp");
	AddRecord(MMS_GenJrnlFldDef,   "����������������������", "GenJrnlFldDef",    NULL, false, "CommonFiledsOfDocs", "CommonFiledsOfDocs", "mdp");
	AddRecord(MMS_DocSelRefObj,    "�����������",            "DocSelRefObj",     NULL, false, "DocumentSelectionRules", "DocumentSelectionRules", "mdp");
	AddRecord(MMS_DocNumDef,       "���������",              "DocNumDef",        NULL, false, "Numerators", "Numerators", "mdp");
	AddRecord(MMS_Consts,          "���������",              "Consts",           NULL, false, "Constants", "Constants", "mdp");
	AddRecord(MMS_Registers,       "�������",                "Registers",        NULL, false, "Registers", "Registers", "mdp");
	AddRecord(MMS_EnumList,        "������������",           "EnumList",         NULL, false, "Enumerations", "Enumerations", "mdp");
	AddRecord(MMS_Calendars,       "���������",              "Calendars",        NULL, false, "Calendars", "Calendars", "mdp");
	AddRecord(MMS_RecalcRules,     "������������������",     "RecalcRules",      NULL, false, "RecalcRules", "RecalcRules", "mdp");
	AddRecord(MMS_Groups,          "��������������",         "Groups",           NULL, false, "RecalcGroups", "RecalcGroups", "mdp");
	AddRecord(MMS_DocumentStreams, "������������������",     "Document Streams", NULL, false, "DocumentStreams", "DocumentStreams", "mdp");
	AddRecord(MMS_Buh,             "�����������",            NULL,               NULL, false, "AccountSettings", "Metadata", "mdp");

	AddRecord(MMS_AccParams,       "�������������",          "AccParams",        NULL, false, "Accounts",    "AccParams", "mdp");
	AddRecord(MMS_Plans,           "����������",             "Plans",            NULL, false, "Accounts",    NULL, NULL);
	AddRecord(MMS_Plan,            "sID",                    "Plan",             NULL, false, "%sID%",    NULL, "pln");
	AddRecord(MMS_Account,         "sID",                    NULL,               NULL, false, NULL,       "%Code%", "acc");
	AddRecord(MMS_ProvParams,      "��������",               "ProvParams",       NULL, false, "Entry", "ProvParams", "mdp");
	AddRecord(MMS_OperParams,      "��������",               "OperParams",       NULL, false, "Operation", "OperParams", "mdp");
	AddRecord(MMS_SbKind,          "�����������",            "SbKind",           NULL, false, "Accounts",    "SbKind", "mdp");
	AddRecord(MMS_TypOpersDef,     "���������������",        "TypOpersDef",      NULL, false, "Operation", "TypOpersDef", "mdp");
	AddRecord(MMS_CorrProvsDef,    "������������������",     "CorrProvsDef",     NULL, false, "Entry", "CorrProvsDef", "mdp");
	AddRecord(MMS_ProvHardFldDef,  NULL,                     "ProvHardFldDef",   NULL, false, "Entry", "ProvHardFldDef", "mdp");
	AddRecord(MMS_OperJournal,     "��������",               "OperJournal",      "OperationList", false, "OperationJournal", "OperationJournal", "mdp");

	AddRecord(MMS_SbCnts,          "����������",             "SbCnts",           "Subconto", false, "References");
	AddRecord(MMS_Documents,       "��������",               "Documents",        "Document", false, "Documents");
	AddRecord(MMS_Journalisters,   "������",                 "Journalisters",    "Journal", false, "DocumentJournals");
	AddRecord(MMS_ReportList,      "�����",                  "ReportList",       "Report", false, "Reports");
	AddRecord(MMS_CalcJournals,    "��������������",         "CJ",               "CalcJournal", false, "CalcJournals");
	AddRecord(MMS_CalcAlgorithms,  "����������",             "Algorithms",       "TypedText", false, "CalcAlgorithms");
	AddRecord(MMS_CalcVars,        "���������",              "CalcVars",         "CalcVar", false, "DataProcessing");

	AddRecord(MMS_TaskItemDescr,   "��������", NULL,        NULL,               false, NULL);
	AddRecord(MMS_Enum,            "sID", NULL,             NULL,               false, NULL);
	AddRecord(MMS_EnumVal,         NULL, "EnumVal",         NULL,               false, NULL);
	AddRecord(MMS_Const,           "sID", NULL,             NULL,               false, "%sID%", NULL, "mdp");
	AddRecord(MMS_SbCnt,           "sID", NULL,             "Subconto_Number",  true,  "%sID%");
	AddRecord(MMS_SbCntParams,     NULL, "Params",          NULL,               false, NULL, "Structure", "mdp");
	AddRecord(MMS_Document,        "sID", NULL,             "Document_Number",  true,  NULL);
	AddRecord(MMS_Report,          "sID", NULL,             "Report_Number",    true,  NULL);
	AddRecord(MMS_DocHeadFields,   NULL, "Head Fields",     NULL,               false, NULL);
	AddRecord(MMS_DocTableFields,  NULL, "Table Fields",    NULL,               false, NULL);
	AddRecord(MMS_Register,        "sID", NULL,             NULL,               false, NULL);
	AddRecord(MMS_RegisterProps,   NULL, "Props",           NULL,               false, NULL);
	AddRecord(MMS_RegisterFigures, NULL, "Figures",         NULL,               false, NULL);
	AddRecord(MMS_RegisterFlds,    NULL, "Flds",            NULL,               false, NULL);
	AddRecord(MMS_Journalister,    "sID", NULL,             "Journal_Number",   false, NULL);
	AddRecord(MMS_JournalFlds,     NULL, "JournalFld",       NULL,               false, NULL);
	AddRecord(MMS_CalcJournal,     "sID", NULL,             "CalcJournal_Number", false, NULL);
	AddRecord(MMS_CJParams,        NULL, "CJParams",        NULL,               false, NULL);
	AddRecord(MMS_CalcAlgorithm,   "sID", NULL,             "CalcAlg_Number",   true,  NULL);

	AddRecord(MMS_DistributionRuler, NULL, "Distribution ruler", NULL,  false,  NULL);

	AddRecord(NT_ObjNameTable,     NULL, NULL,   NULL,                  false, NULL, "MetaObjects", "txt");
	AddRecord(NT_MainMetadataStream, NULL, NULL, "Main MetaData Stream", false, NULL, "Structure", "mdp");
	AddRecord(NT_MetadataPart,     NULL, NULL,   NULL,                  false, NULL, "Structure", "mdp");
	AddRecord(NT_Workbook,         NULL, NULL,   "WorkBook",            false, NULL);
	AddRecord(NT_FormModule,       NULL, NULL,   "MD Programm text",    false, NULL, "FormModule", "1s");
	AddRecord(NT_DialogForm,       NULL, NULL,   "Dialog Stream",       false, NULL, "Form", "frm");
	AddRecord(NT_MoxelSheet,       NULL, NULL,   "Page",                false, NULL, "%sID%", "mxl");
	AddRecord(NT_ListForm,         "�����", NULL, NULL,                 false, "%sID%", NULL, "fls");
	AddRecord(NT_GlobalModuleStor, NULL, NULL,   "ModuleText_Number1",  false, NULL);
	AddRecord(NT_GlobalModule,     NULL, NULL,   "ModuleText_Number1\\MD Programm text", false, NULL, "GlobalModule", "1s");
	AddRecord(NT_TransModuleStor,  NULL, NULL,   "Transact_Number",     true,  NULL);
	AddRecord(NT_TransactModule,   NULL, NULL,   "MD Programm text",    false, NULL, "TransactionModule", "1s");
	AddRecord(NT_UserHelpStor,     NULL, NULL,   "UserHelp_Number",     true,  NULL); //"��������");
	AddRecord(NT_UserHelp,         "��������", NULL, "MD Programm text", false, NULL, "Description", "txt");
	AddRecord(NT_ErtUserHelp,      "��������", NULL, "Inplace description", false, NULL, "Description", "txt");
	AddRecord(NT_SubcontoFolder,   NULL, NULL,   "SubFolder_Number",    true,  "GroupForm");
	AddRecord(NT_SubcontoListForm, "�����������", NULL,   "SubList_Number",      true, "%sID%", NULL, "fls");
	AddRecord(NT_CalcAlgorithm,    "������", NULL, "MD Programm text",  false, NULL, "CalcModule", "1s");
	AddRecord(NT_AccFormStor,      NULL, NULL,   "AccountChart",        false, "Accounts");
	AddRecord(NT_AccForm,          NULL, NULL,   "AccountChart_Number", true,  "AccountForm");
	AddRecord(NT_OperFormStor,     NULL, NULL,   "Operation",           false, "Operation");
	AddRecord(NT_OperForm,         NULL, NULL,   "Operation_Number",    true,  "OperationForm");
	AddRecord(NT_AccListForm,      "����������.�����������", NULL, "AccountChartList", false,  "Accounts", "ListForms", "mdp");
	AddRecord(NT_OperListForm,     "�����������", NULL, "OperationList", false, "Operation", "JournalForms", "mdp");
	AddRecord(NT_ProvListForm,     "��������.�����������", NULL, "ProvList", false, "Entry", "JournalForms", "mdp");
	AddRecord(NT_UnknownListForm,  NULL, NULL,   NULL,                  false,  NULL, "UnknownForm", "mdp");
	AddRecord(NT_GlobalData,       NULL, NULL,   "GlobalData",          false,  NULL);
	AddRecord(NT_CommonMXL,        NULL, NULL,   "GlobalData_Number1",  false,  "CommonMoxel");
	AddRecord(NT_PictureGallery,   NULL, NULL,   "Picture",             false,  "PictureGallery");
	AddRecord(NT_GUIDData,         NULL, NULL,   "Metadata\\GUIDData",  false,  NULL, "GUIDData");
	AddRecord(NT_TagStream,        NULL, NULL,   "Metadata\\TagStream", false,  NULL, "TagStream");
	AddRecord(NT_UserInterface,    NULL, NULL,   "UserDef\\Page.1",     false,  "Interfaces");
	AddRecord(NT_UserRights,       NULL, NULL,   "UserDef\\Page.2",     false,  "UserRights", "%sID%", "txt");
	AddRecord(NT_UserRightsOneFile,NULL, NULL,   "UserDef\\Page.2",     false,  "UserRights", "Rights", "csv");
	AddRecord(NT_ObjectOrdering,   NULL, NULL,   NULL,                  false,  NULL, "ObjectOrder", "ord");

	AddRecord(NT_UICommands,       NULL, NULL,   "Commands",            false,  NULL, "Commands", "txt");
	AddRecord(NT_UIMenu,           NULL, NULL,   "Page.1",              false,  NULL, "Menu", "txt");
	AddRecord(NT_UIPanels,         NULL, NULL,   "Page.2",              false,  NULL, "Panels", "txt");
	AddRecord(NT_UIPanelsBMP,      NULL, NULL,   "Page.2",              false,  NULL, "Panels", "bmp");
}

CNameTable::~CNameTable()
{
	for( int i = 0; i < nRecords; i++ )
	{
		delete NameTable[i];
	}
}

void CNameTable::AddRecord(MMSObjectType Type, LPCSTR Type1C, LPCSTR sID,
						   LPCSTR StorageName, bool HasSuffix, 
						   LPCSTR Dir, LPCSTR FileName, LPCSTR Ext)
{

	GCString TranslitDir;
	if (Dir)
		TranslitDir = Dir;
	else
		TranslitDir = "";
	
	GCString TranslitFileName;
	if (FileName)
		TranslitFileName = FileName;
	else
		TranslitFileName = "";

	InplaceTranslit(TranslitDir);
	InplaceTranslit(TranslitFileName);
  
	CNameTableRecord* rec = new CNameTableRecord;
	rec->Type = Type;
	if( Type1C != NULL ) rec->Type1C = Type1C;
	if( sID != NULL ) rec->sID = sID;
	if( StorageName != NULL ) rec->StorageName = StorageName;
	rec->HasSuffix = HasSuffix;
	if( Dir != NULL ) rec->Dir = TranslitDir;
	if( FileName != NULL ) rec->FileName = TranslitFileName;
	if( Ext != NULL ) rec->Ext = Ext;

	if( nRecords >= NameTable.GetSize() )
		NameTable.Add(rec);
	else
		NameTable.SetAt(nRecords, rec);
	nRecords++;
}

CNameTableRecord* CNameTable::Find(MMSObjectType Type)
{
	for( int i = 0; i < nRecords; i++ )
		if( NameTable[i]->Type == Type ) return NameTable[i];
	return NULL;
}

CNameTableRecord* CNameTable::Find(GCString& sID)
{
	for( int i = 0; i < nRecords; i++ )
		if( NameTable[i]->sID == sID ) return NameTable[i];
	return NULL;
}

CNameTableRecord* CNameTable::FindByType1C(GCString& Type1C)
{
	for( int i = 0; i < nRecords; i++ )
		if( NameTable[i]->Type1C == Type1C ) return NameTable[i];
	return NULL;
}

////////////////////////////////////////////////////////////////////////////
//////  class CNameTableRecord  ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
GCString CNameTableRecord::PrepareFileName(GCString& BaseDir, CMMSObject* object)
{
	GCString FullFName(BaseDir);

	if( BaseDir.GetLength() > 0 ) FullFName += "\\";
	
	if( Dir.GetLength() > 0 )
	{
		FullFName += Dir;
		FullFName += "\\";
	}
	FullFName += FileName;
	if( Ext.GetLength() > 0 )
	{
		FullFName += ".";
		FullFName += Ext;
	}

	if( object != NULL )
	{
		FullFName.Replace("%sID%", Translit(object->sID));
		// ������������� �����. ���� object->sID �������� � ���-�� ���.
		// �������� ��������� � ��������������� "�����"
	}
	return FullFName;
}

GCString CNameTableRecord::PrepareDirName(GCString& BaseDir, CMMSObject* object)
{
	if( Dir.IsEmpty() && FileName.IsEmpty() && Ext.IsEmpty() ) return BaseDir;

	GCString FullDirName;
	GCString Slash;
	
	if( BaseDir.GetLength() > 0 ) Slash = "\\";

	if( (Ext.GetLength() > 0) && (FileName.GetLength() == 0) )
		FullDirName.Format("%s%s%s.%s", BaseDir, Slash, Dir, Ext);
	else
		FullDirName.Format("%s%s%s", BaseDir, Slash, Dir);

	if( object != NULL )
	{
		FullDirName.Replace("%sID%", Translit(object->sID)); 
		// ������������� �����. ���� object->sID �������� � ���-�� ���.
		// �������� �������� � ��������������� "�����"
	}

	return FullDirName;
}

GCString CNameTableRecord::PrepareStorageName(int suffix)
{
	if( HasSuffix )
	{
		GCString StorName;
		StorName.Format("%s%i", StorageName, suffix);
		return StorName;
	}
	else
		return StorageName;
}

