#ifndef CHARDEV_H
#define CHARDEV_H
 
#include <linux/ioctl.h>

#define SUCCESS 0
#define DEVICE_NAME "char_dev"
#define BUF_LEN 80
#define MAJOR_NUM 100

#define IOCTL_SET_MSG _IOR (MAJOR_NUM, 0, char *)
#define IOCTL_GET_MSG _IOR (MAJOR_NUM, 1, char *)
#define IOCTL_GET_NTH_BYTE _IOWR (MAJOR_NUM, 2, int)
#define IOCTL_DELETE_MSG _IOR (MAJOR_NUM, 3, char *)

#define DEVICE_FILE_NAME "char_dev"

static int device_release (struct inode * inode, struct file * file);
static ssize_t device_write (struct file *file, const char __user * buffer, size_t length, loff_t * offset);
static ssize_t device_read (struct file * file, char __user * buffer, size_t length, loff_t * offset);
static long device_ioctl (struct file * file, unsigned int ioctl_num, unsigned long ioctl_param);
static int device_open (struct inode * inode, struct file * file)

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Smirnov Evgeny" );
MODULE_DESCRIPTION( "Lab 8" );
MODULE_VERSION( "1.0" );

static int direction = 1;
char *reverse(char *str);
static int Device_Open = 0;
static char Message [BUF_LEN];
static char * Message_Ptr;

struct file_operations Fops = {
  .read = device_read,
  .write = device_write,
  .unlocked_ioctl = device_ioctl,
  .open = device_open,
  .release = device_release,
};
 
#endif
