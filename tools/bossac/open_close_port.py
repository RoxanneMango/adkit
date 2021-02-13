import serial
import time

print("Opening port")

serial_port = serial.Serial("com3", 1200)
print("Port is open")


serial_port.close()
print("Port is closed")

time.sleep(1);