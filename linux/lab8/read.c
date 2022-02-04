#ifndef READ_C
#define READ_C

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "chardev.h"

static ssize_t device_read (struct file * file, char __user * buffer, size_t length, loff_t * offset)
{
  int bytes_read = 0;
 
  if (*Message_Ptr == 0)
    return 0;

  while (length && *Message_Ptr) {
    put_user (*(Message_Ptr++), buffer++);
    length--;
    bytes_read++;
  }
 
  printk("Read %d bytes, %d left\n", bytes_read, length);
  return bytes_read;
}

#endif
