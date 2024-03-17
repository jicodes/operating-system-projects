#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h> // Include the Linux linked list header
#include <linux/slab.h> // Include kmalloc and kfree

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list; // Use struct list_head for the linked list
};

// Define a linked list head
static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
static int simple_init(void)
{
    struct birthday *person, *ptr;
    int i;

    // Create and initialize five struct birthday instances
    for (i = 0; i < 5; ++i) {
        // Allocate memory for the struct birthday
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        if (!person) {
            printk(KERN_ALERT "Memory allocation failed\n");
            return -ENOMEM;
        }

        // Initialize the struct birthday instance
        person->day = i + 1;
        person->month = i + 3;
        person->year = i + 1995;

        // Initialize the list member in struct birthday
        INIT_LIST_HEAD(&person->list);

        // Add the struct birthday instance to the end of the linked list
        list_add_tail(&person->list, &birthday_list);
    }

    // Traverse the linked list and output its contents to the kernel log buffer
    printk(KERN_INFO "Linked List Contents:\n");
    list_for_each_entry(ptr, &birthday_list, list) {
        printk(KERN_INFO "Birthday: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
    }

    return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void)
{
    struct birthday *ptr, *next;

    // Remove elements from the linked list and return the free memory back to the kernel
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        // Remove the element from the list
        list_del(&ptr->list);

        // Free the memory allocated for the struct birthday
        kfree(ptr);
    }

    printk(KERN_INFO "Linked List Removed\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Module with Linked List");
MODULE_AUTHOR("SGG");