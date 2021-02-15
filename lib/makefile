include makefile.include

#######################################################################################################

.PHONY: all sam adafruit-neopixel rtc clean

all: sam adafruit-neopixel rtc
clean: clean-sam clean-adafruit-neopixel clean-rtc

#######################################################################################################

SAM_BUILD = $(SAM_DIR)/build
SAM_OUT = $(SAM_DIR)/out

SAM_CORE_OBJECTS_CXX = abi.o IPAddress.o new.o Print.o Reset.o RingBuffer.o UARTClass.o USARTClass.o watchdog.o wiring_pulse.o WMath.o WString.o 
SAM_CORE_USB_OBJECTS_CXX = CDC.o PluggableUSB.o USBCore.o
SAM_CORE_OBJECTS_C = cortex_handlers.o hooks.o iar_calls_sam3.o itoa.o syscalls_sam3.o WInterrupts.o wiring.o wiring_analog.o wiring_digital.o wiring_shift.o 
SAM_CORE_AVR_OBJECTS_C = dtostrf.o
SAM_CORE_OBJECTS_S = wiring_pulse_asm.o
SAM_VARS_OBJECTS_CXX = variant.o

SAM_ARCHIVE = sam.a

sam: sam-out-dir $(SAM_CORE_OBJECTS_CXX) $(SAM_CORE_USB_OBJECTS_CXX) $(SAM_CORE_OBJECTS_C) $(SAM_CORE_AVR_OBJECTS_C) $(SAM_CORE_OBJECTS_S) sam-peripherals $(SAM_VARS_OBJECTS_CXX)

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
	rm -r $(SAM_BUILD)
	rm -r $(SAM_OUT)
	
#######################################################################################################

ADAFRUIT_BUSIO_DIR = Adafruit_BusIO
ADAFRUIT_BUSIO_BUILD = $(ADAFRUIT_BUSIO_DIR)/build
ADAFRUIT_BUSIO_OUT = $(ADAFRUIT_BUSIO_DIR)/out

ADAFRUIT_BUSIO_ARCHIVE = Adafruit_BusIO.a
ADAFRUIT_BUSIO_INCLUDE = -I$(ADAFRUIT_BUSIO_DIR)
ADAFRUIT_BUSIO_OBJECTS_CXX = Adafruit_BusIO_Register.o Adafruit_I2CDevice.o Adafruit_SPIDevice.o

adafruit-busio: adafruit-busio-out-dir $(ADAFRUIT_BUSIO_OBJECTS_CXX)

$(ADAFRUIT_BUSIO_OBJECTS_CXX): %.o: $(ADAFRUIT_BUSIO_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(ADAFRUIT_BUSIO_INCLUDE) $< -o $(ADAFRUIT_BUSIO_BUILD)/$@
	$(AR) rcs $(ADAFRUIT_BUSIO_OUT)/$(ADAFRUIT_BUSIO_ARCHIVE) $(ADAFRUIT_BUSIO_BUILD)/$@

adafruit-busio-build-dir:
	cd $(ADAFRUIT_BUSIO_DIR) && mkdir -p build
adafruit-busio-out-dir: adafruit-busio-build-dir
	cd $(ADAFRUIT_BUSIO_DIR) && mkdir -p out
	
clean-adafruit-busio:
	rm -r $(ADAFRUIT_BUSIO_BUILD)
	rm -r $(ADAFRUIT_BUSIO_OUT)

#######################################################################################################

ADAFRUIT_GFX_DIR = Adafruit-GFX-Library
ADAFRUIT_GFX_BUILD = $(ADAFRUIT_GFX_DIR)/build
ADAFRUIT_GFX_OUT = $(ADAFRUIT_GFX_DIR)/out

ADAFRUIT_GFX_ARCHIVE = Adafruit-GFX-Library.a
ADAFRUIT_GFX_INCLUDES = -I$(ADAFRUIT_GFX_DIR) -I$(ADAFRUIT_BUSIO_DIR)
ADAFRUIT_GFX_OBJECTS_CXX = Adafruit_GFX.o Adafruit_GrayOLED.o Adafruit_SPITFT.o
ADAFRUIT_GFX_OBJECTS_C = glcdfont.o

adafruit-gfx: adafruit-gfx-out-dir $(ADAFRUIT_GFX_OBJECTS_CXX) $(ADAFRUIT_GFX_OBJECTS_C)

$(ADAFRUIT_GFX_OBJECTS_CXX): %.o: $(ADAFRUIT_GFX_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(ADAFRUIT_GFX_INCLUDES) $< -o $(ADAFRUIT_GFX_BUILD)/$@
	$(AR) rcs $(ADAFRUIT_GFX_OUT)/$(ADAFRUIT_GFX_ARCHIVE) $(ADAFRUIT_GFX_BUILD)/$@

$(ADAFRUIT_GFX_OBJECTS_C): %.o: $(ADAFRUIT_GFX_DIR)/%.c
	$(CC) $(CFLAGS) $(ADAFRUIT_GFX_INCLUDES) $< -o $(ADAFRUIT_GFX_BUILD)/$@
	$(AR) rcs $(ADAFRUIT_GFX_OUT)/$(ADAFRUIT_GFX_ARCHIVE) $(ADAFRUIT_GFX_BUILD)/$@

adafruit-gfx-build-dir:
	cd $(ADAFRUIT_GFX_DIR) && mkdir -p build
adafruit-gfx-out-dir: adafruit-gfx-build-dir
	cd $(ADAFRUIT_GFX_DIR) && mkdir -p out
	
clean-adafruit-gfx:
	rm -r $(ADAFRUIT_GFX_BUILD)
	rm -r $(ADAFRUIT_GFX_OUT)

#######################################################################################################

ADAFRUIT_SSD1306_DIR = Adafruit_SSD1306
ADAFRUIT_SSD1306_BUILD = $(ADAFRUIT_SSD1306_DIR)/build
ADAFRUIT_SSD1306_OUT = $(ADAFRUIT_SSD1306_DIR)/out

ADAFRUIT_SSD1306_INCLUDES = -I$(ADAFRUIT_SSD1306_DIR) -I$(ADAFRUIT_GFX_DIR)
ADAFRUIT_SSD1306_ARCHIVE = Adafruit_SSD1306.a

adafruit-ssd1306: adafruit-ssd1306-out-dir
	$(CXX) $(CXXFLAGS) $(ADAFRUIT_SSD1306_INCLUDES) $(ADAFRUIT_SSD1306_DIR)/Adafruit_SSD1306.cpp -o $(ADAFRUIT_SSD1306_BUILD)/Adafruit_SSD1306.o
	$(AR) rcs $(ADAFRUIT_SSD1306_OUT)/$(ADAFRUIT_SSD1306_ARCHIVE) $(ADAFRUIT_SSD1306_BUILD)/Adafruit_SSD1306.o

adafruit-ssd1306-build-dir:
	cd $(ADAFRUIT_SSD1306_DIR) && mkdir -p build
adafruit-ssd1306-out-dir: adafruit-ssd1306-build-dir
	cd $(ADAFRUIT_SSD1306_DIR) && mkdir -p out
	
clean-adafruit-ssd1306:
	rm -r $(ADAFRUIT_SSD1306_BUILD)
	rm -r $(ADAFRUIT_SSD1306_OUT)

#######################################################################################################

ADAFRUIT_NEOPIXEL_DIR = Adafruit_NeoPixel
ADAFRUIT_NEOPIXEL_BUILD = $(ADAFRUIT_NEOPIXEL_DIR)/build
ADAFRUIT_NEOPIXEL_OUT = $(ADAFRUIT_NEOPIXEL_DIR)/out

ADAFRUIT_NEOPIXEL_INCLUDES = -I$(ADAFRUIT_NEOPIXEL_DIR) -I$(ADAFRUIT_SSD1306_DIR)
ADAFRUIT_NEOPIXEL_ARCHIVE = Adafruit_NeoPixel.a
ADAFRUIT_NEOPIXEL_OBJECTS_CXX = Adafruit_NeoPixel.o
ADAFRUIT_NEOPIXEL_OBJECTS_C = esp.o kendyte_k210.o

adafruit-neopixel: adafruit-busio adafruit-gfx adafruit-ssd1306 adafruit-neopixel-out-dir $(ADAFRUIT_NEOPIXEL_OBJECTS_CXX) $(ADAFRUIT_NEOPIXEL_OBJECTS_C)

$(ADAFRUIT_NEOPIXEL_OBJECTS_CXX): %.o: $(ADAFRUIT_NEOPIXEL_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(ADAFRUIT_NEOPIXEL_INCLUDES) $< -o $(ADAFRUIT_NEOPIXEL_BUILD)/$@
	$(AR) rcs $(ADAFRUIT_NEOPIXEL_OUT)/$(ADAFRUIT_NEOPIXEL_ARCHIVE) $(ADAFRUIT_NEOPIXEL_BUILD)/$@

$(ADAFRUIT_NEOPIXEL_OBJECTS_C): %.o: $(ADAFRUIT_NEOPIXEL_DIR)/%.c
	$(CC) $(CFLAGS) $(ADAFRUIT_NEOPIXEL_INCLUDES) $< -o $(ADAFRUIT_NEOPIXEL_BUILD)/$@
	$(AR) rcs $(ADAFRUIT_NEOPIXEL_OUT)/$(ADAFRUIT_NEOPIXEL_ARCHIVE) $(ADAFRUIT_NEOPIXEL_BUILD)/$@

adafruit-neopixel-build-dir:
	cd $(ADAFRUIT_NEOPIXEL_DIR) && mkdir -p build
adafruit-neopixel-out-dir: adafruit-neopixel-build-dir
	cd $(ADAFRUIT_NEOPIXEL_DIR) && mkdir -p out

clean-adafruit-neopixel: clean-adafruit-busio clean-adafruit-gfx clean-adafruit-ssd1306
	rm -r $(ADAFRUIT_NEOPIXEL_BUILD)
	rm -r $(ADAFRUIT_NEOPIXEL_OUT)

#######################################################################################################

RTC_DIR = RTCDue
RTC_BUILD = $(RTC_DIR)/build
RTC_OUT = $(RTC_DIR)/out

RTC_INCLUDES = $(RTC_DIR)/src
RTC_ARCHIVE = RTCDue.a

rtc: rtc-out-dir
	$(CXX) $(CXXFLAGS) $(RTC_INCLUDES) $(RTC_DIR)/src/RTCDue.cpp -o $(RTC_BUILD)/RTCDue.o
	$(AR) rcs $(RTC_OUT)/$(RTC_ARCHIVE) $(RTC_BUILD)/RTCDue.o

rtc-build-dir:
	cd $(RTC_DIR) && mkdir -p build
rtc-out-dir : rtc-build-dir
	cd $(RTC_DIR) && mkdir -p out

clean-rtc:
	rm -r $(RTC_BUILD)
	rm -r $(RTC_OUT)

#######################################################################################################