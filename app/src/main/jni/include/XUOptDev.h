#ifndef __LUOPTDEV_H__
#define __LUOPTDEV_H__

#include "util.h"
#include <linux/videodev2.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE > KERNEL_VERSION (3, 0, 36)
#include <linux/uvcvideo.h>
#endif

#define XU_SONIX_SYS_ASIC_RW	      			0x01

#if LINUX_VERSION_CODE > KERNEL_VERSION (3, 0, 36)
#define UVC_SET_CUR					0x01
#define UVC_GET_CUR					0x81
#define UVCIOC_CTRL_MAP		_IOWR('u', 0x20, struct uvc_xu_control_mapping)
#define UVCIOC_CTRL_QUERY	_IOWR('u', 0x21, struct uvc_xu_control_query)
#else
#define UVCIOC_CTRL_ADD		_IOW('U', 1, struct uvc_xu_control_info)
#define UVCIOC_CTRL_MAP		_IOWR('U', 2, struct uvc_xu_control_mapping)
#define UVCIOC_CTRL_GET		_IOWR('U', 3, struct uvc_xu_control)
#define UVCIOC_CTRL_SET		_IOW('U', 4, struct uvc_xu_control)
#endif

BOOL XU_OpenCamera(char *devPath);
BOOL XU_CloseCamera();

BOOL XU_ReadFromASIC(USHORT addr, BYTE *pValue);
BOOL XU_WriteToASIC(USHORT addr, BYTE value);

#endif





