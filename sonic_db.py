import time,sys
import grovepi
import MySQLdb


conn = MySQLdb.connect(
        user='yuya',
        passwd='yuya',
        host='192.168.4.139',
        db='iot'
)


ultrasonic_ranger = 2
cur = conn.cursor()

while True:
    range = grovepi.ultrasonicRead(ultrasonic_ranger)
    print("Range:" + str(range))

#    sql = 'INSERT INTO sonic_range (`range`) VALUES(%s)'

    cur.execute("INSERT INTO sonic_range (`range`) VALUES("+str(range)+")")
    conn.commit()
    time.sleep(1)



