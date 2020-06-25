
#!/usr/bin/python

import time
import picamera
import grovepi
from datetime import datetime as dt


# Connect the Grove PIR Motion Sensor to digital port D8
# SIG,NC,VCC,GND
pir_sensor = 2


grovepi.pinMode(pir_sensor,"INPUT")

while True:
    try:
        if grovepi.digitalRead(pir_sensor):
            print 'Motion Rec...'
            with picamera.PiCamera() as camera:
                camera.resolution = (640, 480)
                # camera.start_preview()
                tdatetime = dt.now()
                tstr = tdatetime.strftime('./motion_image/%Y%m%d%H%M%S')
                camera.start_recording(tstr + '.h264')
                camera.wait_recording(10)
                camera.stop_recording()


        else:
            print '-'

        time.sleep(0.4)

    except IOError:
        print "Error"

