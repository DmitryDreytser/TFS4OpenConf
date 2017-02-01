#ifndef MMS_Calculation_H
#define MMS_Calculation_H

#include "MMS_Basic.h"

///////////////////////////////////////////////////////////
//////  ������� ��������  /////////////////////////////////
///////////////////////////////////////////////////////////
class CCalcJournalFld : public CMMSObjectAttribute
{
private:
	static CCalcJournalFld* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CStoredBool NonNegative;
	CStoredBool DivideTriades;

public:
	CCalcJournalFld();

	CPropertySet* GetPropSet() {return &PropSet;};
};

class CCalcJournalFldList : public CMMSAttributes
{
public:
	CCalcJournalFldList() {MMS_Type = MMS_CJParams;}

	virtual const char* BeautyName()
		{ return "���� �������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{ return new CCalcJournalFld; }
};

class CCalcJournSelections : public CMMSSimpleReferList
{
public:
	virtual const char* BeautyName() {return "����� ������";}
	virtual const char* MMSName() {return "FF";}
};

class CMMSCalcJournal : public CMMSObjectAttribute
{
private:
	static CMMSCalcJournal* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMMSObjRef		Subconto;		//5.  �������� ������������� ����������� (���� "����������" � ������� ���������� �������)
	CStoredSet		Period;			//6.	�������������: 0 - ����, 1 - ������, 2 - �����, 3 - �������, 4 - ���
	int				StartDate;		//7.	���� ������ ������� � ���� ���������� ���� � �����-�� ������� ���� (� ������ �����?)
	CCalcJournalFldList FldList;	//8.	��������� �������
	int				ResultLength;	//9.	����� ����������
	int				ResultPrec;		//10.	�������� ����������
	CStoredSet		WriteOn;		//11.	���������� ��: 0 - �� ����� ���������� �������; 1 - �� ������ ���������� �������
	CCalcJournSelections Selections;//12.	����� ������
	CFormDescrList	Forms;			//13.	����� ������
	CMMSObjRef      SelectionForm;	//14.	�������� ������������� ����� ��� ������
	CMMSObjRef      MainForm;		//15.	�������� ������������� �������� �����

public:
	CMMSCalcJournal();

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);

	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};

//----------------------
class CMMSCalcJournalList: public CMMSAttributes
{
public:
	CMMSCalcJournalList()
		{MMS_Type = MMS_CalcJournals;}

	virtual const char* BeautyName() {return "������� ��������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{ return new CMMSCalcJournal; }

	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};


///////////////////////////////////////////////////////////
//////  ���� ��������  ////////////////////////////////////
///////////////////////////////////////////////////////////
class CCalcAlgExclusion : public CMMSRefers
{
public:
	virtual const char* BeautyName() {return "����������� ���� �������";}
};

class CCalcAlgInGroups : public CMMSSimpleReferList
{
public:
	virtual const char* BeautyName() {return "������ � ������";}
	virtual const char* MMSName() {return "InGroups";}
};

class CMMSCaclAlgorithm : public CMMSObjectAttribute
{
private:
	static CMMSCaclAlgorithm* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	int Priority; //5.	��������� (�����)
	GCString Param6;
	GCString Param7;
	CCalcAlgExclusion Exclusion; //8.	��������� ����������
	CCalcAlgInGroups InGroups; //9.	�������� � ������

public:
	CMMSCaclAlgorithm()
		{MMS_Type = MMS_CalcAlgorithm; ToDestroyChildren = false;}

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);

	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};


//--------------
class CMMSCaclAlgorithmList : public CMMSAttributes_SF
{
public:
	CMMSCaclAlgorithmList()
		{MMS_Type = MMS_CalcAlgorithms;}

	virtual const char* BeautyName() {return "���� ��������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSCaclAlgorithm;}

	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};

///////////////////////////////////////////////////////////
//////  �������  �����������  /////////////////////////////
///////////////////////////////////////////////////////////
class CRecalcDependent : public CMMSRefers
{
public:
	virtual const char* BeautyName() {return "��� �������������";}
};

class CRecalcBase : public CMMSRefers
{
public:
	virtual const char* BeautyName() {return "��������� ��� ���������";}
};

class CMMSRecalcRule : public CMMSObjectAttribute
{
private:
	static CMMSRecalcRule* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CStoredSet When;  //5.	������ ��� ���������: 0 - ������ � ������� ������� ������� ��������; 1 - � ��� �� ������� ��; 2 - � ��������� N ��������
	int NumPeriods;   //6.	����� <param5> = 2, �� ��� ����� �������� ��� ��������� (N)
	CRecalcDependent Dependent; //7.	������ �� ���� ��������, ������� ����� �������������
	CRecalcBase Base; //8.	������ �� ���� ��������, ��� ����� ������� ���������� ��������

public:
	CMMSRecalcRule();

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);
};


//--------------
class CMMSRecalcRuleList : public CMMSAttributes
{
public:
	CMMSRecalcRuleList()
		{MMS_Type = MMS_RecalcRules;}

	virtual const char* BeautyName() {return "������� �����������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSRecalcRule;}
};

///////////////////////////////////////////////////////////
//////  ������ ��������  //////////////////////////////////
///////////////////////////////////////////////////////////
class CCalcGroupAlgs : public CMMSSimpleReferList
{
public:
	virtual const char* BeautyName() {return "������ ������";}
	virtual const char* MMSName() {return "Algs";}
};

class CMMSCaclAlgGroup: public CMMSObjectAttribute
{
private:
	static CMMSCaclAlgGroup* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CCalcGroupAlgs Algs; //5.	������ ������

public:
	CMMSCaclAlgGroup()
		{ToDestroyChildren = false;}

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);
};


//--------------
class CMMSCaclAlgGroupList : public CMMSAttributes_SF
{
public:
	CMMSCaclAlgGroupList()
		{MMS_Type = MMS_Groups;}

	virtual const char* BeautyName() {return "������ ��������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSCaclAlgGroup;}
};

///////////////////////////////////////////////////////////
//////  ���������  ////////////////////////////////////////
///////////////////////////////////////////////////////////
class CMMSHolydays: public CMMSObjectAttribute
{
private:
	static CMMSHolydays* DefVal;
	static CObjectProperty Props[];
	static CPropertySet    PropSet;

public:
	CMigrationRules MigrationRules; //5. ������� ��������

public:
	CMMSHolydays() {}

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return &MigrationRules;}
	virtual CMMSObject* AddChild(CMMSObject* child) {return NULL;}
	
	virtual void BeautyString(CBeautyString& String, int level);
	virtual void ToString(CMMSString& String);
};

class CCalendarDays : public CMMSNamedList
{
public:
	virtual CStoredProperty* CreateProperty() {return new CStoredString;}
	virtual const char* BeautyName() {return "��������� ����";}
	virtual const char* MMSName() {return "Days";}
};

class CMMSCalendar : public CMMSObjectAttribute
{
private:
	static CMMSCalendar* DefVal;
	static CObjectProperty Props[];
	static CPropertySet    PropSet;
	static CMMSCalendar*   HolydaysDefVal;
	static CObjectProperty HolydaysProps[];
	static CPropertySet    HolydaysPropSet;

public:
	int StartDate; //5. ��������� ���� � ���� ����� ���� � ������ �����
	CCalendarDays Days; //6. ����� ���� �������� � ���� ����� �����. ����� �������� ���������� �����, ��� ����� ����� ������ �� 10.
	CMigrationRules MigrationRules; //7. ������� ��������
	
	CMMSHolydays Holydays;

public:
	CMMSCalendar()
		{MMS_Type = MMS_Calendar; ToDestroyChildren = false;}

	CPropertySet* GetPropSet();
	virtual bool SetValue(int MMS_Index, GCString& Value);
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);

	virtual void BeautyString(CBeautyString& String, int level);
	virtual void ToString(CMMSString& String);
};

//--------------
class CMMSCalendarList : public CMMSAttributes
{
public:
	CMMSCalendarList()
		{MMS_Type = MMS_Calendars;}

	virtual const char* BeautyName() {return "���������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSCalendar;}

	virtual void ToString(CMMSString& String);
};

#endif