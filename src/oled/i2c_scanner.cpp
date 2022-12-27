#include "i2c_scanner.h"
 
byte
i2c_scanner()
{

	Wire.begin();
	
	byte error, address, result = 0;
	int nDevices = 0;

	printf("Scanning...\n\r");

	for(address = 1; address < 127; address++ ) {
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		if (error == 0) {
			printf("I2C device found at address 0x");
			if (address<16) {
				printf("0");
			}
			printf("%X\n\r", address);
			result = address;
			nDevices++;
		}
		else if (error==4) {
			printf("Unknow error at address 0x");
			if (address<16) {
				printf("0");
			}
			printf("%X\n\r",address);
		}    
	}
	if (nDevices == 0) {
		printf("No I2C devices found\n\r");
	}
	else {
		printf("done\n\r");
		return result;
	}
	return -1;
}