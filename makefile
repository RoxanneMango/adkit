# linux:

MAKE = make
MKDIR = mkdir
CURL = curl
UNZIP = tar
RM = rm
PYTHON = py

ARM_GCC_VERSION = 9.3.1-2020q2
ARM_GCC = arm-none-eabi-gcc
ARM_GCC_URL = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2?revision=05382cca-1721-44e1-ae19-1e7c3dc96118&la=en&hash=D7C9D18FCA2DD9F894FD9F3C3DC9228498FA281A"
ARM_GCC_ZIP = $(ARM_GCC_VERSION).tar.bz2
ARM_GCC_DIR = $(ARM_GCC_VERSION)-linux
TOOLS_DIR = tools

BOSSAC = $(TOOLS_DIR)/bossac/BOSSAC-1.6.2-arduino/bin/bossac
PORT_BUMP = $(TOOLS_DIR)/bossac/open_close_port.py

BIN_FILE = main.bin
PORT = ttyS3

ifeq ($(OS),Windows_NT)

PYTHON = py
RM = del

ARM_GCC_URL = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-win32.zip?revision=95631fd0-0c29-41f4-8d0c-3702650bdd74&la=en&hash=D2C7F7C52183A8818AE6179AB87AA7CF6B1AE275"
ARM_GCC_ZIP = $(ARM_GCC_VERSION).zip
ARM_GCC_DIR = $(ARM_GCC_VERSION)-windows
PORT = com3

endif

.PHONY: all gcc-unzip lib bossac

all: gcc lib bossac

gcc: gcc-get
	cd $(TOOLS_DIR) && cd $(ARM_GCC) && \
	$(UNZIP) xvf $(ARM_GCC_ZIP) -C $(ARM_GCC_DIR)/.
bossac:
	cd tools && cd bossac && cd BOSSAC-1.6.2-arduino && $(MAKE)
lib:
	cd lib && $(MAKE)

ifeq ($(OS),Windows_NT)

gcc-get: gcc-dir
	cd $(TOOLS_DIR) && cd $(ARM_GCC) && \
	if not exist $(ARM_GCC_ZIP) $(CURL) -L $(ARM_GCC_URL) --output $(ARM_GCC_ZIP)
gcc-dir:
	cd $(TOOLS_DIR) && if not exist $(ARM_GCC) $(MKDIR) $(ARM_GCC)
	cd $(TOOLS_DIR) && cd $(ARM_GCC) && if not exist $(ARM_GCC_DIR) $(MKDIR) $(ARM_GCC_DIR)
flash:
	@echo "Forcing reset with port-bump of 1200 bps . . ."
	$(PYTHON) $(PORT_BUMP)
	@echo "Writing binary to the arduino due . . ."
	$(BOSSAC) -i -d --port=$(PORT) -U false -e -w -v -b $(BIN_FILE) -R
clean:
	rmdir $(TOOLS_DIR)\\$(ARM_GCC)\\$(ARM_GCC_DIR) /s /q
	del $(TOOLS_DIR)\\$(ARM_GCC)\\$(ARM_GCC_ZIP) /s /q

else

gcc-get: gcc-dir
	cd $(TOOLS_DIR) && cd $(ARM_GCC) && \
	if test ! -f $(ARM_GCC_ZIP); then $(CURL) -L $(ARM_GCC_URL) --output $(ARM_GCC_ZIP) && $(MKDIR) -p $(ARM_GCC_DIR); fi
gcc-dir:
	cd $(TOOLS_DIR) && if test ! -d $(ARM_GCC); then $(MKDIR) $(ARM_GCC); fi
	cd $(TOOLS_DIR) && cd $(ARM_GCC) && if test ! -d $(ARM_GCC_DIR); then $(MKDIR) $(ARM_GCC_DIR); fi
flash:
	@echo "Writing binary to the arduino due . . ."
	$(BOSSAC) -i -d --port=$(PORT) -U false -e -w -v -b $(BIN_FILE) -R
clean:
	rm -rf $(TOOLS_DIR)/$(ARM_GCC)/$(ARM_GCC_DIR)
	rm $(TOOLS_DIR)/$(ARM_GCC)/$(ARM_GCC_ZIP)
	
endif