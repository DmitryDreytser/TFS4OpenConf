// TaskHelp.cpp: implementation of the CTaskHelp class.
//////////////////////////////////////////////////////////////////////

#include "Task.h"
#include "CommonFunctions.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


void CTask::HelpRu()
{
	Msg(0,"\n������: gcomp.exe <��������>\n\n���������: ");
	Msg(0,"  -h - �������� ��� ������");
	Msg(0,"  -d - ��������� ���� 1cv7.md � ����� SRC");
	Msg(0,"  -c - ������� ����� SRC � ���� 1cv7.md");
	Msg(0,"  --version - �������� ������� ������ GComp � �����");
	Msg(0,""); /*------------------------*/
	Msg(0,"�� ������ ������������ ��������� �������������� ���������");
	Msg(0,"  -q - ���������� �����. ������� ��������� ������.");
	Msg(0,"  -v - ��������� ���� ������, ��� �� ���������.");
	Msg(0,"  -vv - ��� ������ ���������.");
	Msg(0,"  -F <��������>");
	Msg(0,"  -D <�������������>");
	Msg(0,"  -DD <�������������>");
	Msg(0,"  --external-report - �������, ��� �������� � ������� ������� (.ert ������)");
	Msg(0,"  --meta-data - �������, ��� �������� � ������ ������������ (1cv7.md ������)");
	Msg(0,"  --no-order - �� ��������� ������� �������� � ������������. ����� �������� ������ ��� ������������. ��� ���������� ������� ����� ������������� � ��� �������, ��� ������������ ������� ������ ��������.");
	Msg(0,"  --no-profiles - ���������� ��� ������ ����� (������), � ������ Container.Profile");
	Msg(0,"  --no-empty-mxl - ���������� ��� ������ ������ ������� �������� ����");
	Msg(0,"  --truncate-mms - ��� ������ ������� ������� gcomp ������� ����� 'Main MetaData Stream' �� ������");
	Msg(0,"  --eng - GComp ���������� ������� ����� � ����� � ����������� ������� (������ ����� ��������� � ��������� beta)");
	Msg(0,"  --translit - GComp ���������� ������� ����� � ����� � ������������������ ������� (������ ����� ��������� � ��������� beta)");
	Msg(0,"	   * ����� --eng � --translit �� ��������� ������������ ���������� ����.");
	Msg(0,"");
	Msg(0,"  --no-defaults - ��������� ��� ��������� ����������� ��������. ��� ���� ����� ��������� ������ �� ����������, ������� ���������� �� �������� �� ���������. ����� ��������� ������ ��� ������������.");
	Msg(0,"  --no-parse-dialogs - ���������� ����� ����� ��������� As Is, ��� ����� ���� ���������. ��� ���������� ������ �������� ������������ �������������.");
	Msg(0,"  --no-version - ��� ������������ �� ����� ����������� ���� gcomp.ver � ����������� � ������ gcomp.");
	Msg(0,"  --no-empty-folders - ��� ������������ ����� ������� ������ ����� (��� SVN ������������).");
	Msg(0,"  --filter <��� �������> - ���������� ������������/����������. ��� ������� ������� ��� ���� � �������� ��� �����. ��������:");
	Msg(0,"\t�����������\\�����������");
	Msg(0,"\t�����������\\�����������\\�����������");
	Msg(0,"\t��������\\*\\����������������");
	Msg(0,"� �������� ������������ ����� ������������ ������� '\\', '/' � '.'");
	Msg(0,"  --more-subfolders - �������, ������� �� ��������� ����������� � ���� ������ mdp-�����, ����� ��������� �� ���������. ���: ���������, ������������, ����� ���� ����������, ����������, ����� ������ ����������, ������������������ ����������, ��������, ������ ��������, ������� �����������, ���������");
	Msg(0,"  --sort-rights - ������� ���������� ���������������� ���� ����� ������������� �� ���� ������� (���������, ����������, �������� � �.�.) � �� �������������� �������.");
	Msg(0,"  --sort-form-controls - ����������� �������� ���������� ���� �� ��������������. �������� ��� ��������������� ����������� �� ������� ������.");
	Msg(0,"  --no-broken-links - �� ��������� ������� ���� � �����������, ����������� �� ������������� ����������.");
	Msg(0,"  --save-all-rights - ��������� ��� ������ ���� � ����� csv ����� (��� ���������� ������������)");
	Msg(0,""); /*------------------------*/
	Msg(0,"�� ���������, ������� ������ �������������� ������ ��������.");
	Msg(0,"��� ��� ����� ������� ����������� ��������� �������:");
	Msg(0,"<����������������>\\<���������������������>");
	Msg(0,"������, ���� ������� �������� -DD, �� ��� �������� ��������� �����, ��� ������� � ����� -DD");
	Msg(0,""); /*------------------------*/
	Msg(0,"�������:");
	Msg(0," > gcomp -d");
	Msg(0,"�������� ���������� 1cv7.md � ������� SRC");
	Msg(0," > gcomp -d -D C:\\Papka");
	Msg(0,"�������� ���������� 1cv7.md � ������� C:\\Papka");
	Msg(0," > gcomp -d -F TestReport.ert -D Reports");
	Msg(0,"�������� ���������� TestReport.ert � ������� Reports\\TestReport");
	Msg(0," > gcomp -d -F TestReport.ert");
	Msg(0,"�������� ���������� TestReport.ert � ������� SRC\\TestReport");
	Msg(0," > gcomp -d --external-report");
	Msg(0,"�������� ���������� 1cv7.md � ������� SRC\\1cv7");
	Msg(0," > gcomp -c -F TestReport.ert");
	Msg(0,"������� ���� TestReport.ert �� �������� SRC\\TestReport");
	Msg(0," > gcomp -c -F TestReport.ert -DD TestReportSource");
	Msg(0,"������� ���� TestReport.ert �� �������� TestReportSource");
	Msg(0,""); /*------------------------*/
	Msg(0,"��������������: ������������ � �������� ������� ����� ������� ������ ������!!!");
	Msg(0,"������ �����������!!!");
	Msg(0,"");/*------------------------*/
	Msg(0,"����������� \"gcomp -h | more\", ��� ������������� ��������� ������, ���");
	Msg(0,"\"gcomp -h > gcomp_hlp.txt\" ��� �������� ����� � ������� ������.");
}

void CTask::HelpEn()
{
	Msg(0,"\nUsage: gcomp.exe <Parameter>\n");
	Msg(0,"Parameterss: ");
	Msg(0,"  -h - Show this help");
	Msg(0,"  -d - Decompile 1cv7.md into SRC folder");
	Msg(0,"  -c - Compile SRC folder into 1cv7.md");
	Msg(0,"  --version - show current GComp version and exit");
	Msg(0,"");/*------------------------*/
	Msg(0,"You may use this optional parameters");
	Msg(0,"  -q - Quiet mode. No messages in stdout at all.");
	Msg(0,"  -v - Verbose gcomp job.");
	Msg(0,"  -vv - Much more verbose gcomp job.");
	Msg(0,"  -F <FileName>");
	Msg(0,"  -D <Directory>");
	Msg(0,"  -DD <Directory>");
	Msg(0,"  --external-report - tell to gcomp, that the file is external report (.ert style)");
	Msg(0,"  --meta-data - tell to gcomp, that the file is metadata (1cv7.md style)");
	Msg(0,"  --no-profiles - gcomp will skip files (streams), named Container.Profile");
	Msg(0,"  --no-empty-mxl - gcomp will throw away empty mxl patterns");
	Msg(0,"  --truncate-mms - when compiling external reports gcomp will repalce original 'Main MetaData Stream' with empty copy");
	Msg(0,"  --eng - GComp will be try to create folders and files with english names (beta state)");
	Msg(0,"  --translit - GComp will be try to create folders and files with translit names (beta state)");
	Msg(0,"		\'--eng\' and \'--translit\' options didn't check originality of result names.");
	Msg(0,"  --no-defaults - objects will be extracted with all propertys regardless of defaul values. Works only for decompile.");
	Msg(0,"  --no-version - file gcomp.ver (info about version of gcomp) will not create on decompile.");
	Msg(0,"  --no-empty-folders - empty folders will be deleted on decompile (for SVN repository).");
	Msg(0,"  --filter <ObjectName> - selective compilation/decompilation. Object name as path to folder or file. For example:");
	Msg(0,"\t�����������\\�����������");
	Msg(0,"\t�����������\\�����������\\�����������");
	Msg(0,"\t��������\\*\\����������������");
	Msg(0,"It is possible to use simbols '\\', '/' and '.' as separators");
	Msg(0,"  --more-subfolders - Objects, decompiled as one mdp-file, will be decompile in folder. This is: constants, enumerators, common document fields, numerators, document fields of selectiopn, document orders, registers, calc groups, calc rules, calendars");
	Msg(0,"  --sort-rights - user rights object willbe sorted by type (Constant, Reference, Document etc) and by object identifier.");
	Msg(0,"  --sort-form-controls - sort dialog form controls by identifier. Controls without identifier sorted by taborder.");
	Msg(0,"  --save-all-rights - save all user rights in one csv file (ignored on compile)");
	Msg(0,"");/*------------------------*/
	Msg(0,"By default external reports treated in some special way.");
	Msg(0,"When they extracted/compiled the destination/source directory formed as");
	Msg(0,"<StartDirectory>\\<FileNameWithoutExtension>");
	Msg(0,"But if you specify -DD parameter, directory name will be");
	Msg(0,"leaved unchanged.");
	Msg(0,"");/*------------------------*/
	Msg(0,"For example:");
	Msg(0," > gcomp -d");
	Msg(0,"will extract contents of 1cv7.md into directory SRC");
	Msg(0," > gcomp -d -D C:\\Papka");
	Msg(0,"will extract contents of 1cv7.md into directory C:\\Papka");
	Msg(0," > gcomp -d -F TestReport.ert -D Reports");
	Msg(0,"will extract contents of TestReport.ert into directory Reports\\TestReport");
	Msg(0," > gcomp -d -F TestReport.ert");
	Msg(0,"will extract contents of TestReport.ert into directory SRC\\TestReport");
	Msg(0," > gcomp -d --external-report");
	Msg(0,"will extract contents of 1cv7.md into directory SRC\\1cv7");
	Msg(0," > gcomp -c -F TestReport.ert");
	Msg(0,"will compile file TestReport.ert from directory SRC\\TestReport");
	Msg(0," > gcomp -c -F TestReport.ert -DD TestReportSource");
	Msg(0,"will compile file TestReport.ert from directory TestReportSource");
	Msg(0,"");/*------------------------*/
	Msg(0,"Warning: decompiling into not empty directory may cause data loss!!!");
	Msg(0,"Be carefull!!!");
	Msg(0,"");/*------------------------*/
	Msg(0,"Use \"gcomp -h | more\", for paging help message, or");
	Msg(0,"\"gcomp -h > gcomp_hlp.txt\" for create help file");
}

void CTask::Help()
{
	if( lang_Eng == TaskParameters.Language )
		HelpEn();
	else
		HelpRu();

}
