# linux:

MKDIR = mkdir
WGET = wget
UNZIP = tar
RM = rm

ARM_GCC_VERSION = 9.3.1-2020q2
ARM_GCC = arm-none-eabi-gcc
ARM_GCC_URL = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2?revision=05382cca-1721-44e1-ae19-1e7c3dc96118&la=en&hash=D7C9D18FCA2DD9F894FD9F3C3DC9228498FA281A"
ARM_GCC_ZIP = $(ARM_GCC_VERSION).tar.bz2
TOOLS = tools

gcc-unzip: gcc-get
	cd $(TOOLS) && cd $(ARM_GCC) && \
	$(UNZIP) xvf $(ARM_GCC_ZIP) -C $(ARM_GCC_VERSION)/. && \
	$(RM) $(ARM_GCC_ZIP)
	
gcc-get: gcc-dir
	cd $(TOOLS) && cd $(ARM_GCC) && \
	if test ! -d $(ARM_GCC_VERSION); then $(WGET) -N -O $(ARM_GCC_ZIP) $(ARM_GCC_URL) && $(MKDIR) -p $(ARM_GCC_VERSION); fi

#tools-dir:
#	$(MKDIR) -p $(TOOLS)

gcc-dir:
	cd $(TOOLS) && $(MKDIR) -p $(ARM_GCC)