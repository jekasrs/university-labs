#ifndef WRITE_C
#define WRITE_C

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "chardev.h"

static ssize_t device_write (struct file *file, const char __user * buffer, size_t length, loff_t * offset)
{
  int i;
 
  printk ("device_write(%p,%s,%d)", file, buffer, length);
  
  for (i = 0; i < length && i < BUF_LEN; i++)
    get_user (Message[i], buffer + i);

  if (strstr(Message, "direction back")){

    direction = 0;
    strcpy(Message, Message+15);
  }
  else if (strstr(Message, "direction forward")){
    direction = 1; 
    strcpy(Message, Message+17);
  }
  if (direction)
    Message_Ptr = Message;
  else 
    Message_Ptr = reverse(Message);

  return i;
}

#endif
