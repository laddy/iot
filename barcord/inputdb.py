import sqlite3

con = sqlite3.connect('/tmp/iot.db')
cur = con.cursor()

try :
    cur.execute("CREATE TABLE IF NOT EXISTS input(data text, date datetime)")

    while True:
        print("Input No:")
        input_code = input()
        if "end" != input_code :
            cur.execute("INSERT INTO input VALUES(?, CURRENT_TIMESTAMP)", (input_code, ))
            con.commit()
        else :
            break
except :
    print("Error!!")    
    con.close()

cur.execute("SELECT * FROM input")
for row in cur :
    print("input: " + str(row[0]) + "\t time: " + row[1])


