///////////////////////////////////////////////////////////////////////
///// Main Metadata Stream ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

#ifndef MMS_Basic_H
#define MMS_Basic_H

#include <afxtempl.h>
#include "StreamInfo.h"
#include "Declarations.h"
#include "MMS_BasicTypes.h"
#include "Lexer.h"


typedef struct {
	int ID;
	GCString Name;
} TObjNameCacheRecord;
typedef CArray<TObjNameCacheRecord, TObjNameCacheRecord&> CObjNameCache;


///////////////////////////////////////////////////////////
//// Generic MMS object ///////////////////////////////////
///////////////////////////////////////////////////////////
class CMMSObject : public CStoredObject
{
public:
	MMSObjectType MMS_Type;
	enum {IDT_NoID = 0, IDT_OnlyNumeric = 1, IDT_OnlyTextual = 2, IDT_BothIDs = 3} ID_Type;
	GCString sID;
	int ID;
	int Order; //��� ����������

	//bool Used; //��� �������� �������� ������� � ��� ������� �������

protected:
	CPtrArray Children;
	bool ToDestroyChildren;

public:
	CMMSObject();
	CMMSObject(CMMSObject& src);
	virtual ~CMMSObject();

	void DestroyObjects();

public:
	//===== ������ ������� � �������� ==========
	virtual CMMSObject* AddChild(CMMSObject* child)
	{
		Children.Add((void*)child);
		return child;
	}
	virtual void DelChild(int i)
	{
		Children.RemoveAt(i, 1);
	}
	virtual void DelChild(GCString& sID);
	virtual int GetNChildren()
	{
		return Children.GetSize();
	}
	virtual CMMSObject* GetChild(int i)
	{
		return (CMMSObject*)(Children.GetAt(i));
	}

	//������� ������ ����� �������� - ����� ��� ������ ���������� � ���� �������
	virtual int CountObjects() {return GetNChildren();}

	//� ������ ������������ ������ � pList ����� ������������ ������ ���� � �������
	virtual CMMSObject* FindChild(int ID, bool recursive = false, CPtrList* pList = NULL);
	virtual CMMSObject* FindChild(GCString& sID, bool recursive = false);

	void SortByOrder();

	//===== ������ �������� ����� ��������. ��� �������. =======
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);
	virtual void SetIDs(const char* Name, const char* Value); //����� ���������� �� �������
	virtual void ParseMetadata(CLexer& Lexer);
	virtual void AssembleMetadata(GCString& Dir);
	virtual void ParseFile(CLexer& Lexer);
	bool ParseFile(GCString& FileName);

	//===== ������ ��� ������ ��� �� ������ ��������. ��� ������� �������. =====
	//void MarkUsed(int ID);
	//void DeleteUnused();

	virtual void ToString(CMMSString& String);

	virtual void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);
	virtual void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& Dir);

	//==== ��������������� ������ ��� ������������ ============
	void ExtractString(CStorage& Storage, GCString& DestDir, GCString& Str, MMSObjectType Type);
	bool ExtractMetadata(GCString& DestDir, MMSObjectType Type, CStorage& TypedTextStorage);
	void ExtractMetadata(GCString& DestDir, CStorage& TypedTextStorage);
	
	//FNamePrefix - � ����� ������ ��� ������� � ����������� '\'
	//StdName - ���� true, �� ��� ����� ������� ��� ����� ������ �� NameTable � �� sID. 
	//          �������� ���� ��������� �������� ����������� �� sID.
	void ExtractDescriptions(GCString& FNamePrefix, CStorage& TypedTextStor, bool StdName);
	void ImportDescriptions(CStorage& TypedTextStor, GCString& FNamePrefix, bool StdName);

	bool ImportStreamByType(CStorage& Storage, MMSObjectType Type, GCString& SrcDir);
	void ExtractStreamByType(CStorage& Storage, MMSObjectType Type, GCString& Dir, bool NotExtractEmpty = false);
	
	void ExtractMoxelPages(GCString& DestDir, CStorage& WBStorage);
	void ExtractWorkBook(GCString& DestDir, CStorage& Storage, CMMSObject* Parent);
	void ExtractListForms(CFormDescrList& Forms, GCString& Dir, CStorage& Storage, GCString Prefix);
	void ExtractOrdering(CStorage& Storage, GCString& DestDir);

	bool ImportMoxelPages(CStorage& Storage, GCString& SrcDir, GCString& ContCont);
	void ImportContainerProfile(CStorage& Storage, GCString& SrcDir);
	bool ImportWorkBook(CStorage& Storage, GCString& SrcDir);
	bool ImportListForms(CFormDescrList& Forms, CStorage& Storage, GCString& SrcDir, GCString Prefix);
	void ImportOrdering(GCString& SrcDir);

	void BuildObjNameCache(CObjNameCache& Cache, GCString& NamePrefix, int level = 0);
	GCString GetObjectDir(GCString& ParentDir);
};


////////////////////////////////////////////////////////////
//// �������������� ������  /////////////////////////////////
////////////////////////////////////////////////////////////
//������� ���� ����������, �������� � �.�.  � �������� ������ ����� ��������� ���
//<BeautyName>:
//{
//	...
//}
class CMMSTypedObject : public CMMSObject
{
public:
	virtual const char* BeautyName() {return sID;}
	virtual void BeautyString(CBeautyString& String, int level);
};

////////////////////////////////////////////////////////////
//// Array of attributes   /////////////////////////////////
////////////////////////////////////////////////////////////
class CMMSAttributes : public CMMSObject
{
public:
	CMMSAttributes();

	virtual bool SetValue(int MMS_Index, GCString& Value);
	virtual const char* BeautyName() = 0;
	virtual const char* MMSName();

	virtual void BeautyString(CBeautyString& String, int level);
	virtual void ToString(CMMSString& String);

	virtual void AssembleMetadata(GCString& Dir);
};

//�������, ������� ����� �������������� �� ������ (���������, ������������, ���������� � �.�.)
class CMMSAttributes_SF : public CMMSAttributes
{
public:
	virtual int CountObjects();

	virtual void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);
	virtual void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};

class CMMSSynonymedObject : public CMMSObject
{
public:
	GCString Comment;
	GCString Synonym;

public:
	CMMSSynonymedObject() {ID_Type = IDT_BothIDs;}
};

////////////////////////////////////////////////////////////
//// ��������� �������� �������  ///////////////////////////
////////////////////////////////////////////////////////////
class CMMSObjectAttribute : public CMMSSynonymedObject
{
public:
	CMMSAttributeType Type;

public:
	void BeautyString(CBeautyString& String, int level, bool NoNumericID);
	virtual void BeautyString(CBeautyString& String, int level);
};

////////////////////////////////////////////////////////////
//// ����� ������  /////////////////////////////////////////
////////////////////////////////////////////////////////////
class CFormDescr : public CMMSObjectAttribute
{
private:
	static CFormDescr* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CPropertySet* GetPropSet() {return &PropSet;};
};

class CFormDescrList : public CMMSAttributes
{
public:
	CFormDescrList() {sID = "Form";}

	virtual bool SetValue(int MMS_Index, GCString& Value) {return true;}

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CFormDescr;}
	virtual const char* BeautyName() {return "����� ������";}
};

///////////////////////////////////////////////////////////
//// ������ ������ �� ������ �������  /////////////////////
///////////////////////////////////////////////////////////
class CMMSReferList : public CMMSObject
{
	friend class CMMSRefers;

private:
	CPtrArray Refers;

public:
	~CMMSReferList();

	virtual void ParseMetadata(CLexer& Lexer);
	virtual void ParseFile(CLexer& Lexer);
	virtual bool SetValue(int MMS_Index, GCString& Value);
	virtual bool SetValue(GCString& Name, GCString& Value);

	virtual const char* BeautyName() {return "������";}
	virtual void BeautyString(CBeautyString& String, int level);
	virtual void ToString(CMMSString& String);
};

class CMMSRefers : public CMMSObjectAttribute
{
public:
	CMMSReferList Refers;

private:
	static CMMSRefers* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CPropertySet* GetPropSet() {return &PropSet;};
	virtual const char* BeautyName() {return "������";}
	virtual void BeautyString(CBeautyString& String, int level);
	virtual void ToString(CMMSString& String);
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return &Refers;}
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);
	virtual CMMSObject* AddChild(CMMSObject* child) {return NULL;}
};

//"�����������" ������ ����������. ��������:  {"Days", "800", "800", "0"}
class CMMSNamedList : public CMMSObject
{
private:
	CPtrArray PropArray;

public:
	CMMSNamedList();
	~CMMSNamedList();

	virtual int GetNChildren() {return PropArray.GetSize();}
	virtual CStoredProperty* CreateProperty() = 0;

	virtual bool SetValue(int MMS_Index, GCString& Value);
	virtual void ParseMetadata(CLexer& Lexer);
	virtual void ParseFile(CLexer& Lexer);

	virtual const char* BeautyName() = 0;
	virtual const char* MMSName() = 0;

	virtual void BeautyString(CBeautyString& String, int level);
	virtual void ToString(CMMSString& String);
};

//������ �� �������, �� �������� ��������������� �� � �������� �������
class CMMSSimpleReferList : public CMMSNamedList
{
public:
	virtual CStoredProperty* CreateProperty() {return new CMMSObjRef;}
	virtual const char* BeautyName() {return "������";}
	virtual const char* MMSName() {return "Ref";}
};

////////////////////////////////////////////////////////////
//// ������� ��������  /////////////////////////////////////
////////////////////////////////////////////////////////////
class CMigrationRules : public CMMSObject
{
public:
	CMigrationArea	Area;		//1.	������� ���������������: W - ��� �������������� ����, L - ����� ��������, M - ����� �������� � �����
	GCString		OtherBases;	//2.	���� �������������� �� (���� "�������������" � ���������� ������ ��������): ������
	CStoredBool		AutoRegisterChanges; //3.	�������������� ����������� ���������: 1 ��� 0

private:
	static CMigrationRules* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMigrationRules();
	CMigrationRules& operator=(CMigrationRules& src);
	
	const char* BeautyName() {return "��������� ��������";}

	bool operator==(CMigrationRules& Rules);
	CPropertySet* GetPropSet() {return &PropSet;};
	virtual void BeautyString(CBeautyString& String, int level);
	virtual void ToString(CMMSString& String);
};

////////////////////////////////////////////////////////////
//// ���������  ////////////////////////////////////////////
////////////////////////////////////////////////////////////
class CConstant: public CMMSObjectAttribute
{
public:
	CStoredBool NonNegative;
	CStoredBool DivideTriades;
	CStoredBool Periodical;
	CMigrationRules MigrationRules;

private:
	static CConstant* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CConstant();

	CPropertySet* GetPropSet() {return &PropSet;};

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);
};

class CConstantList : public CMMSAttributes_SF
{
public:
	CConstantList();

	virtual const char* BeautyName() { return "���������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CConstant;}
};

///////////////////////////////////////////////////////////////////////
///////////  ������ ���������  ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//  ���������
class CRegisterProp : public CMMSObjectAttribute
{
private:
	static CRegisterProp* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CStoredBool	NonNegative;	//9.	���������������: 1 ��� 0
	CStoredBool	DivideTriades;	//10.	��������� ������: 1 ��� 0
	CStoredBool	SelectMovement;	//11.	����� ��������: 1 ��� 0
	CStoredBool	SelectSummaries;//12.	����� ������: 1 ��� 0

	CPropertySet* GetPropSet() {return &PropSet;};
};

class CRegisterProps : public CMMSAttributes_SF
{
public:
	CRegisterProps() {MMS_Type = MMS_RegisterProps;}

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CRegisterProp;}
	virtual const char* BeautyName() {return "���������";}
};

//-- ������� ---------------------------
class CRegisterFigure : public CMMSObjectAttribute
{
private:
	static CRegisterFigure* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CStoredBool	NonNegative;	//9.	���������������: 1 ��� 0
	CStoredBool	DivideTriades;	//10.	��������� ������: 1 ��� 0

	CPropertySet* GetPropSet() {return &PropSet;};
};

class CRegisterFigures : public CMMSAttributes
{
public:
	CRegisterFigures() {MMS_Type = MMS_RegisterFigures;}

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CRegisterFigure;}
	virtual const char* BeautyName() {return "�������";}
};

//-- ��������� ---------------------------
class CRegisterFld : public CMMSObjectAttribute
{
private:
	static CRegisterFld* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CStoredBool	NonNegative;	//9.	���������������: 1 ��� 0
	CStoredBool	DivideTriades;	//10.	��������� ������: 1 ��� 0
	CStoredBool	SelectMovement;	//11.	����� ��������: 1 ��� 0

	CPropertySet* GetPropSet() {return &PropSet;};
};

class CRegisterFlds : public CMMSAttributes
{
public:
	CRegisterFlds() {MMS_Type = MMS_RegisterFlds;}

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CRegisterFld;}
	virtual const char* BeautyName() {return "���������";}
};

//-- ������� ---------------------------
class CMMSRegister : public CMMSObjectAttribute
{
private:
	static CMMSRegister* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CStoredBool      Rotation;		//5.	���������: 1 ��� 0
	CPeriod          Period;		//6.	������������� (������ ��� ���������): Y - ���, Q - �������, M - �����, C - ������, W - ������, D - ����
	CStoredBool      FastMovement;	//7.	������� ��������� ��������: 1 ��� 0
	CStoredBool      Migration;		//8.	��������� �������� ��������: 1 ��� 0  (������ 1).
	CRegisterProps   RegProps;		//9.	���������
	CRegisterFigures Figures;		//10.	�������
	CRegisterFlds    Flds;			//11.	���������

public:
	CMMSRegister();
	CPropertySet* GetPropSet() {return &PropSet;};

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);
};

class CMMSRegisterList: public CMMSAttributes_SF
{
public:
	CMMSRegisterList() {MMS_Type = MMS_Registers;}
	virtual const char* BeautyName() {return "��������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSRegister;}
};

////////////////////////////////////////////////////////////
class CMMSEnumVal : public CMMSObjectAttribute
{
public:
	GCString Representation;

private:
	static CMMSEnumVal* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;
public:
	CPropertySet* GetPropSet() {return &PropSet;};
};

class CMMSEnumValList : public CMMSAttributes
{
public:
	CMMSEnumValList() {MMS_Type = MMS_EnumVal;}

	virtual const char* BeautyName()
		{return "�������� ������������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSEnumVal;}
};

class CMMSEnum : public CMMSObjectAttribute
{
public:
	CMMSEnumValList ValList;

private:
	static CMMSEnum* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMMSEnum();
	CPropertySet* GetPropSet() {return &PropSet;};

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return &ValList;}
};

class CMMSEnumList: public CMMSAttributes_SF
{
public:
	CMMSEnumList()
		{MMS_Type = MMS_EnumList; ID_Type = IDT_OnlyTextual;}
	virtual const char* BeautyName()
		{return "������������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSEnum;}
};


////////////////////////////////////////////////////////////
class CMMSReport : public CMMSObjectAttribute//public CMMSSynonymedObject
{
private:
	static CMMSReport* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMMSReport() {MMS_Type = MMS_Report;};

	CPropertySet* GetPropSet() {return &PropSet;};

	void Decompile(GCString& Dir, CStorage& Storage, GCString& Prefix, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir, GCString& SubStroragePrefix);
};

////////////////////////////////////////////////////////////
class CMMSReportList : public CMMSAttributes
{
public:
	CMMSReportList() {MMS_Type = MMS_ReportList; sID = "ReportList";}

	virtual const char* BeautyName()
		{ return "������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{ return new CMMSReport; }

public:
	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};

class CMMSCalcVarList : public CMMSReportList
{
public:
	CMMSCalcVarList() {MMS_Type = MMS_CalcVars; sID = "CalcVars";}

	virtual const char* BeautyName()
		{ return "���������"; }
};

#endif //MMS_Basic_H