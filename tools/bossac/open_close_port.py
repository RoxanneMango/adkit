import serial
import time
import sys

print("Opening port")

port = "com3"
if(len(sys.argv) >= 1):
    port = str(sys.argv[1])

serial_port = serial.Serial(port, 1200)
print("Port is open")

serial_port.close()
print("Port is closed")

time.sleep(1);