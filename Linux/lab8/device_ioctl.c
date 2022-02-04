#ifndef DEVICEIOCTL_C
#define DEVICEIOCTL_C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "chardev.h"

static long device_ioctl (struct file * file, unsigned int ioctl_num, unsigned long ioctl_param)
{
  int i;
  char * temp;
  char ch;
 
  switch (ioctl_num) {

  case IOCTL_SET_MSG:
    temp = (char *)ioctl_param;
    get_user (ch, temp);
    for (i = 0; ch && i < BUF_LEN; i++, temp++)
      get_user (ch, temp);
    device_write (file, (char *)ioctl_param, i, 0);
    break;
 
  case IOCTL_GET_MSG:
    i = device_read (file, (char *)ioctl_param, 99, 0);
    put_user ('\0', (char *)ioctl_param + i);
    break;
		  
  case IOCTL_DELETE_MSG:
	  device_write (file, "1", 1, 0);
    break;  
 
  case IOCTL_GET_NTH_BYTE:
    return Message [ioctl_param];
    break;
  }
 
  return SUCCESS;
}

#endif
