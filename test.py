import time
import grovepi

# Connect the Grove Accelerometer (+/- 1.5g) to any I2C port eg. I2C-1
# Can be found at I2C address 0x4c
# SCL,SDA,VCC,GND

test = grovepi.acc_xyz()
print test[0]
