#ifndef OPENRELEASE_C
#define OPENRELEASE_C

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "chardev.h"

static int device_open (struct inode * inode, struct file * file)
{
  printk ("device_open(%p)\n", file);

  if (Device_Open) 
    return -EBUSY;
  
  Device_Open++;
  Message_Ptr = Message;
  try_module_get (THIS_MODULE);
  return SUCCESS;
}

static int device_release (struct inode * inode, struct file * file)
{
  printk ("device_release(%p,%p)\n", inode, file);
  Device_Open--;
  module_put (THIS_MODULE);
  return SUCCESS;
}

#endif
