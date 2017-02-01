
#include "DLL\GComp.h"
#include "Rights.h"
#include "CommonFunctions.h"
#include "Strings.h"
#include "Ordering.h"
#include "Storage.h"
#include "NameTable.h"
#include "MMS_Filter.h"
#include "MMS.h"


/////////////////////////////////////////////////////////////////////
CUserRightsProp::TTypeTable CUserRightsProp::TypeTable[] = {
	{0x00, "0x00"},
	{0x01, "������"},
	{0x02, "�������������"},
	{0x03, "����� ���������"},
	{0x04, "�������������"},
	{0x05, "���� ������"},
	{0x06, "��������"},
	{0x07, "��������� ����������� ����������"},
	{0x08, "���������� ���������"},
	{0x09, "���������� ��������� ������ ������"},
	{0x0a, "���������� ������������ �������"},
	{0x0b, "���������������� �������"},
	{0x0c, "�������� ������� �������"},
	{0x0d, "�������� ������� \"������\""},
	{0x0e, "�����"},
	{0x0f, "�������� ����������� ����������"},
	{0x10, "�������"},
	{0x11, "��������� ���������� ��� ��������������"},
	{0x12, "������������� � �������� OLE Automation �������"},
	{0x13, "������"},
	{0x14, "��������� ���������� �������"},
	{0x15, "0x15"},
	{0x16, "0x16"},
	{0x17, "0x17"},
	{0x18, "0x18"},
	{0x19, "�������� ���������� ��������"},
	{0x1a, "������� �� ��������"},
	{0x1b, "������������� ����� ������� ������� � ���������"},
	{0x1c, "������ ������� �� ��������"},
	{0x1d, "������������� ������� � ����� � ���������� ������������"},
	{0x1e, "����� ������ �� �������"},
	{0x1f, "������������� ����� ������� ������� � ���������"},
	{0x20, "���� �������� ��� �������� ��������"},
	{0x21, "�������������� ������ ���������� ��������"},
	{0x22, "������������� ����� ������"},
	{0x23, "���������� �������������� �������"},
	{0x24, "�������� ������"},
	{0x25, "�������������� �������� ���������"},
	{0x26, "�������� ������ ���������� ��������"},
	{0x27, "���������� �������� ��������"},
	{0x28, "��������� �������� ��������"},
	{0x29, "��������� ���������� ����������"},
	{0x2a, "����������/�������� ������"},
	{0x2b, "����������� �����"},
	{0x2c, "��������� � �������������� ��"},
	{0x2d, "������������� ���������"},
	{0x2e, "������������� Web ����������"},
	{0x00, NULL}
};

CUserRightsProp::CUserRightsProp()
{
	Type = 0;
	Value = 0;
}

const char* CUserRightsProp::TypeAsString()
{
	TTypeTable* ptr = TypeTable;
	while( ptr->sID != NULL )
	{
		if( ptr->ID == Type )
			return ptr->sID;
		ptr++;
	}
	
	Msg(0, "WARN: �� ������ ��� ����. ID = %i", Type);

	char str[32];
	ltoa(Type, str, 16);
	return str;
}

const char* CUserRightsProp::ValueAsString()
{
	if( Value == 0 )
		return "���";
	else
		return "��";
}

void CUserRightsProp::BeautyString(CBeautyString& String, int level)
{
	String.add_parameter(level, TypeAsString(), ValueAsString(), "", true);
}

void CUserRightsProp::CSVString(GCString& String)
{
	GCString str = TypeAsString();
	str += ";";
	str += ValueAsString();
	String += str;
}


void CUserRightsProp::Read(CStorage& Storage)
{
	IStream* pStream = Storage.pStream;

	pStream->Read(&Type, sizeof(Type), NULL);
	pStream->Read(&Value, sizeof(Value), NULL);
}

////////////////////////////////////////////////////////////////////
CUserRightsBlock::TBlockType CUserRightsBlock::BlockTypes[] = {
	{0x01, "���������"},
	{0x03, "����������"},
	{0x06, "�������"},
	{0x09, "��������"},
	{0x0b, "������ ����������"},
	{0x10, "�����"},
	{0x11, "������������"},
	{0x12, "���������"},
	{0x17, "������ ��������"},
	{0x18, "���������"},
	{0x19, "���� ������"},
	{0x1a, "��������"},
	{0x1b, "��������"},
	{0x1c, "������� ��������"},
	{0x1f, "0x1F"},
	{0x00, NULL}
};

CUserRightsBlock::CUserRightsBlock()
{
	Type = 0;
	MetadataID = 0;
	nProps = 0;
}

CUserRightsBlock& CUserRightsBlock::operator=(CUserRightsBlock& Block)
{
	Type = Block.Type;
	MetadataID = Block.MetadataID;
	nProps = Block.nProps;
	return *this;
}

const char* CUserRightsBlock::TypeAsString()
{
	TBlockType* ptr = BlockTypes;
	while( ptr->sID != NULL )
	{
		if( ptr->ID == Type ) return ptr->sID;
		ptr++;
	}

	Msg(0, "WARN: ����������� ������ ����. ID = %i", Type);

	char str[32];
	ltoa(Type, str, 16);
	return str;
}

void CUserRightsBlock::BeautyString(CBeautyString& String, int level)
{
	String.add_parameter(level, TypeAsString(), Metadata_sID, NULL, true);
	String.add_brace(level, '{');

	for( int i = 0; i < nProps; i++ )
	{
		Props[i].BeautyString(String, level+1);
	}

	String.add_brace(level, '}');
}

void CUserRightsBlock::CSVString(GCString& String, GCString& Prefix)
{
	GCString str;

	for( int i = 0; i < nProps; i++ )
	{
		str += Prefix;
		if( Metadata_sID.IsEmpty() )
		{
			str += TypeAsString();
		}
		else
		{
			str += Metadata_sID;
		}
		str += ";";
		Props[i].CSVString(str);
		str += "\n";
	}

	String += str;
}

void CUserRightsBlock::Read(CStorage& Storage)
{
	IStream* pStream = Storage.pStream;
	
	pStream->Read(&Type, sizeof(Type), NULL);
	pStream->Read(&MetadataID, sizeof(MetadataID), NULL);
	pStream->Read(&nProps, sizeof(nProps), NULL);

	Props.SetSize(nProps);
	for( int i = 0; i < nProps; i++ )
	{
		Props[i].Read(Storage);
	}

	if( MetadataID != 0 )
	{
		Metadata_sID = MainMetadataStream->ObjectIDtoName(MetadataID);
		if( Metadata_sID.IsEmpty() )
			Metadata_sID.Format("%i", MetadataID);
	}
}

int __cdecl CUserRightsBlock::CompareBysID(const void *elem1, const void *elem2)
{
	CUserRightsBlock *b1 = (CUserRightsBlock*)elem1, *b2 = (CUserRightsBlock*)elem2;

	if( b1->Type == b2->Type )
		return b1->Metadata_sID.CollateNoCase(b2->Metadata_sID);

	//����� �� ������������ ����� ���� �������.
	if( b1->Type == 0x11 ) return -1;
	if( b2->Type == 0x11 ) return 1;

	if( b1->Type < b2->Type )
		return -1;
	else
		return 1;
}


////////////////////////////////////////////////////////////////////
CUserRights::CUserRights()
{
	ID = 0x06;
	nBlocks = 0;
}

void CUserRights::BeautyString(CBeautyString& String)
{
	Description.quote_linefeeds();
	String.add_parameter(0, "��������", Description, "");

	for( int i = 0; i < nBlocks; i++ )
	{
		if( TaskParameters.NoBrokenLinks && Blocks[i].LinkIsBroken() ) continue;
		Blocks[i].BeautyString(String, 0);
	}
}

void CUserRights::CSVString(GCString& String, GCString& RightsName)
{
	GCString str;
	GCString Prefix = RightsName;
	Prefix += ";";
	for( int i = 0; i < nBlocks; i++ )
	{
		if( TaskParameters.NoBrokenLinks && Blocks[i].LinkIsBroken() ) continue;
		Blocks[i].CSVString(str, Prefix);
	}
	String += str;
}


void CUserRights::Read(CStorage& Storage)
{
	IStream* pStream = Storage.pStream;
	
	pStream->Read(&ID, sizeof(ID), NULL);
	ReadSizedString(Description, pStream);
	
	pStream->Read(&nBlocks, sizeof(nBlocks), NULL);

	Msg(2, "   %i ������", nBlocks);
	Blocks.SetSize(nBlocks);
	for( int i = 0; i < nBlocks; i++ )
	{
		Blocks[i].Read(Storage);
	}

	if( TaskParameters.SortUserRightsObjects )
		qsort((void*)Blocks.GetData(), nBlocks, sizeof(CUserRightsBlock), CUserRightsBlock::CompareBysID);
}

void CUserRights::WriteToFile(CStorage& Storage, GCString FileName)
{
	CBeautyString String;
	BeautyString(String);
	Storage.CopyStringToFile(String, FileName);
}


void DecompileUserRights(GCString& Dir, CStorage& Storage)
{
	CNameTableRecord* nt_rec = NameTable.Find(NT_UserRights);
	GCString DestDir = nt_rec->PrepareDirName(Dir);

	CNameTableRecord* nt_rec_one_file = NameTable.Find(NT_UserRightsOneFile);
	GCString CSV_FName = nt_rec_one_file->PrepareFileName(Dir);

	MMS_Filter.Down();
	if( MMS_Filter.Test(NULL, nt_rec) )
	{
		CStorage RtStorage(Storage);

		if( RtStorage.Open(nt_rec->PrepareStorageName()) )
		{
			GCString CSVString;
			CContainer CC;
			RtStorage.ParseStream(&CC, GCString("Container.Contents"), false);
			CObjectOrdering Ordering(2);

			CreateDirectory(DestDir);

			for( int i = 0; i < CC.GetNChildren(); i++ )
			{
				CContainerRecord* RtDescr = (CContainerRecord*)CC.GetChild(i);
				CUserRights Rights;
				GCString& StreamName = RtDescr->StreamName;
				GCString& RightsName = RtDescr->ObjectName;
				RtDescr->sID = (LPCSTR)RightsName;
				MangleFileName(RtDescr->sID);
				GCString FileName = nt_rec->PrepareFileName(Dir, RtDescr);

				Msg(2, "����� ���� '%s'", RightsName);
				RtStorage.OpenStream(StreamName);
				try
				{
					Rights.Read(RtStorage);
				}
				catch(...)
				{
					Msg(0, "ERR: ������ ��� ������ ������ ���� %s", RightsName);
				}

				Rights.WriteToFile(RtStorage, FileName);
				Ordering.Add(RtDescr->sID, RightsName, StreamName);

				if (TaskParameters.MakeUserRightsInOneFile)
					Rights.CSVString(CSVString, RightsName);
			}
			Ordering.WriteFile(RtStorage, DestDir);

			if (TaskParameters.MakeUserRightsInOneFile)
				RtStorage.CopyStringToFile(CSVString, CSV_FName);
		}
	}
	MMS_Filter.Up();
}