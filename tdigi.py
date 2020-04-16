import time
import grovepi

display = 5
sensor = 3
leading_zero = 0

grovepi.fourDigit_number(display, 5, leading_zero)

while True:
	list = grovepi.dht(3, 0)
	grovepi.fourDigit_number(display, int(list[0]), 1)
        time.sleep(3)
