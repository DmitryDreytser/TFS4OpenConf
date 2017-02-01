
#ifndef MMS_Document_H
#define MMS_Document_H

#include "MMS_Basic.h"

////////////////////////////////////////////////////////////
//// ����������  ///////////////////////////////////////////
////////////////////////////////////////////////////////////
class CDocNumDef : public CMMSObjectAttribute
{
public:
	int Length;
	CStoredSet Period;
	CStoredSet Type;
	CStoredSet	AutoNumeration;	//8.	�������������� ���������: 1 - ���, 2 - ��
	CStoredBool Unique;

private:
	static CDocNumDef* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CDocNumDef();

	CPropertySet* GetPropSet() {return &PropSet;};
};

class CDocNumDefList : public CMMSAttributes_SF
{
public:
	CDocNumDefList() {MMS_Type = MMS_DocNumDef;}
	
	virtual const char* BeautyName() { return "����������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CDocNumDef;}
};

////////////////////////////////////////////////////////////
//// ����� ���� ����������  ////////////////////////////////
////////////////////////////////////////////////////////////
class CGenJrnlFldDef : public CMMSObjectAttribute
{
public:
	CStoredBool NonNegative;
	CStoredBool DivideTriades;
	CStoredBool Selection;

private:
	static CGenJrnlFldDef* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CGenJrnlFldDef();

	CPropertySet* GetPropSet() {return &PropSet;};
};

class CGenJrnlFldList : public CMMSAttributes_SF
{
public:
	CGenJrnlFldList() {MMS_Type = MMS_GenJrnlFldDef;}

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CGenJrnlFldDef;}
	virtual const char* BeautyName() {return "����� ���� ����������";}
};

///////////////////////////////////////////////////////////
//// ��������� ////////////////////////////////////////////
///////////////////////////////////////////////////////////
class CDocHeadField : public CMMSObjectAttribute
{
public:
	CStoredBool	NonNegative;	//9.	���������������: 1 ��� 0
	CStoredBool	DivideTriades;	//10.	��������� ������: 1 ��� 0

	CDocHeadField();
	CPropertySet* GetPropSet() {return &PropSet;};
private:
	static CDocHeadField* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;
};

class CDocHeadFieldList : public CMMSAttributes
{
public:
	CDocHeadFieldList() {MMS_Type = MMS_DocHeadFields;}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CDocHeadField;}
	virtual const char* BeautyName() {return "�������� �����";}
};

//-----------------
class CDocTableField : public CMMSObjectAttribute
{
public:
	CStoredBool	NonNegative;	//9.	���������������: 1 ��� 0
	CStoredBool	DivideTriades;	//10.	��������� ������: 1 ��� 0
	CStoredBool	ColumnSum;		//11.	���� �� �������: 1 ��� 0

	CDocTableField();
	CPropertySet* GetPropSet() {return &PropSet;};

private:
	static CDocTableField* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;
};

class CDocTableFieldList : public CMMSAttributes
{
public:
	CDocTableFieldList() {MMS_Type = MMS_DocTableFields;}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CDocTableField;}
	virtual const char* BeautyName() {return "�������� ��������� �����";}
};

class CDocBaseRefers : public CMMSRefers
{
public:
	virtual const char* BeautyName() {return "�������� ���������� ���";}
};

//----------------
class CMMSDocument : public CMMSObjectAttribute
{
public:
	int			NumberLength;	//5.	����� ������
	CStoredSet	NumberPeriod;	//6.	�������������: 0 - �� ���� ������� ����, 1 - � �������� ����, 2 - � �������� ��������, 3 - � �������� ������, 4 - � �������� ���.
	CStoredSet	NumberType;		//7.	��� ������: 1 - ���������, 2 - ��������
	CStoredSet	AutoNumeration;	//8.	�������������� ���������: 1 - ���, 2 - ��
	CMMSObjRef	Journal;		//9.	���������� ������������� ������� ����������. ���� 0, �� ������ �� �����.
	int			Param10;		//10.	����������. ������ -1.
	CStoredBool	UniqueNumbers;	//11.	�������� ������������ �������: 1 ��� 0
	CMMSObjRef	Numerator;		//12.	��������� ������������� ����������. ���� 0, �� ��������� �� �����.
	CStoredBool	Trade;			//13.	����������� ����: 1 ��� 0
	CStoredBool	Salary;			//14.	������: 1 ��� 0
	CStoredBool	Account;		//15.	������������� ����: 1 ��� 0
	CDocBaseRefers BaseParams;	//16.	��������� ����� �� ���������
	CStoredBool	BaseForAny;		//17.	����� �������� ���������� ��� ������ ���������: 1 ��� 0
	CStoredSet	CreateOperation;//18.	��������� ��������: 0 - ������, 1 - ���������, 2 - ������ ��� ����������
	CStoredBool	AutoNumberLines;//19.	�������������� ��������� �����: 1 ��� 0
	CStoredBool	AutoDelActions;	//20.	�������������� �������� ��������
	CStoredBool	EditOperation;	//21.	������������� ��������: 1 ��� 0
	CStoredBool	EnableActions;	//22.	��������� ����������: 1 ��� 0
	
	CDocHeadFieldList HeadFields;
	CDocTableFieldList TableFields;
	CMigrationRules MigrationRules;

private:
	static CMMSDocument* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMMSDocument();
	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);

public:
	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};


////////////////////////////////////////////////////////////
class CMMSDocuments : public CMMSAttributes
{
public:
	CMMSDocuments();
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSDocument;}
	virtual const char* BeautyName() {return "���������";}

public:
	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};

///////////////////////////////////////////////////////////
//// ������������������ ���������� ////////////////////////
///////////////////////////////////////////////////////////
class CDocStreamRegisters : public CMMSSimpleReferList
{
public:
	virtual const char* BeautyName() {return "�������� �������� �� ������������������";}
	virtual const char* MMSName() {return "Registers";}
};
class CDocStreamDocuments: public CMMSSimpleReferList
{
public:
	virtual const char* BeautyName() {return "������������������ ������ �� ���������� ����������";}
	virtual const char* MMSName() {return "Documents";}
};

class CMMSDocStream: public CMMSObjectAttribute
{
public:
	GCString Param5;
	CStoredSet Migration; //6. ��������� ��� ����: 0 - ������ ������������������ � ����������� ��; 1 - ��������� ������������������ � ����� ��.
	CDocStreamRegisters Registers; //7
	CDocStreamDocuments Documents; //8

private:
	static CMMSDocStream* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMMSDocStream();

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);
};

class CMMSDocStreamList : public CMMSAttributes_SF
{
public:
	CMMSDocStreamList() {MMS_Type = MMS_DocumentStreams;}
	virtual const char* BeautyName() {return "������������������ ������ �� ���������� ����������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSDocStream;}
};

////////////////////////////////////////////////////////////
//// ����� ������  /////////////////////////////////////////
////////////////////////////////////////////////////////////
class CDocSelRefObj : public CMMSObjectAttribute
{
public:
	CStoredBool SelectEmpty;
	CMMSTypeLetter TypeLetter;
	CMMSObjRef TypeObject;
	CMMSReferList Refers;

private:
	static CDocSelRefObj* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CDocSelRefObj();

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);
};

class CDocSelRefObjList : public CMMSAttributes_SF
{
public:
	CDocSelRefObjList() {MMS_Type = MMS_DocSelRefObj;}

	virtual const char* BeautyName() { return "����� ������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CDocSelRefObj;}
};

///////////////////////////////////////////////////////////
//////  ������� ����������  ///////////////////////////////
///////////////////////////////////////////////////////////
class CJournFldContent: public CMMSReferList
{
public:
	virtual const char* BeautyName() {return "���� ����������";}
};

class CJournalFld : public CMMSObjectAttribute
{
private:
	static CJournalFld* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CJournFldContent DocumentFields;

public:
	CJournalFld() {}

	CPropertySet* GetPropSet() {return &PropSet;};

	virtual CMMSObject* AddChild(CMMSObject* child) {return NULL;}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{ return &DocumentFields; }
};

class CJournalFldList : public CMMSAttributes
{
public:
	CJournalFldList() {MMS_Type = MMS_JournalFlds;}

	virtual const char* BeautyName()
		{ return "���� �������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{ return new CJournalFld; }
};

class CJournalDocuments : public CMMSRefers
{
public:
	virtual const char* BeautyName() {return "������ �������";}
};

class CMMSJournal: public CMMSObjectAttribute//CMMSSynonymedObject
{
private:
	static CMMSJournal* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	GCString        Param5;         //5.	����������� ��������
	CStoredBool     IsCommon;       //6.	��� �������: 0 - �������, 1 - �����
	CMMSObjRef      SelectionForm;  //7.	�������� ������������� ����� ��� ������
	CMMSObjRef      MainForm;       //8.	�������� ������������� �������� �����
	CStoredBool     NonAditional;   //9.	�� ��������������: 0 - ������ ��������������, 1 - ���
	CJournalDocuments Documents;    //10.	������ �������
	CJournalFldList Fields;         //11.	����� �������
	CFormDescrList  Forms;          //12.	����� �������

public:
	CMMSJournal();
	CPropertySet* GetPropSet() {return &PropSet;};

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);

	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};


////////////////////////////////////////////////////////////
class CMMSJournalList: public CMMSAttributes
{
public:
	CMMSJournalList()
		{MMS_Type = MMS_Journalisters;}
	virtual const char* BeautyName() {return "������� ����������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{ return new CMMSJournal; }

	void Decompile(GCString& SrcDir, CStorage& Storage, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};

#endif
