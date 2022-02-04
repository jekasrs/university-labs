#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");

static short int myshort = 1;
static char *mystring = "blah-blah";

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");

static int __init init_hello_5(void)
{
  pr_info("Hello, world 5.\n=========================\n");
  pr_info("myshort is a short integer: %hd\n", myshort);
  pr_info("mystring is a string: %s\n", mystring);

  return 0;
}

static void __exit cleanup_hello_5(void)
{
  pr_info("Goodbye, world 5.\n");
}

module_init(init_hello_5);
module_exit(cleanup_hello_5);
