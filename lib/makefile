include makefile.include

#######################################################################################################

.PHONY: all sam adafruit-neopixel catch2 clean

all: sam adafruit-neopixel catch2
	@echo "Done"

clean: clean-sam clean-adafruit-neopixel clean-catch2

#######################################################################################################

SAM_DIR = ArduinoCore-sam
SAM_BUILD = $(SAM_DIR)/build
SAM_OUT = $(SAM_DIR)/out

SAM_CORE = $(SAM_DIR)/cores/arduino
SAM_CORE_USB = $(SAM_CORE)/usb
SAM_CORE_AVR = $(SAM_CORE)/avr
SAM_LIBS = $(SAM_DIR)/libraries
SAM_VARS = $(SAM_DIR)/variants/arduino_due_x

SAM_CORE_OBJECTS_CXX = abi.o IPAddress.o new.o Print.o Reset.o RingBuffer.o UARTClass.o USARTClass.o watchdog.o wiring_pulse.o WMath.o WString.o 
SAM_CORE_USB_OBJECTS_CXX = CDC.o PluggableUSB.o USBCore.o
SAM_CORE_OBJECTS_C = cortex_handlers.o hooks.o iar_calls_sam3.o itoa.o syscalls_sam3.o WInterrupts.o wiring.o wiring_analog.o wiring_digital.o wiring_shift.o 
SAM_CORE_AVR_OBJECTS_C = dtostrf.o
SAM_CORE_OBJECTS_S = wiring_pulse_asm.o
SAM_VARS_OBJECTS_CXX = variant.o

SAM_ARCHIVE = sam.a

sam: sam-out-dir $(SAM_CORE_OBJECTS_CXX) $(SAM_CORE_USB_OBJECTS_CXX) $(SAM_CORE_OBJECTS_C) $(SAM_CORE_AVR_OBJECTS_C) $(SAM_CORE_OBJECTS_S) sam-peripherals $(SAM_VARS_OBJECTS_CXX)
	@echo "Successfully created SAM archive"

sam-out-dir: sam-build-dir
	cd $(SAM_DIR) && mkdir -p out
	
sam-build-dir:
	cd $(SAM_DIR) && mkdir -p build

$(SAM_CORE_USB_OBJECTS_CXX): %.o: $(SAM_CORE_USB)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $(SAM_BUILD)/$@
	$(AR) rcs $(SAM_OUT)/$(SAM_ARCHIVE) $(SAM_BUILD)/$@

$(SAM_CORE_AVR_OBJECTS_C): %.o: $(SAM_CORE_AVR)/%.c
	$(CC) $(CFLAGS) $< -o $(SAM_BUILD)/$@
	$(AR) rcs $(SAM_OUT)/$(SAM_ARCHIVE) $(SAM_BUILD)/$@

$(SAM_CORE_OBJECTS_CXX): %.o: $(SAM_CORE)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $(SAM_BUILD)/$@
	$(AR) rcs $(SAM_OUT)/$(SAM_ARCHIVE) $(SAM_BUILD)/$@

$(SAM_CORE_OBJECTS_C): %.o: $(SAM_CORE)/%.c
	$(CC) $(CFLAGS) $< -o $(SAM_BUILD)/$@
	$(AR) rcs $(SAM_OUT)/$(SAM_ARCHIVE) $(SAM_BUILD)/$@

$(SAM_CORE_OBJECTS_S): %.o: $(SAM_CORE)/%.S
	$(CC) $(C_ASM_FLAGS) $< -o $(SAM_BUILD)/$@
	$(AR) rcs $(SAM_OUT)/$(SAM_ARCHIVE) $(SAM_BUILD)/$@

sam-peripherals:
	$(CXX) $(CXXFLAGS) $(SAM_LIBS)/HID/src/HID.cpp -o $(SAM_BUILD)/HID.o
	$(CXX) $(CXXFLAGS) $(SAM_LIBS)/SPI/src/SPI.cpp -o $(SAM_BUILD)/SPI.o
	$(CXX) $(CXXFLAGS) $(SAM_LIBS)/Wire/src/Wire.cpp -o $(SAM_BUILD)/Wire.o

$(SAM_LIBS_OBJECTS_CXX): %.o: $(SAM_LIBS)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $(SAM_BUILD)/$@
	$(AR) rcs $(SAM_OUT)/$(SAM_ARCHIVE) $(SAM_BUILD)/$@

$(SAM_VARS_OBJECTS_CXX): %.o: $(SAM_VARS)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $(SAM_BUILD)/$@
	$(AR) rcs $(SAM_OUT)/$(SAM_ARCHIVE) $(SAM_BUILD)/$@

clean-sam: 
	@echo "Initiating lemon pledge . . ."
	rm -r $(SAM_BUILD)
	rm -r $(SAM_OUT)
	@echo ("I clean . . .");
	
#######################################################################################################

NEOPIXEL_DIR = Adafruit_NeoPixel


