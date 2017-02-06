#include <linux/kernel.h>

 asmlinkage long mySysCall(void)
{
        printk("Hello world\n");
        return 0;
 }
