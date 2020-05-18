
#include "XUOptDev.h"
#include "util.h"
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

int fd = 0;
extern BOOL camera_init;

BOOL XU_OpenCamera(char *devPath)
{
	struct v4l2_capability cap;
	if((fd = open(devPath,O_RDWR | O_NONBLOCK)) < 0)
	{
		return FALSE;
	} 

	memset(&cap, 0, sizeof(cap));
	if(ioctl(fd,VIDIOC_QUERYCAP,&cap)<0)
	{
		printf("Error opening device %s : unable to query device.\n", devPath);
		close(fd);
		return FALSE;
	}
	printf("Device %s opened: %s.\n",devPath, cap.card);
	return TRUE;
}

BOOL XU_CloseCamera()
{
	if(!camera_init)
		return FALSE;
	
	if(-1 == close(fd))
	{
		perror("Fail to close fd");	
		return FALSE;
	}
	return TRUE;
}

int XU_Get_Cur(__u8 xu_unit, __u8 xu_selector, __u16 xu_size, __u8 *xu_data)
{
	int err=0;
#if LINUX_VERSION_CODE > KERNEL_VERSION (3, 0, 36)
	struct uvc_xu_control_query xctrl;
	xctrl.unit = xu_unit;
	xctrl.selector = xu_selector;
	xctrl.query = UVC_GET_CUR;
	xctrl.size = xu_size;
	xctrl.data = xu_data;
	err=ioctl(fd, UVCIOC_CTRL_QUERY, &xctrl);
#else
	struct uvc_xu_control xctrl;	
	xctrl.unit = xu_unit;
	xctrl.selector = xu_selector;
	xctrl.size = xu_size;
	xctrl.data = xu_data;
	err=ioctl(fd, UVCIOC_CTRL_GET, &xctrl);
#endif	
	return err;
}

int XU_Set_Cur(__u8 xu_unit, __u8 xu_selector, __u16 xu_size, __u8 *xu_data)
{
	int err=0;
#if LINUX_VERSION_CODE > KERNEL_VERSION (3, 0, 36)
	struct uvc_xu_control_query xctrl;
	xctrl.unit = xu_unit;
	xctrl.selector = xu_selector;
	xctrl.query = UVC_SET_CUR;
	xctrl.size = xu_size;
	xctrl.data = xu_data;
	err=ioctl(fd, UVCIOC_CTRL_QUERY, &xctrl);
#else
	struct uvc_xu_control xctrl;	
	xctrl.unit = xu_unit;
	xctrl.selector = xu_selector;
	xctrl.size = xu_size;
	xctrl.data = xu_data;
	err=ioctl(fd, UVCIOC_CTRL_SET, &xctrl);
#endif		
	return err;
}

BOOL XU_ReadFromASIC(USHORT addr, BYTE *pValue)
{
	int ret = 0;
	__u8 ctrldata[4];

	//uvc_xu_control parmeters
	__u8 xu_unit= 3; 
	__u8 xu_selector= XU_SONIX_SYS_ASIC_RW;
	__u16 xu_size= 4;
	__u8 *xu_data= ctrldata;

	xu_data[0] = (addr & 0xFF);
	xu_data[1] = ((addr >> 8) & 0xFF);
	xu_data[2] = 0x0;
	xu_data[3] = 0xFF;		/* Dummy Write */
	
	/* Dummy Write */
	if ((ret=XU_Set_Cur(xu_unit, xu_selector, xu_size, xu_data)) < 0) 
	{
		printf("ioctl(UVCIOC_CTRL_SET) FAILED (%i) \n",ret);
		//if(ret==EINVAL)			printf("Invalid arguments\n");		
		return FALSE;
	}
	
	/* Asic Read */
	xu_data[3] = 0x00;
	if ((ret=XU_Get_Cur(xu_unit, xu_selector, xu_size, xu_data)) < 0) 
	{
		printf("ioctl(UVCIOC_CTRL_GET) FAILED (%i)\n",ret);
		//if(ret==EINVAL)			printf("Invalid arguments\n");
		return FALSE;
	}
	*pValue = xu_data[2];
	if(ret < 0)
		return FALSE;
	return TRUE;
}

BOOL XU_WriteToASIC(USHORT addr, BYTE value)
{
	int ret = 0;
	__u8 ctrldata[4];

	//uvc_xu_control parmeters
	__u8 xu_unit= 3; 
	__u8 xu_selector= XU_SONIX_SYS_ASIC_RW;
	__u16 xu_size= 4;
	__u8 *xu_data= ctrldata;

	xu_data[0] = (addr & 0xFF);			/* Addr Low */
	xu_data[1] = ((addr >> 8) & 0xFF);	/* Addr High */
	xu_data[2] = value;
	xu_data[3] = 0x0;					/* Normal Write */
	
	/* Normal Write */
	if ((ret=XU_Set_Cur(xu_unit, xu_selector, xu_size, xu_data)) < 0) 
	{
		printf("ioctl(UVCIOC_CTRL_SET) FAILED (%i) \n",ret);
		//if(ret==EINVAL)			printf("Invalid arguments\n");	
		return FALSE;	
	}
	
	if(ret < 0)
		return FALSE;
	return TRUE;
}


