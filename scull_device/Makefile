ifneq ($(KERNELRELEASE),)
	obj-m := scull.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.mod.c *.o *.mod.o *.order *.symvers
endif
