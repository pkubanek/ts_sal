#include "globals.h"
#include "fifo.h"

// --------------------------
extern void StopTimer ();
void InitNddsSendThread();
void NddsSendThread();
void EndNddsSendThread();
extern void SendBuf (u_char *buf, int length, int typeflag, long *timestamp);
extern int  FifoDelete (FIFO_ID FifoId);
// --------------------------
extern FIFO_ID sendQueue;
int timestampnum;
// --------------------------

void InitNddsSendThread()
{
	DWORD NddsSendThreadId;
	//printf("Initializing NddsSendThread.\n");
	
	hNddsSendThread = CreateThread( 
        NULL,						// no security attributes        
        0,							// use default stack size        
        (LPTHREAD_START_ROUTINE) NddsSendThread, // thread function       
        NULL,						// argument to thread function   
        0,							// use default creation flags    
        &NddsSendThreadId);			// returns the thread identifier 
	return;
}

void NddsSendThread()
{
	DWORD evnt;
	BFU32 imageType =PANO_TYPEFLAG_CMPGREEN;
	int timetstampnum =1;
	printf("Starting NddsSendThread.\n");
	// create the events
	NddsSendEvent[NDDSSEND_END]=CreateEvent(NULL,FALSE, FALSE,"ExitNddsSendThread");
	NddsSendEvent[NDDSSEND_COMP0RED]=CreateEvent(NULL,FALSE,FALSE,"NddsSendComp0Red");
	NddsSendEvent[NDDSSEND_COMP0GREEN]=CreateEvent(NULL,FALSE,FALSE,"NddsSendComp0Green");
	NddsSendEvent[NDDSSEND_COMP0BLUE]=CreateEvent(NULL,FALSE,FALSE,"NddsSendComp0Blue");
	NddsSendEvent[NDDSSEND_COMP1RED]=CreateEvent(NULL,FALSE,FALSE,"NddsSendComp1Red");
	NddsSendEvent[NDDSSEND_COMP1GREEN]=CreateEvent(NULL,FALSE,FALSE,"NddsSendComp1Green");
	NddsSendEvent[NDDSSEND_COMP1BLUE]=CreateEvent(NULL,FALSE,FALSE,"NddsSendComp1Blue");
	NddsSendEvent[NDDSSEND_COMP0OLD]=CreateEvent(NULL,FALSE,FALSE,"NddsSendComp0Old");
	NddsSendEvent[NDDSSEND_COMP1OLD]=CreateEvent(NULL,FALSE,FALSE,"NddsSendComp1Old");
	NddsSendEvent[NDDSSEND_RAWIMAGE]=CreateEvent(NULL,FALSE,FALSE,"NddsSendRawImage");
	NddsSendEvent[NDDSSEND_RGBIMAGE]=CreateEvent(NULL,FALSE,FALSE,"NddsSenndRGBImage");

	//begin the main loop waiting for buffers to send
	while (1)
	{
		evnt= WaitForMultipleObjects(11,NddsSendEvent, FALSE, INFINITE)-WAIT_OBJECT_0;
		
		switch (evnt)
		{
		case NDDSSEND_END:
			return;
			
		case NDDSSEND_RAWIMAGE:
			SendBuf((unsigned char*)RawImageBuf,RAWIMSIZE,PANO_TYPEFLAG_RAW,LastTimestamp[0]);
			break;
		case NDDSSEND_RGBIMAGE:
			if (OldRGBColor)
				SendBuf(RGBOldBufs[0],RGBIMSIZE,PANO_TYPEFLAG_RGB,LastTimestamp[0]);
			else
			{
				SendBuf(RGBImageBufs[0],RGBIMWIDTH*RGBIMWIDTH*2,PANO_TYPEFLAG_RED,LastTimestamp[0]);
				SendBuf(RGBImageBufs[1],RGBIMWIDTH*RGBIMWIDTH*2,PANO_TYPEFLAG_GREEN,LastTimestamp[0]);
				SendBuf(RGBImageBufs[2],RGBIMWIDTH*RGBIMWIDTH*2,PANO_TYPEFLAG_BLUE,LastTimestamp[0]);
			}
			break;
		case NDDSSEND_COMP0RED:
			timestampnum=0;
			imageType=PANO_TYPEFLAG_CMPRED;
			goto CompSend;
		case NDDSSEND_COMP0GREEN:
			timestampnum=0;
			goto CompSend;
		case NDDSSEND_COMP0BLUE:
			timestampnum=0;
		case NDDSSEND_COMP1BLUE:
			imageType=PANO_TYPEFLAG_CMPBLUE;
			goto CompSend;
		case NDDSSEND_COMP1RED:
			imageType=PANO_TYPEFLAG_CMPRED;
		case NDDSSEND_COMP1GREEN:
CompSend:	if (WiImageBufs[evnt-NDDSSEND_COMP0RED]->Size==0) printf("CmpImage had size 0.\n");
			else 
			{
				//printf("Sending buffer %d, of %d\n",evnt-NDDSSEND_COMP0RED,
				//	WiImageBufs[evnt-NDDSSEND_COMP0RED]->Size);
				SendBuf(WiImageBufs[evnt-NDDSSEND_COMP0RED]->CmpData,
							WiImageBufs[evnt-NDDSSEND_COMP0RED]->Size,
							imageType,LastTimestamp[timestampnum]);
			}
			break;
		// these are the old true rgb buffers, being replaced with the above 12bit colors.
		case NDDSSEND_COMP0OLD:
			timestampnum=0;
		case NDDSSEND_COMP1OLD:
			if (WiOldBufs[evnt-NDDSSEND_COMP0OLD]->Size==0) printf("CmpImage had size 0.\n");
			else 
			{
			//	printf("Sending buffer %d, of %d.\n",evnt-NDDSSEND_COMP0OLD,
			//		WiOldBufs[evnt-NDDSSEND_COMP0OLD]->Size);
				SendBuf(WiOldBufs[evnt-NDDSSEND_COMP0OLD]->CmpData,
							WiOldBufs[evnt-NDDSSEND_COMP0OLD]->Size,
							PANO_TYPEFLAG_IMAGE,LastTimestamp[timestampnum]);
			}
			break;
		}		
	}
	return;
}

void EndNddsSendThread()
{
	DWORD returnValue;

	Sleep(3000);
	SetEvent(NddsSendEvent[NDDSSEND_END]);
	returnValue = WaitForSingleObject(hNddsSendThread,INFINITE)-WAIT_OBJECT_0;
	if (returnValue)
	{
		printf ("Wait for thread to complete failed:%d.\n",returnValue-WAIT_OBJECT_0);
	}
	printf("NddsSendThread ended.\n");

	//Do some close down work here at the end.
	Sleep(2000);
	StopTimer();
	FifoDelete(sendQueue);
	return;
}

void PanoReport()
{
	char report[1024];
	struct _timeb tstruct; 
	char *timeline;
	long tmptime[2];

	_ftime( &tstruct );
    timeline = ctime( & (tmptime[0]=tstruct.time) );
	sprintf(report,"PanosphericReport:%.19s.%hu %s", timeline, tmptime[1]=tstruct.millitm, &timeline[20] );
	SendBuf((unsigned char *)report,strlen(report),PANO_TYPEFLAG_REPORT,tmptime);
	return;
}
