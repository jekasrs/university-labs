#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("JENEK");
MODULE_DESCRIPTION("A sample trigger");

static int __init init_hello_4(void)
{
  pr_info("Hello, world 4.\n");
  return 0;
}

static void __exit cleanup_hello_4(void)
{
  pr_info("Goodbye, world 4.\n");
}

module_init(init_hello_4);
module_exit(cleanup_hello_4);
