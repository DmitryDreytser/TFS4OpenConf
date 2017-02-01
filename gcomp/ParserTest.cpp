
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>

#include "task.h"
#include "MMS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
  
void MMS_Test(char* FName);

int _tmain(int argc, TCHAR* argv[])
{
	char* FName = NULL;
	if( argc >= 2 ) FName = argv[1];
	MMS_Test(FName);
	//ContainerTest();

	return 0;
}


extern int MMS_debug;

void MMS_Test(char* FName)
{
	FILE *f;

	if( FName != NULL )
		f = fopen(FName, "rt");
	else
		f = stdin;

	CTime Time = CTime::GetCurrentTime();
	struct _timeb start;
	_ftime(&start);
    
	CMMS* pMMS;
	//char str[10];
	//MMS_debug = 1;
	//gets((char*)str);
	MMS_InitParser();
	//gets((char*)str);

	int RetCode = MMS_parse(f, (CMMSObject**)&pMMS);
	if( FName != NULL ) fclose(f);

	struct _timeb end;
	_ftime(&end);
	CTimeSpan ParseTime = CTime::GetCurrentTime() - Time;

	printf("Parser returns %i\n", RetCode);

	if( RetCode != 0 ) return;

	if( pMMS != NULL )
	{
		printf("%s\n", (LPCSTR)pMMS->AsString(-100));
		//gets((char*)str);
		//printf("CRC:\n{\n%s\n}\n", (LPCSTR)pMMS->AsStringCRC());
		delete pMMS;
	}

	CTimeSpan FullTime = CTime::GetCurrentTime() - Time;
	struct _timeb full;
	_ftime(&full);
	cout << "Parse takes: " << ParseTime.Format("%H:%M:%S") << ", full time - " << FullTime.Format("%H:%M:%S") << "\n";
	cout << (end.time*1000+end.millitm) - (start.time*1000+start.millitm) << ", " << (full.time*1000+full.millitm) - (start.time*1000+start.millitm) << "\n";
}


