#ifndef MMS_Buh_H
#define MMS_Buh_H

#include "MMS_Basic.h"
#include "MMS_Document.h"

////////////////////////////////////////////////////////////
//// �����  ////////////////////////////////////////////////
////////////////////////////////////////////////////////////
class CAccountSubconto : public CMMSObjectAttribute
{
public:
	CStoredBool Param9;
	CStoredBool Param10;
	CMMSObjRef SbKind; //11. ��� ��������
	CStoredBool OnlyMovement; //12. ������ �������
	CStoredBool BySum; //13. ���� �� �����
	CStoredBool ByCurrencySum; //14. ���� �� �������� �����
	CStoredBool ByAmount; //15. ���� �� ����������
private:
	static CAccountSubconto* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CPropertySet* GetPropSet() {return &PropSet;};
	virtual void BeautyString(CBeautyString& String, int level);
};

class CAccountSubcontoList : public CMMSAttributes
{
public:
	CAccountSubcontoList() {sID = "AccSbCnts";}

	virtual const char*BeautyName() {return "���������";}
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CAccountSubconto;}
};

class CMMSAccount: public CMMSObject
{
public:
	GCString Name;
	GCString Param2; //��������� ���. ������ ""
	GCString Code;   //��� �����
	CStoredBool IsCurrency; //��������
	CStoredBool IsAmount;   //�������������� ����
	CStoredBool IsSingle;   //������������ ����
	CStoredBool IsGroup;    //���� � ������� �������
	CStoredSet  IsActive;   //1 - ��������; 2 - ���������; 3 - �������-���������
	CAccountSubcontoList SubcontoList;

private:
	static CMMSAccount* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMMSAccount();

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual void BeautyString(CBeautyString& String, int level);

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return &SubcontoList;}
	virtual void SetIDs(const char* Name, const char* Value);

	void Decompile(GCString& Dir, CStorage& Storage, CObjectOrdering& Order);
};

class CMMSAccountList : public CMMSAttributes
{
public:
	CMMSAccountList() {sID = "Accounts";}

	virtual const char*BeautyName() {return "�����";}

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSAccount;}
};

////////////////////////////////////////////////////////////
//// ����� ������ ///////////////////////////////////////////
////////////////////////////////////////////////////////////
class CMMSAccountPlan: public CMMSObject
{
public:
	GCString Comment;
	GCString Synonym;
	GCString AccountMask1; //����� ���� �����
	GCString AccountMask2; //��� ���� �� ��� - � �� ����
	CMMSAccountList Accounts;
	CMigrationRules Migration;
	
private:
	static CMMSAccountPlan* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;
	int AccMaskAmount;

public:
	CMMSAccountPlan();

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);

	virtual void BeautyString(CBeautyString& String, int level);
	virtual void ToString(CMMSString& String);

	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage, CObjectOrdering& Order);

	virtual void AssembleMetadata(GCString& Dir);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};

class CMMSAccountPlanList: public CMMSAttributes
{
public:
	CMMSAccountPlanList();

	virtual const char* BeautyName() { return "����� ������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSAccountPlan;}

	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);

	virtual void AssembleMetadata(GCString& Dir);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};


////////////////////////////////////////////////////////////
//// ��������� ����������� /////////////////////////////////
////////////////////////////////////////////////////////////
class CMMSTypedField : public CMMSObjectAttribute
{
public:
	CStoredBool	NonNegative;	//9.	���������������: 1 ��� 0
	CStoredBool	DivideTriades;	//10.	��������� ������: 1 ��� 0
	CStoredBool Selection;		//11.	�����
	CStoredBool Periodical;		//12.	�������������

private:
	static CMMSTypedField* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CPropertySet* GetPropSet() {return &PropSet;};
};

class CMMSTypedDocField : public CMMSTypedField
{
private:
	static CMMSTypedDocField* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CPropertySet* GetPropSet() {return &PropSet;};
};

class CMMSAccountFieldList : public CMMSAttributes
{
public:
	CMMSAccountFieldList() {MMS_Type = MMS_AccParams;}

	virtual const char* BeautyName() { return "��������� �����"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSTypedField;}
};

//----------------------------------------------------
class CMMSEntryFieldList : public CMMSAttributes
{
public:
	CMMSEntryFieldList() {MMS_Type = MMS_ProvParams;}

	virtual const char* BeautyName() { return "��������� ��������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSTypedDocField;}
};

//----------------------------------------------------
class CMMSOperFieldList : public CMMSAttributes
{
public:
	CMMSOperFieldList() {MMS_Type = MMS_OperParams;}

	virtual const char* BeautyName() { return "��������� ��������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSTypedDocField;}
};

//----------------------------------------------------
class CMMSBuhSbKindRepr : public CMMSTypedObject
{
public:
	CMMSObjRef Field; //1.	������ �� ���� �������
	GCString Name;	//2.	���������
	CStoredBool FromNewLine;	//3.	� ����� ������
private:
	static CMMSBuhSbKindRepr* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CPropertySet* GetPropSet() {return &PropSet;};
	virtual const char* BeautyName() {return "�������������";}
};

class CMMSBuhSbKindReprList : public CMMSAttributes
{
public:
	CMMSBuhSbKindReprList() {}

	virtual const char* BeautyName() { return "������������� ��������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSBuhSbKindRepr;}

	virtual void ToString(CMMSString& String);

};

class CMMSBuhSbKind : public CMMSObjectAttribute
{
public:
	CStoredBool	DivideTriades;	//9.	��������� ������: 1 ��� 0
	CStoredBool	NonNegative;	//10.	���������������: 1 ��� 0
	CStoredBool Selection;		//11.	�����
	CMMSObjRef Price;	//12.	�������� ����������� "����"
	CMMSObjRef CurrencyPrice;	//13.	�������� ����������� "�������� ����"
	CMMSBuhSbKindReprList Representation;	//14.	�������������
	CStoredBool FastSelection;	//15.	������� �����
	CStoredBool AllowEmpty;	//16.	���� ������ ��������

private:
	static CMMSBuhSbKind* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMMSBuhSbKind() {ToDestroyChildren = false;}

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
};

class CMMSBuhSbKindList : public CMMSAttributes
{
public:
	CMMSBuhSbKindList() {MMS_Type = MMS_SbKind;}

	virtual const char* BeautyName() { return "���� ��������"; }
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSBuhSbKind;}
};

//----------------------------------------------------
class CMMSTypOper : public CMMSSynonymedObject
{
public:
	CMigrationRules MigrationRules;

private:
	static CMMSTypOper* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMMSTypOper() {ToDestroyChildren = false;}

	CPropertySet* GetPropSet() {return &PropSet;};
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return &MigrationRules;}

	virtual void BeautyString(CBeautyString& String, int level);
};

class CMMSTypOperList : public CMMSAttributes
{
public:
	CMMSTypOperList() {MMS_Type = MMS_TypOpersDef;}

	virtual const char* BeautyName() { return "������� ��������"; }
	virtual void ToString(CMMSString& String);

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSTypOper;}
};

//----------------------------------------------------
class CMMSCorrProvsDef : public CMMSTypOper
{
};

class CMMSCorrProvsDefList : public CMMSAttributes
{
public:
	CMMSCorrProvsDefList() {MMS_Type = MMS_CorrProvsDef;}

	virtual const char* BeautyName() { return "���������� ��������"; }
	virtual void ToString(CMMSString& String);

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSCorrProvsDef;}
};

//----------------------------------------------------
class CMMSProvHardFldDefList : public CMMSAttributes
{
public:
	CMMSProvHardFldDefList() {MMS_Type = MMS_ProvHardFldDef;}

	virtual const char* BeautyName() { return "��������������� ��������� ��������"; }
	virtual void ToString(CMMSString& String);

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return new CMMSTypedDocField;}
};

class CMMSOperJournal : public CMMSJournal //CMMSSynonymedObject
{
public:
	CMMSOperJournal() {MMS_Type = NT_OperListForm;}
};

class CMMSOperJournalList: public CMMSJournalList
{
public:
	CMMSOperJournalList() {MMS_Type = MMS_OperJournal;}

	virtual const char* BeautyName() { return "������ ��������"; }
	virtual void ToString(CMMSString& String);

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{ return new CMMSOperJournal; }
};

//------------------------------------------------------
class CAccListForms : public CFormDescrList
{
public:
	CAccListForms() { sID = "�����������������"; };
	virtual const char* BeautyName() {return "����� ������ ������";}
};
class CUnknownListForms : public CFormDescrList
{
public:
	CUnknownListForms() { sID = "UnknownListForms"; };
	virtual const char* BeautyName() {return "UnknownListForms";}
};
class CProvListForms : public CFormDescrList
{
public:
	CProvListForms() { sID = "�������������������"; };
	virtual const char* BeautyName() {return "����� ������ ��������";}
};

//------------------------------------------------------
//------------------------------------------------------
class CMMSBuh: public CMMSObjectAttribute
{
public:
	//����� ����� � �������� ������������ �� ID
	CStoredSet EditWay; //5. �������������
	CMMSObjRef ChoosingListForm; //6. ������������� ����� ������ ��� ������
	CMMSObjRef MainListForm; //7. ������������� �������� ����� ������
	int AccountNameLen; //8. ����� ������������ �����
	int AccountCodeLen; //9. ����� ���� �����
	int MaxSubcontoNum; //10. ������������ ������������ ��������
	int OperCommentLen; //11. ����� ���������� ��������
	int OperSumLen; //12. ����� ����� ��������
	int OperSumPrec; //13. �������� ����� ��������
	int EntrySumLen; //14. ����� ����� ��������
	int EntrySumPrec; //15. �������� ����� ��������
	int EntryCurrencySumLen; //16. ����� �������� ����� ��������
	int EntryCurrencySumPrec; //17. �������� �������� ����� ��������
	int EntryAmountLen; //18. ����� ���������� ��������
	int EntryAmountPrec; //19. �������� ���������� ��������
	int Param20;
	int Param21;
	int Param22;
	int Param23;
	CMMSObjRef Currency_Subconto; //24. ID ����������� �����
	CMMSObjRef Currency_Rate; //25. ID ��������� "����"
	GCString Param26;
	CStoredBool SelectByOperSum; //27. ����� �� ����� ��������
	CStoredBool SelectByOperComment; //28. ����� �� ���������� ��������
	CStoredSet  CalcOperSum; //29. ������ ����� ��������: 0 - �� ������������; 1 - �� ���� ���������; 2 - �� ���� ��������� � �������� �����; 3 - �� ������ ��������; 4 - �� ������ �������� � �������� �����
	CStoredBool EnableEntrySelect; //30. ��������� ����� ��������
	int LevelAmountForSelection; //31. ���������� ������� ��� ������ �������� (0-�� ����)
	CStoredBool OperSum_DivideTriades; //32. ��������� ������ ����� ��������
	CStoredBool EntrySum_DivideTriades; //33. ��������� ������ ����� ��������
	CStoredBool EntryCurrSum_DivideTriades; //34. ��������� ������ �������� ����� ��������
	CStoredBool EntryAmount_DivideTriades; //35. ��������� ������ ���������� ��������
	CStoredBool SelectByEntrySum; //36. ����� �� ����� ��������
	CStoredBool SelectByEntryCurr; //37. ����� �� ������ ��������
	CStoredBool SelectByEntryCurrSum; //38. ����� �� �������� ����� ��������
	CStoredBool SelectByEntryAmount; //39. ����� �� ���������� ��������
	CMMSObjRef  Currency_Multiple; //40. ��� ��������� ��������� � ����� ������
	CStoredBool EnableComplexEntries; //41. ������� ��������
	CStoredBool ToChooseCalcSumMode; //42. ����� ������ ������� �����
	CStoredBool SelectEntryByDebCred; //43. ����� �������� �� ������/�������
	CStoredSet  DocOperEditMode; //44. ������������� �������� ����������: 0 - ���������; 1 - ���������; 2 - ��������� 
	CStoredBool SelectByEntryPlan; //45. ����� �� ������ ������ ��������
	CStoredBool AmountOnlyByAnalytics; //46. ���������������� ���� ������ �� ���������
	CMMSObjRef  AccountingDividor; //47. ��� ��������� �������� - ����������� �����
	CMMSObjRef  MainAccPlan; //48. ��� ��������� ����� ������
	GCString Param49; //49.
	CMMSBuhSbKindReprList Param50; //50.	������������� ����-��
	int Param51; //51.
	int Param52; //52.
	CMMSAccountFieldList AccountFields; //53.
	CMMSAccountPlanList AccountPlans; //54.
	CMMSEntryFieldList EntryFields; //55.
	CMMSOperFieldList OperFields; //56.
	CAccListForms AccListForms; //57.
	CUnknownListForms UnknownListForms; //58.
	CProvListForms ProvListForms; //59.
	CMMSBuhSbKindList SbKinds; //60.
	CMMSTypOperList TypOpers; //61. TypOpersDef
	CMMSCorrProvsDefList CorrProvsDefs; //62. CorrProvsDef
	CMMSProvHardFldDefList ProvHardFldDefs; //63. ProvHardFldDef
	CMMSOperJournalList OperJournal; //64. OperJournal

	//CFormDescrList UnknownListForms;

private:
	static CMMSBuh* DefVal;
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMMSBuh();

	CPropertySet* GetPropSet() {return &PropSet;};
	
	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1);
	virtual CMMSObject* CreateChild(const char* Name, const char* Value);
	virtual CMMSObject* AddChild(CMMSObject* Child) {return NULL;}

	virtual const char* BeautyName() { return "��������� �����������"; }
	virtual void BeautyString(CBeautyString& String, int level);
	virtual void ToString(CMMSString& String);

	void ExtractForm(GCString& Dir, CStorage& Storage, MMSObjectType StorType, MMSObjectType Type);
	void ExtractListForm(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage,
		MMSObjectType Type, CFormDescrList& ListForms);
	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage);

	virtual void AssembleMetadata(GCString& Dir);
	void ImportForm(CStorage& Storage, GCString& SrcDir, MMSObjectType StorType, MMSObjectType Type);
	void ImportListForm(CStorage& Storage, GCString& SrcDir, MMSObjectType Type, CFormDescrList& ListForms);
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir);
};

class CMMSBuhContainer : public CMMSAttributes
{
public:
	CMMSBuh Buh;

public:
	CMMSBuhContainer();

	virtual const char* BeautyName() { return "��������� �����������"; }
	virtual const char* MMSName() { return "Buh"; }

	virtual CMMSObject* CreateChild(const char* Name, int MMS_Index = -1)
		{return &Buh;}
	virtual CMMSObject* AddChild(CMMSObject* Child) {return NULL;}

	virtual void AssembleMetadata(GCString& Dir);

	void Decompile(GCString& Dir, CStorage& Storage, CStorage& TypedTextStorage)
		{Buh.Decompile(Dir, Storage, TypedTextStorage);}
	void Compile(CStorage& Storage, CStorage& TypedTextStorage, GCString& SrcDir)
		{Buh.Compile(Storage, TypedTextStorage, SrcDir);}
};

#endif