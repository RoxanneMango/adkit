DELETE = rm
DELETE_DIR = rm -r
MAKE = make
CC = gcc
CXX = g++

CFLAGS = -Wall -static -O3
CXXFLAGS = -Wall -std=c++14 -static -O3
LIBS = 

SRC = src
BUILD = build
OUT = bin

OBJECTS = CmdOpts.o Samba.o FlashFactory.o Flash.o WordCopyApplet.o Applet.o WordCopyArm.o Flasher.o EfcFlash.o EefcFlash.o NvmFlash.o
EXEC = bossac

ARCHIVE = lib.a

ifeq ($(OS),Windows_NT)
	DELETE = del
	LIBS += -lsetupapi
	OBJECTS += WinPortFactory.o WinSerialPort.o
	CXXFLAGS += -D _WIN32_WINNT=0x0601
	EXEC = bossac.exe
	DELETE_DIR = rmdir
else
	OBJECTS += LinuxPortFactory.o PosixSerialPort.o
endif

.PHONY: all clean run db

all: $(OBJECTS) $(OUT)
	cd $(BUILD)
	$(CXX) -o $(OUT)/$(EXEC) $(SRC)/bossac.cpp $(BUILD)/$(ARCHIVE) $(CXXFLAGS) $(LIBS)
#	$(DELETE_DIR) $(BUILD)

$(OBJECTS): %.o: $(SRC)/%.cpp $(BUILD)
	$(CXX) -c $(CXXFLAGS) $(LIBS) $< -o $(BUILD)/$@
	$(AR) rcs $(BUILD)/$(ARCHIVE) $(BUILD)/$@

ifeq ($(OS),Windows_NT)

$(BUILD):
	if not exist $(BUILD) mkdir $(BUILD)
$(OUT): $(BUILD)
	if not exist $(OUT) mkdir $(OUT) && cd ..

clean:
	$(DELETE) $(BUILD)\\*.*
	$(DELETE) $(OUT)\$(EXEC)

else

$(BUILD):
	mkdir -p $(BUILD)
$(OUT): $(BUILD)
	mkdir -p $(OUT)

clean:
	$(DELETE) $(BUILD)/*.*
	$(DELETE) $(OUT)/$(EXEC)
	
endif