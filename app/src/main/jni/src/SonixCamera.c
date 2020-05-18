#include "SonixCamera.h"
#include "XUOptDev.h"
#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <XUOptDev.h>

int camera_init = FALSE;
extern unsigned int uiRomID;

int SonixCam_Init(int videoIndex)
{
    if(camera_init)
        return TRUE;

	char devPath[300] = {0};
	sprintf(devPath, "/dev/video%d", videoIndex);
	if(!XU_OpenCamera(devPath))
	{
		fprintf(stderr, "Open video device failed\n");
		return FALSE;
	}

	camera_init = TRUE;
	
    return TRUE;
}

int SonixCam_UnInit()
{
	if (!camera_init)
		return FALSE;

	if(!XU_CloseCamera())
	{
		return FALSE;
	}
	camera_init = FALSE;
    return TRUE;
}

int SonixCam_AsicRegisterRead(unsigned short addr, unsigned char pData[], long len)
{
	if (!camera_init)
		return FALSE;
	
	BYTE data = 0;
	USHORT startAddr = addr;
	LONG i = 0;
	for (i = 0; i < len; i++)
	{
		if (TRUE != XU_ReadFromASIC((USHORT)startAddr++, &data))
			return FALSE;
		memcpy(pData + i, &data, 1);
	}
	return TRUE;
}

int SonixCam_AsicRegisterWrite(unsigned short addr, unsigned char pData[], long len)
{
	if (!camera_init)
		return FALSE;
	
	BYTE data = 0;
	LONG startAddr = addr;
	LONG i = 0;
	for (i = 0; i < len; i++)
	{
		data = pData[i];
		if (TRUE != XU_WriteToASIC((USHORT)startAddr++, data))
			return FALSE;
	}
	return TRUE;
}


