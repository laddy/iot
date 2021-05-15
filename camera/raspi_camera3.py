import RPi.GPIO as GPIO
import os
import time
import picamera
from datetime import datetime

target_dir = "/home/pi/html/"
MOTION_PIN = 23
GPIO.setmode(GPIO.BCM)
GPIO.setup(MOTION_PIN, GPIO.IN)


while True:
    if 1 == GPIO.input(MOTION_PIN) :

        mdir = datetime.now().strftime('%Y%m%d')
        if not os.path.exists(target_dir + mdir) :
            os.makedirs(target_dir + mdir)

        with picamera.PiCamera() as camera:
            camera.resolution = (640, 480)
            tdatetime = datetime.now()
            tstr = target_dir + mdir + "/" + tdatetime.strftime('%H%M%S')
            camera.capture(tstr + '.jpg')
            time.sleep(3)

        print("in camera")

    else :
        print("none")
        time.sleep(0.5)
