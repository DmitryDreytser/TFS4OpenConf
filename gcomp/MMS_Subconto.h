#ifndef MMS_Subconto_H
#define MMS_Subconto_H

#include "MMS_Basic.h"

////////////////////////////////////////////////////////////
//// �������� ������������  ////////////////////////////////
////////////////////////////////////////////////////////////
class CSbCntParam : public CMMSObjectAttribute
{
public:
	CStoredBool NotNegative; //1 - ���������������, 0 - ��� (��� �����)
	CStoredBool DivideTriades; //1 - ��������� ������, 0 - ���
	CStoredBool Periodical; //1 - �������������, 0 - ���
	CStoredBool ForElement; //1 - ��� ��������, 0 - ���
	CStoredBool ForGroup;   //1 - ��� ������, 0 - ���
	CStoredBool Sorting; //1 - ���������� �� ���������, 0 - ���
	CStoredBool HistManualChanged; //1 - ������ ���������, 0 - ��� (��� �������������)
	CStoredBool HistChangedByDocs; //1 - ���������� �����������, 0 - ��� (��� �������������)
	CStoredBool Selection; //1 - ����� �� ���������, 0 - ���

private:
	static CSbCntParam* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CSbCntParam() {
		ID_Type = IDT_BothIDs;
		NotNegative = 0;
		DivideTriades = 0;
		Periodical = 0;
		ForElement = 0;
		ForGroup = 0;
		Sorting = 0;
		HistManualChanged = 0;
		HistChangedByDocs = 0;
		Selection = 0;
	};

	CPropertySet* GetPropSet() {return &PropSet;};
};

class CSbCntParams : public CMMSAttributes
{
public:
	CSbCntParams() {MMS_Type = MMS_SbCntParams; }

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CSbCntParam;}
	virtual const char* BeautyName() {return "��������";}
};

////////////////////////////////////////////////////////////
//// �����������  //////////////////////////////////////////
////////////////////////////////////////////////////////////
class CMMSSbCnt : public CMMSObjectAttribute
{
public:
	CMMSObjRef Owner; //���������� - ��������. 0 - �� ��������
	int CodeLength; //����� ����
	CStoredSet CodeSeries; //1 - �� ��� �����������, 2 - � �������� ����������
	CStoredSet CodeType; //��� ���� 1 - ���������, 2 - ��������
	CStoredSet AutoNumeration; //2 - �������������� ���������, 1 - ��������
	int NameLength; //����� ������������
	CStoredSet BasicRepresentation; //�������� ������������� 1 - � ���� ����, 2 - � ���� ������������
	CStoredSet EditWay; //������ �������������� 0 - � ������, 1 - � �������, 2 - ������ ���������
	int Levels; //���������� �������
	CMMSObjRef ChoosingListForm; //������������� ����� ������ ��� ������
	CMMSObjRef MainListForm; //������������� �������� ����� ������
	CStoredBool OneForm; //1 - ���� ����� ��� �������� � ������, 0 - ������ �����
	CStoredBool UniqueCodes; //�������� ������������ 1 - ���� ���������, 0 - �� �����������
	CStoredBool GroupsOnTop; //������ ������ 1 - ������, 0 - � ����� �������

	CSbCntParams Parameters;
	CFormDescrList Forms;

	CMigrationRules MigrationRules;
	
private:
	static CMMSSbCnt* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;
	void SetUpTables();

public:
	CMMSSbCnt();

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);

public:
	CPropertySet* GetPropSet() {return &PropSet;};

	void Decompile(GCString& BaseDir, CStorage& Storage, CStorage& TypedTextStorage, CStorage& SubFolderStorage, CStorage& SubListStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& Dir, CStorage& SubFolderStorage, CStorage& SubListStorage);
};

////////////////////////////////////////////////////////////
class CMMSSbCnts : public CMMSAttributes
{
public:
	CMMSSbCnts() {MMS_Type = MMS_SbCnts; ID_Type = IDT_OnlyTextual;}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSSbCnt;}
	virtual const char* BeautyName() {return "�����������";}

	void Decompile(GCString& BaseDir, CStorage& Storage, CStorage& TypedTextStorage);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& Dir);
};

#endif