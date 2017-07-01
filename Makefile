
BUILD_DIR ?= $(PWD)/build
BUILD_DIR_MAKEFILE ?= $(PWD)/build/Makefile

obj-m += ksm.o

default: $(BUILD_DIR_MAKEFILE)
	 make -C /lib/modules/$(shell uname -r)/build M=$(BUILD_DIR) src=$(PWD) modules

$(BUILD_DIR):
	mkdir -p "$@"

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	touch "$@"

clean:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) src=$(PWD) clean

# TODO: make install_mod_dir viable only for arch distros
install:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) src=$(PWD) modules_install
