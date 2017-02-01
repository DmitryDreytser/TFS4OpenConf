
#ifndef MMS_BasicTypes
#define MMS_BasicTypes

#include "Declarations.h"
#include "Strings.h"

#define VAR_OFFSET(OBJ, VAR) ((int)(&(OBJ->VAR)) - (int)OBJ)

class CObjectProperty;
class CPropertySet;


class CStoredProperty
{
public:
	virtual void SetValue(GCString& Value) = 0;
	virtual GCString BeautyString() = 0;
	virtual GCString MMSString() = 0;
};

//��� ������������� ������������ ���� ����� ������ ���� ������!
class CStoredObject
{
public:
	virtual ~CStoredObject() {}

	virtual CPropertySet* GetPropSet() {return NULL;};
	virtual bool SetValue(GCString& Name, GCString& Value);
	virtual bool SetValue(int MMS_Index, GCString& Value);
	virtual void BeautyString(CBeautyString& String, int level);
	virtual void ToString(CMMSString& String);
};

class CObjectProperty
{
public:
	const char* Name;
	int MMS_Index;
	enum {
		t_object,    //������, ������� � ��� ���������� �� '{'
		t_subobject, //������ ������ gcomp (�������� ��� ���������)
		t_prop,      //�������� ���� CStoredProperty, ��� ����������� �����
		t_string, t_quotstring, 
		t_bool, t_int, t_uint
	} Type;
	int Offset; //offset from beginning of object, in bytes
};


class CPropertySet
{
private:
	CObjectProperty* Propertys;
	CStoredObject* DefaultValues;
public:
	int nProps;
	int MaxMMS_Index;

private:
	void add_flags(CBeautyString& String, int level, const char* id, unsigned int Flags, char* FlagNames[]);
public:
	CPropertySet(CObjectProperty* Props, CStoredObject* Defaults);
	~CPropertySet();

	CObjectProperty& operator[] (int i) { return Propertys[i]; };
	void* GetObjProp(void* Object, int i);
	
	int FindByName(const char* Name);
	int FindByMMSIndex(int Index);
	void SetValue(void* Object, int i, GCString& Value, bool Unqoute = true);
	bool SetByMMSIndex(void* Object, int MMS_Index, GCString& Value, bool Unqoute = true);
	
	void BeautyString(CBeautyString& String, int level, const void* Object, int i);
	void ToString(CMMSString& String, const void* Object, int i, bool AddComma);
};

//������
class CStoredString : public CStoredProperty
{
private:
	GCString Value;

public:
	CStoredString() {}
	GCString& operator=(GCString& NewVal) { Value = NewVal; return Value; }
	GCString& operator()() { return Value; }
	operator GCString() {return Value;}
	
	virtual void SetValue(GCString& NewVal) {Value = NewVal;}
	
	virtual GCString BeautyString() {return Value;}
	virtual GCString MMSString() {return Value;}
};

// ���������� ���
class CStoredBool : public CStoredProperty
{
private:
	bool Value;

public:
	CStoredBool() { Value = false; }
	bool operator=(bool NewVal) { Value = NewVal; return Value; }
	bool operator()() { return Value; }
	operator bool() {return Value;}
	
	virtual void SetValue(GCString& Value);
	
	virtual GCString BeautyString();
	virtual GCString MMSString();
};

// ���������� ��� ��� ����� "����������" � ���������� ������
class CFontBold : public CStoredProperty
{
private:
	bool Value;
	bool Needed;

public:
	CFontBold() { Value = false; Needed = true; };
	bool operator=(bool NewVal) { Value = NewVal; return Value; };
	bool operator()() { return Value; };

	void UnNeeded() { Needed = false; }
	
	virtual void SetValue(GCString& Value);
	
	virtual GCString BeautyString();
	virtual GCString MMSString();
};

//������ �� ������ ����������
class CMMSObjRef : public CStoredProperty
{
public:
	int iTypeObjectID;
	GCString sTypeObjectID;

public:
	CMMSObjRef() { iTypeObjectID = 0; };
	
	virtual void SetValue(GCString& Value);
	
	virtual GCString BeautyString();
	virtual GCString MMSString();
};

//����� � �������� �������
class CStoredBitSet : public CStoredProperty
{
private:
	char** BitNames;
	unsigned int Value;

public:
	CStoredBitSet() {BitNames = NULL;}
	void SetTable(char** Names) {BitNames = Names;}

	int BitByName(const char* BitName);
	bool BitValue(int i);

	unsigned int operator=(unsigned int NewVal) { Value = NewVal; return Value; };
	virtual void SetValue(GCString& Value);

	virtual GCString BeautyString();
	virtual GCString MMSString();
};

//����� ��������� ��������
class CStoredSet : public CStoredProperty
{
public:
	typedef struct {
		int value;
		char* representation;
	} TSetPair; //��� ��� ������ ������� ������������

private:
	TSetPair* ValTable;
	int Value;

public:
	CStoredSet() {ValTable = NULL; Value = 0;}
	CStoredSet(int NewValue) {Value = NewValue;}
	void SetTable(TSetPair* aValTable) {ValTable = aValTable;}

	virtual void SetValue(GCString& NewValue);

	virtual GCString BeautyString();
	virtual GCString MMSString();
};

//�����, ������������ ���
class CMMSTypeLetter : public CStoredProperty
{
public:
	GCString TypeLetter;
	bool Numeric;

private:
	typedef struct {
		char letter;
		char* type;
	} TTypeTable;
	static struct TTypeTable type_table[];

public:
	CMMSTypeLetter() {TypeLetter = 'U'; Numeric = false;}

	virtual void SetValue(GCString& Value);

	virtual GCString BeautyString();
	virtual GCString MMSString();
	GCString AsNumber();
};

//��� ��������
class CMMSAttributeType : public CStoredObject
{
public:
	CMMSTypeLetter TypeLetter;
	int Length;
	int Precision; //�������� (��� �����)
	CMMSObjRef TypeObjectID;

	bool NeedType; //��� ��������� ���������� ����, ��� ��� �� �����

private:
	static CObjectProperty Props[];
	static CPropertySet PropSet;

public:
	CMMSAttributeType() { Length = Precision = 0; NeedType = true; };
	void SetNumeric() {TypeLetter.Numeric = true;}
	CPropertySet* GetPropSet() {return &PropSet;};
	virtual void BeautyString(CBeautyString& String, int level);
};

//�����, ������������ ������� ���������������
class CMigrationArea : public CStoredProperty
{
public:
	GCString Letter;

	CMigrationArea() { Letter = 'W'; };
	virtual void SetValue(GCString& Value);
	virtual GCString BeautyString();
	virtual GCString MMSString();
};

//�����, ������������ ������������� ��������
class CPeriod : public CStoredProperty
{
public:
	GCString PeriodLetter;

	CPeriod() { PeriodLetter = ' '; };
	virtual void SetValue(GCString& Value);
	virtual GCString BeautyString();
	virtual GCString MMSString();
};

#endif