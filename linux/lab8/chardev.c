#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "chardev.h"
#include "openrelease.c"
#include "write.c"
#include "read.c"
#include "device_ioctl.c"

int init_module ()
{
  int ret_val;
  ret_val = register_chrdev (MAJOR_NUM, DEVICE_NAME, &Fops);

  if (ret_val < 0) {
    printk ("%s failed with %d\n",
           "Sorry, registering the character device ", ret_val);
    return ret_val;
  }
 
  printk ("%s The major device number is %d.\n", "Registeration is a success", MAJOR_NUM); 
  return 0;
}

void cleanup_module ()
{
  unregister_chrdev (MAJOR_NUM, DEVICE_NAME);
}

char *reverse(char *str)
{ 
  int i= 0;
  int j = 0;
  char ch;

  if (!str || !*str)
  {
    return str; 
  }

  i = strlen(str) - 1;

  while (i > j)
  {
   ch = str[i];
   str[i] = str[j];
   str[j] = ch;
   i--;
   j++;
  }
  
  return str;
}
