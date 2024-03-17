# Loading and Removing Kernel Modules

## Part 1

- Kernel modules are loaded using the insmod command, which is run as follows:

```bash
sudo insmod simple.ko
```

- To check whether the module has loaded, enter the lsmod command and search for the module simple. Recall that the module entry point is invoked when the module is inserted into the kernel. To check the contents of this message in the kernel log buffer, enter the command `dmesg` You should see the message `"Loading Module."`

- Removing the kernel module involves invoking the rmmod command
  (notice that the .ko suffix is unnecessary):

```bash
sudo rmmod simple
```

- Be sure to check with the dmesg command to ensure the module has been removed. Because the kernel log buffer can fill up quickly, it often makes sense to clear the buffer periodically. This can be accomplished as follows:

```bash
sudo dmesg -c
```

## Part 2

- In the module entry point, create a linked list containing five struct birthday elements. Traverse the linked list and output its contents to the kernel log buffer. Invoke the `dmesg` command to ensure the list is properly constructed once the kernel module has been loaded.

- In the module exit point, delete the elements from the linked list and return the free memory back to the kernel. Again, invoke the `dmesg` command to check that the list has been removed once the kernel module has been unloaded.

## How to test the kernel module

1. Upload module source code and Makefile to cloud vm directory:
   /usr/src/kernel-modules/

2. Use `make` to build into a `<module_name>.ko` file

```bash
make
```
- You may install some packages depending on the distro of your vm, for example:
- `gcc`
- `make`
- `...`

3. Load the Kernel Module:

- Navigate to the directory containing the compiled kernel module (usually located in the ./build or ./output directory) and run:

```bash
sudo insmod <module_name>.ko
```

- Replace `<module_name>.ko` with the name of my kernel module file.

4. Verify the Module is Loaded:

- After loading the kernel module, we can verify that it has been loaded successfully by checking the kernel log using the `dmesg` command.
- Run `sudo dmesg -c` in the terminal and look for log messages related to the module to ensure it was loaded without any errors.

5. Unload the Kernel Module:

- Run the following command in the terminal:

```bash
sudo rmmod <module_name>
```

6. Verify the Module is Unloaded:

- After unloading the kernel module, we can verify that it has been unloaded successfully by checking the kernel log using the `sudo dmesg -c` command.
