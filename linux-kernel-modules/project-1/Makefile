obj-m += simple.o

KERNEL_DIR := /usr/src/kernels/$(shell uname -r)

all:
    make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
    make -C $(KERNEL_DIR) M=$(PWD) clean