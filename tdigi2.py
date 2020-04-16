import time,sys
import grovepi


if sys.platform == 'uwp':
    import winrt_smbus as smbus
    bus = smbus.SMBus(1)
else:
    import smbus
    import RPi.GPIO as GPIO
    rev = GPIO.RPI_REVISION
    if rev == 2 or rev == 3:
        bus = smbus.SMBus(1)
    else:
        bus = smbus.SMBus(0)

DISPLAY_RGB_ADDR = 0x62
DISPLAY_TEXT_ADDR = 0x3e

display = 5
sensor = 3
leading_zero = 0
ultrasonic_ranger = 4


def textCommand(cmd):
    bus.write_byte_data(DISPLAY_TEXT_ADDR, 0x80, cmd)

# set display text \n for second line(or auto wrap)     
def setText(text):
    textCommand(0x01) # clear display
    time.sleep(.05)
    textCommand(0x08 | 0x04) # display on, no cursor
    textCommand(0x28) # 2 lines
    time.sleep(.05)
    count = 0
    row = 0

    for c in text:
        if c == '\n' or count == 16:
            count = 0
            row += 1
            if row == 2:
                break
            textCommand(0xc0)
            if c == '\n':
                continue
        count += 1
        bus.write_byte_data(DISPLAY_TEXT_ADDR,0x40,ord(c))

def setRGB(r,g,b):
    bus.write_byte_data(DISPLAY_RGB_ADDR,0,0)
    bus.write_byte_data(DISPLAY_RGB_ADDR,1,0)
    bus.write_byte_data(DISPLAY_RGB_ADDR,0x08,0xaa)
    bus.write_byte_data(DISPLAY_RGB_ADDR,4,r)
    bus.write_byte_data(DISPLAY_RGB_ADDR,3,g)
    bus.write_byte_data(DISPLAY_RGB_ADDR,2,b)

#Update the display without erasing the display
def setText_norefresh(text):
    textCommand(0x02) # return home
    time.sleep(.05)
    textCommand(0x08 | 0x04) # display on, no cursor
    textCommand(0x28) # 2 lines
    time.sleep(.05)
    count = 0
    row = 0

    while len(text) < 32: #clears the rest of the screen
        text += ' '

    for c in text:
        if c == '\n' or count == 16:
            count = 0
            row += 1
            if row == 2:
                break
            textCommand(0xc0)
            if c == '\n':
                continue
        count += 1
        bus.write_byte_data(DISPLAY_TEXT_ADDR,0x40,ord(c))

if __name__=="__main__":
    setText("Hi everyone!")

    while True:
        range = grovepi.ultrasonicRead(ultrasonic_ranger)
        if range < 10:
            setRGB(200, 0, 0)
        elif range < 20 :
            setRGB(150, 50, 50)
        elif range < 50 :
            setRGB(100, 50, 100)
        else :
            setRGB(0, 0, 200)

        list = grovepi.dht(3, 0)
        print list;
        setText_norefresh("temp:" + str(list[0]) + "\nRange:" + str(range))

        time.sleep(1)

# grovepi.fourDigit_number(display, 5, leading_zero)

#while True:
#	list = grovepi.dht(3, 0)
#	grovepi.fourDigit_number(display, int(list[0]), 1)
#       time.sleep(3)


