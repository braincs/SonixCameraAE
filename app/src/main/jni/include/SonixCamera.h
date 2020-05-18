#ifndef __SONIXCAMERA_H__
#define __SONIXCAMERA_H__
#include "util.h"


// lib init
int  SonixCam_Init(int videoIndex);

int  SonixCam_UnInit();

//reset device
int  SonixCam_RestartDevice();

//error code
ERROR_CODE SonixCam_GetErrorCode();

// dsp register read 
int  SonixCam_AsicRegisterRead(unsigned short addr, unsigned char pData[], long len);
// * dsp register write 
int  SonixCam_AsicRegisterWrite(unsigned short addr, unsigned char pData[], long len);


#endif
