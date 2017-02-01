
%{
	#include <stdio.h>
	#include "MMS.h"
	
	#define YYSTYPE MMS_StackValue

	int MMS_lex(YYSTYPE *lvalp, FILE *File);
	void MMS_error (FILE *File, CMMSObject** ParserResult, char const * ErrString);
%}


%token TEXTUAL_ID
%token NUMERIC_ID
%token QUOTED_STRING
%token TOK_ContainerContents
%token TOK_DialogForm
%token TOK_MainDataContDef
%token TOK_TaskItem
%token TOK_Consts
%token TOK_SbCnts
%token TOK_GenJrnlFldDef
%token TOK_DocSelRefObj
%token TOK_DocNumDef
%token TOK_Documents
%token TOK_DocumentStreams
%token TOK_Registers
%token TOK_ReportList
%token TOK_Journalisters
%token TOK_EnumList
%token TOK_CalcJournals
%token TOK_Calendars
%token TOK_CalcAlgorithms
%token TOK_RecalcRules
%token TOK_Groups
%token TOK_Buh
%token TOK_AccParams
%token TOK_Plans
%token TOK_Accounts
%token TOK_ProvParams
%token TOK_OperParams
%token TOK_SbKind
%token TOK_TypOpersDef
%token TOK_CorrProvsDef
%token TOK_ProvHardFldDef
%token TOK_OperJournal
%token TOK_FormList


%pure_parser
%parse-param {FILE *File}
%lex-param {FILE *File}
%parse-param {CMMSObject** ParserResult}

%name-prefix = "MMS_"
%debug

%% /* Grammar rules and actions follow.  */


mms: '{' object_list '}'
{
	CMMS* pMMS = new CMMS($2.pList);
	*ParserResult = (CMMSObject*)pMMS;
	delete $2.pList;
}
| '{' TOK_ContainerContents ',' object_list '}'
{
	*ParserResult = (CMMSObject*)$4.pList;
}
| '{' TOK_ContainerContents '}'
{
	*ParserResult = (CMMSObject*)new CMMSNodeList();
}
| '{' TOK_DialogForm ',' object_list '}'
{
	*ParserResult = (CMMSObject*) new CMMSObjectWithProps($2.String, CString(""), $4.pList);
	(*ParserResult)->ID_Type = CMMSObject::IDT_OnlyTextual;
	delete $4.pList;
}
| '{' TOK_DialogForm ',' object_list '}' may_be_errors
{
	*ParserResult = (CMMSObject*) new CMMSObjectWithProps($2.String, CString(""), $4.pList);
	(*ParserResult)->ID_Type = CMMSObject::IDT_OnlyTextual;
	delete $4.pList;
	fprintf(stderr, "\t(thrash after end of dialog form)\n");
}

may_be_errors: error
| may_be_errors error

object_list: object
{
	$$.pList = new CMMSNodeList;
	$$.pList->AddNode($1.pNode);
}
| object_list ',' object
{
	$$ = $1;
	$$.pList->AddNode($3.pNode);
}

object: '{' TEXTUAL_ID properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSObjectWithProps($2.String, CString(""), $3.pList);
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
	if( $3.pList!= NULL ) delete $3.pList;
}
| '{' NUMERIC_ID '}'
{
	$$.pNode = new CMMSObject(CString(), $2.String);
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyNumeric;
}
| '{' NUMERIC_ID ',' QUOTED_STRING properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSObjectWithProps($4.String, $2.String, $5.pList);
	if( $5.pList != NULL ) delete $5.pList;
}
| '{' NUMERIC_ID ',' object properties '}'
{
	if( $5.pList == NULL ) $5.pList = new CMMSNodeList;
	$5.pList->AddHead($4.pNode);
	$$.pNode = (CMMSObject*) new CMMSObjectWithProps(CString(""), $2.String, $5.pList);
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyNumeric;
	delete $5.pList;
}
| '{' properties '}'
{
	if( $2.pList == NULL )
		$$.pNode = (CMMSObject*)new CMMSObject;
	else
	{
		$$.pNode = (CMMSObject*) new CMMSObjectWithProps($2.pList);
		delete $2.pList;
	}
}
///////////////////////////////////////////////////////////////////
/////////////////  типизированные объекты  ////////////////////////
///////////////////////////////////////////////////////////////////
//MainDataContDef
| '{' TOK_MainDataContDef ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING '}'
{
	$$.pNode = (CMMSObject*) new CMMSDescr($2.String, $4.String, $6.String, $8.String);
}
//TaskItem
| '{' TOK_TaskItem properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_TaskItem, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
//Константы
| '{' TOK_Consts properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_Consts, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
//Справочники
| '{' TOK_SbCnts '}'
{
	$$.pNode = (CMMSObject*) new CMMSSbCnts($2.String, NULL);
}
| '{' TOK_SbCnts ',' sbcnts_list '}'
{
	$$.pNode = (CMMSObject*) new CMMSSbCnts($2.String, $4.pList);
	delete $4.pList;
}
//Общие поля документов
| '{' TOK_GenJrnlFldDef properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSGenJrnlFldDef($2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
//Графы отбора документов в журналах
| '{' TOK_DocSelRefObj properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSDocSelRefObj($2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
//Нумераторы
| '{' TOK_DocNumDef properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSDocNumDef($2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
//Документы
| '{' TOK_Documents '}'
{
	$$.pNode = (CMMSObject*) new CMMSDocuments($2.String, NULL);
}
| '{' TOK_Documents ',' doc_list '}'
{
	$$.pNode = (CMMSObject*) new CMMSDocuments($2.String, $4.pList);
	delete $4.pList;
}
//Регистры
| '{' TOK_Registers properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_Registers, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
//Последовательности документов
| '{' TOK_DocumentStreams '}'
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_DocumentStreams, $2.String, NULL);
	$$.pNode->Type = MMS_DocumentStreams;
}
| '{' TOK_DocumentStreams ',' doc_stream_list '}'
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_DocumentStreams, $2.String, $4.pList);
	delete $4.pList;
}
//Отчеты и обработки
| '{' TOK_ReportList '}'
{
	$$.pNode = (CMMSObject*) new CMMSReportList($2.String, NULL);
}
| '{' TOK_ReportList ',' report_list '}'
{
	$$.pNode = (CMMSObject*) new CMMSReportList($2.String, $4.pList);
	delete $4.pList;
}
//Журналы документов
| '{' TOK_Journalisters '}'
{
	$$.pNode = (CMMSObject*) new CMMSJournalisters($2.String, NULL);
}
| '{' TOK_Journalisters ',' journal_list '}'
{
	$$.pNode = (CMMSObject*) new CMMSJournalisters($2.String, $4.pList);
	delete $4.pList;
}
//Перечисления
| '{' TOK_EnumList properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_EnumList, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
//Журналы расчетов
| '{' TOK_CalcJournals '}'
{
	$$.pNode = (CMMSObject*) new CMMSCalcJournals($2.String, NULL);
}
| '{' TOK_CalcJournals ',' calcjournal_list '}'
{
	$$.pNode = (CMMSObject*) new CMMSCalcJournals($2.String, $4.pList);
	delete $4.pList;
}
//Календари
| '{' TOK_Calendars properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_Calendars, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
//Алгоритмы расчета
| '{' TOK_CalcAlgorithms '}'
{
	$$.pNode = (CMMSObject*) new CMMSCaclAlgorithms($2.String, NULL);
}
| '{' TOK_CalcAlgorithms ',' calcalg_list '}'
{
	$$.pNode = (CMMSObject*) new CMMSCaclAlgorithms($2.String, $4.pList);
	delete $4.pList;
}
//Правила пересчета
| '{' TOK_RecalcRules properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_RecalcRules, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
//Группы расчетов
| '{' TOK_Groups properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_Groups, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
//Параметры бухгалтерии
| '{' TOK_Buh '}'
{
	$$.pNode = (CMMSObject*) new CMMSObject($2.String, $2.String);
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
}
| '{' TOK_Buh ',' '{' buh_params '}' '}'
{
	$$.pNode = $5.pNode;
	$$.pNode->sID = $2.String;
}


/////////////////////////////////
/////  subcontos ////////////////
/////////////////////////////////
sbcnts_list: subconto
{
	$$.pList = new CMMSNodeList;
	$$.pList->AddNode($1.pNode);
}
| sbcnts_list ',' subconto
{
	$$ = $1;
	$$.pList->AddNode($3.pNode);
}

subconto: '{' NUMERIC_ID ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSSbCnt(
		$4.String, 
		$2.String, 
		$6.String, 
		$8.String,
		$10.pList);
	delete $10.pList;
}

/////////////////////////////////
/////  documents ////////////////
/////////////////////////////////
doc_list: document
{
	$$.pList = new CMMSNodeList;
	$$.pList->AddNode($1.pNode);
}
| doc_list ',' document
{
	$$ = $1;
	$$.pList->AddNode($3.pNode);
}

document: '{' NUMERIC_ID ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSDocument(
		$4.String, 
		$2.String, 
		$6.String, 
		$8.String,
		$10.pList);
	delete $10.pList;
}

////////////////////////////////////////
/////  document streams  ///////////////
////////////////////////////////////////
doc_stream_list: doc_stream
{
	$$.pList = new CMMSNodeList;
	$$.pList->AddNode($1.pNode);
}
| doc_stream_list ',' doc_stream
{
	$$ = $1;
	$$.pList->AddNode($3.pNode);
}

doc_stream: '{' NUMERIC_ID ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' ds_reg_props ',' ds_doc_props '}'
{
	$$.pNode = (CMMSObject*) new CMMSDocStream($4.String, $2.String, 
		$6.String, $8.String, 
		$10.String, $12.String,
		$14.pNode, $16.pNode);
}

ds_reg_props: '{' TOK_Registers '}'
{
	$$.pNode = (CMMSObject*) new CMMSObjectWithProps($2.String, $2.String);
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
}
| '{' TOK_Registers ',' properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSObjectWithProps($2.String, $2.String, $4.pList);
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
	delete $4.pList;
}

ds_doc_props: '{' TOK_Documents '}'
{
	$$.pNode = (CMMSObject*) new CMMSObjectWithProps($2.String, $2.String);
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
}
| '{' TOK_Documents ',' properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSObjectWithProps($2.String, $2.String, $4.pList);
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
	delete $4.pList;
}


/////////////////////////////////
/////  reports  /////////////////
/////////////////////////////////
report_list: report
{
	$$.pList = new CMMSNodeList;
	$$.pList->AddNode($1.pNode);
}
| report_list: report_list ',' report
{
	$$ = $1;
	$$.pList->AddNode($3.pNode);
}

report: '{' NUMERIC_ID ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING '}'
{
	$$.pNode = (CMMSObject*) new CMMSReport(
		$4.String, 
		$2.String, 
		$6.String, 
		$8.String);
}


/////////////////////////////////
/////  journals  ////////////////
/////////////////////////////////
journal_list: journal
{
	$$.pList = new CMMSNodeList;
	$$.pList->AddNode($1.pNode);
}
| journal_list: journal_list ',' journal
{
	$$ = $1;
	$$.pList->AddNode($3.pNode);
}

journal: '{' NUMERIC_ID ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSJournalister(
		$4.String, 
		$2.String, 
		$6.String, 
		$8.String,
		$10.pList);
	delete $10.pList;
}

/////////////////////////////////
/////  calc journals  ///////////
/////////////////////////////////
calcjournal_list: calcjournal
{
	$$.pList = new CMMSNodeList;
	$$.pList->AddNode($1.pNode);
}
| calcjournal_list: calcjournal_list ',' calcjournal
{
	$$ = $1;
	$$.pList->AddNode($3.pNode);
}

calcjournal: '{' NUMERIC_ID ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSCalcJournal(
		$4.String, 
		$2.String, 
		$6.String, 
		$8.String,
		$10.pList);
	delete $10.pList;
}

/////////////////////////////////
/////  calc algorithms //////////
/////////////////////////////////
calcalg_list: calcalg
{
	$$.pList = new CMMSNodeList;
	$$.pList->AddNode($1.pNode);
}
| calcalg_list: calcalg_list ',' calcalg
{
	$$ = $1;
	$$.pList->AddNode($3.pNode);
}

calcalg: '{' NUMERIC_ID ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSCaclAlgorithm(
		$4.String, 
		$2.String, 
		$6.String, 
		$8.String,
		$10.pList);
	delete $10.pList;
}

///////////////////////////////////////////////////////////////////////
//////////  Параметры бухгалтерии  ////////////////////////////////////
///////////////////////////////////////////////////////////////////////
buh_params: NUMERIC_ID
{
	$$.pNode = (CMMSObject*) new CMMSBuh(CString("Buh"), $1.String);
}
| buh_params ',' buh_object
{
	$$.pNode = $1.pNode;
	$1.pNode->AddProperty($3.pNode);
}

////////////////////////////////////////////////////
//  Объект бухгалтерии
////////////////////////////////////////////////////
buh_object : property
{
	$$.pNode = $1.pNode;
}
| '{' TOK_AccParams properties '}' 
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_AccParams, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
| '{' TOK_Plans '}' 
{
	$$.pNode = (CMMSObject*) new CMMSObjectWithProps($2.String, CString(), NULL);
	$$.pNode->Type = MMS_Plans;
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
}
| '{' TOK_Plans ',' AccPlanList '}' 
{
	$$.pNode = (CMMSObject*) new CMMSAccountPlans($2.String, $4.pList);
	delete $4.pList;
}
| '{' TOK_ProvParams properties '}' 
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_ProvParams, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
| '{' TOK_OperParams properties '}' 
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_OperParams, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
| '{' TOK_SbKind properties '}' 
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_SbKind, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
| '{' TOK_TypOpersDef properties '}' 
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_TypOpersDef, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
| '{' TOK_CorrProvsDef properties '}' 
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_CorrProvsDef, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
| '{' TOK_ProvHardFldDef properties '}' 
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_ProvHardFldDef, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}
| '{' TOK_OperJournal properties '}' 
{
	$$.pNode = (CMMSObject*) new CMMSMetadataPart(MMS_OperJournal, $2.String, $3.pList);
	if( $3.pList != NULL ) delete $3.pList;
}

///////////////////////////////////////////////////////////////////////
//// Планы счетов
///////////////////////////////////////////////////////////////////////
AccPlanList: AccPlan
{
	$$.pList = new CMMSNodeList;
	$$.pList->AddNode($1.pNode);
}
|AccPlanList ',' AccPlan
{
	$$.pList = $1.pList;
	$$.pList->AddNode($3.pNode);
}

//план счетов 10011
AccPlan: '{' NUMERIC_ID ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' AccList '}'
{
	$$.pNode = (CMMSObject*) new CMMSAccountPlan($4.String, $2.String, $6.String, $8.String, 
		$10.String, $12.String, $14.pNode);
}
//план счетов 10009 - первая маска счёта пустая
| '{' NUMERIC_ID ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' AccList '}'
{
	$$.pNode = (CMMSObject*) new CMMSAccountPlan($4.String, $2.String, $6.String, $8.String, 
		CString(""), $10.String, $12.pNode);
}

AccList: '{' TOK_Accounts '}'
{
	$$.pNode = (CMMSObject*) new CMMSObjectWithProps($2.String, CString(), NULL);
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
}
|'{' TOK_Accounts ',' Accounts '}'
{
	$$.pNode = (CMMSObject*) new CMMSObjectWithProps($2.String, CString(), $4.pList);
	$$.pNode->ID_Type = CMMSObject::IDT_OnlyTextual;
	if( $4.pList != NULL ) delete $4.pList;
}

///////////////////////////////////////////////////////////////////////
////  Счета
///////////////////////////////////////////////////////////////////////
Accounts: Account
{
	$$.pList = new CMMSNodeList();
	$$.pList->AddNode($1.pNode);
}
|Accounts ',' Account
{
	$$.pList = $1.pList;
	$$.pList->AddNode($3.pNode);
}

Account: '{' NUMERIC_ID ',' QUOTED_STRING ',' QUOTED_STRING ',' 
QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' 
QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING ',' QUOTED_STRING properties '}'
{
	$$.pNode = (CMMSObject*) new CMMSAccount($4.String, $2.String, $6.String, $8.String,
		$10.String, $12.String, $14.String, 
		$16.String, $18.String, $20.String, $21.pList);
	if( $21.pList != NULL ) delete $21.pList;
}


/////////////////////////////////
/////  untyped properties ///////
/////////////////////////////////
properties: {$$.pList = NULL;}
| prop_list {$$.pList = $1.pList;} 
| ',' prop_list {$$.pList = $2.pList;} 

prop_list: property
{
	$$.pList = new CMMSNodeList;
	$$.pList->AddNode($1.pNode);
}
|prop_list ',' property
{
	$$ = $1;
	$$.pList->AddNode($3.pNode);
}

property: QUOTED_STRING
{
	$$.pNode = (CMMSObject*) new CMMSNode(MMS_Property, $1.String, CString());
}
|object
{
	$$ = $1;
}

%%


/* The lexical analyzer returns quoted string (without quotes) or single token.
   It skips all blanks and tabs, and returns 0 for end-of-input. 
*/

typedef struct YYLTYPE
{
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} YYLTYPE;

static YYLTYPE location = {1, 1, 1, 1};
static int MMS_PropNum = 1;

static struct{
	char* strID;
	int intID;
} MapPairs[] = {
	{"Container.Contents", TOK_ContainerContents},
	{"Dialogs", TOK_DialogForm},
	{"MainDataContDef", TOK_MainDataContDef},
	{"TaskItem", TOK_TaskItem},
	{"Consts", TOK_Consts},
	{"SbCnts", TOK_SbCnts},
	{"GenJrnlFldDef", TOK_GenJrnlFldDef},
	{"DocSelRefObj", TOK_DocSelRefObj},
	{"DocNumDef", TOK_DocNumDef},
	{"Documents", TOK_Documents},
	{"Document Streams", TOK_DocumentStreams},
	{"Registers", TOK_Registers},
	{"ReportList", TOK_ReportList},
	{"Journalisters", TOK_Journalisters},
	{"EnumList", TOK_EnumList},
	{"CJ", TOK_CalcJournals},
	{"Calendars", TOK_Calendars},
	{"Algorithms", TOK_CalcAlgorithms},
	{"RecalcRules", TOK_RecalcRules},
	{"Groups", TOK_Groups},
	{"CalcVars", TOK_ReportList},
	{"Buh", TOK_Buh},
	{"AccParams", TOK_AccParams},
	{"Plans", TOK_Plans},
	{"Accounts", TOK_Accounts},
	{"ProvParams", TOK_ProvParams},
	{"OperParams", TOK_OperParams},
	//{"Form", TOK_FormList},
	{"SbKind", TOK_SbKind},
	{"TypOpersDef", TOK_TypOpersDef},
	{"CorrProvsDef", TOK_CorrProvsDef},
	{"ProvHardFldDef", TOK_ProvHardFldDef},
	{"OperJournal", TOK_OperJournal},
	{NULL, 0}};
static CMapStringToOb Map;

static CString ParsedObject; //для сообщений об ошибках

void MMS_InitParser(CString& aParsedObject)
{
	ParsedObject = aParsedObject;

	location.first_line = 1;
	location.first_column = 1;
	location.last_line = 1;
	location.last_column = 1;

	if( Map.GetCount() == 0 )
	{
		for( int i = 0; MapPairs[i].strID != NULL; i++ )
			Map.SetAt(MapPairs[i].strID, (CObject*)MapPairs[i].intID);
	}
}

int GetTokenType(CString& token)
{
	char *ptr;
	CObject* token_id;

	if( MMS_PropNum > 0 ) return QUOTED_STRING;

	ptr = (LPSTR)(LPCSTR)token;
	if( Map.Lookup(ptr, token_id) ) return (int)token_id;

	size_t len = token.GetLength();
	if( len == 0 ) return TEXTUAL_ID;
	if( token[0] == '0' ) return TEXTUAL_ID; //числовые идентификаторы с 0 не начинаются.
	if( strspn(token, "0123456789") == len ) return NUMERIC_ID;
	return TEXTUAL_ID;
}

bool SkipSpaces(FILE* File, YYLTYPE *llocp)
{
	while( !feof(File) )
	{
		int c = fgetc(File);
		
		if( c == '\n' )
		{
			llocp->first_line++;
			llocp->first_column = 1;
			continue;
		}
		if( c != ' ' && c != '\t' && c != '\n' && c != '\r' )
		{
			ungetc(c, File);
			return true;
		}
		if( c != '\r')
		{
			llocp->first_column++;
		}
	}
	return false;
}

int MMS_lex (YYSTYPE *lvalp, FILE *File)
{
	char c;

	if( feof(File) ) return 0;
	if( !SkipSpaces(File, &location) ) return 0;

	c = fgetc(File);
	location.first_column++;

	if( c != '"' )
	{
		if( c == '{' )
			MMS_PropNum = 0;
		else
			MMS_PropNum++;
		return c;
	}
	
	CString& token = lvalp->String;
	token = "";
	int state = 0; // 0 - внутри строки; 1 - попалась кавычка
	while( !feof(File) ) 
	{
		c = fgetc(File);

		switch( state )
		{
		case 0:
			if( c == '"' )
				state = 1;
			else
				token += c;
			break;
		case 1:
			if( c == '"' )
			{
				token += "\"\""; // оставим двойную кавычку как есть - не будем менять на одну
				state = 0;
			}
			else
			{
				ungetc(c, File);
				int tok_t = GetTokenType(token);
				MMS_PropNum++;
				return tok_t;
			}
		}

		location.first_column++;
	}
		
	return 0;
}


// Called by yyparse on error.
void MMS_error (FILE *File, CMMSObject** ParserResult, char const *s)
{
	printf ("%s: %s - Line %i Column %i\n", ParsedObject, s, location.first_line, location.first_column);
}

