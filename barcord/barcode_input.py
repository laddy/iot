# -*- coding:utf-8 -*
import sqlite3
from datetime import datetime

try :
    # データベースに接続する
    con = sqlite3.connect('/tmp/iot.db')
    cur = con.cursor()

    # テーブル作成もし存在したら作らない
    cur.execute("CREATE TABLE IF NOT EXISTS barcode2 (\
        name VARCHAR(255),\
        lotno VARCHAR(255),\
        process VARCHAR(255),\
        starttime VARCHAR(255),\
        completetime VARCHAR(255),\
        quantity INTEGER)")
except :
    print("Error!!")    
    con.close()

# ユーザ名入力
print ("Employee name?: ")
name = input()

# ロットナンバー入力
while True:
    print("Input Lot No:")
    lotno = input()
    
    # ロットナンバーの形の確認 (TH52-333xxxxxx)
    if lotno[0:2].isalpha() and lotno[2:4].isdecimal() :

        # 作業種別入力
        while True:
            print("Process? :")
            process = input()

            # 入力データが作業種別の形 (WELD-0002)
            if process[0:4].isalpha() :
                break
            else :
                print("Wrong Process ID")

        # いきなり終了できないように目印
        ST_FLAG = False

        # 作業開始・終了
        while True:
            print("INPUT: operate command?")
            command = input()

            # 開始
            if command == 'START' :
                ST_FLAG = True
                ST_TIME = datetime.now()
                print("Start: " + ST_TIME.strftime('%Y-%m-%d %H:%M:%S'))
            # 終了
            elif command == 'FINISH' and ST_FLAG == True :
                ED_TIME = datetime.now()
                print("End: " + ED_TIME.strftime('%Y-%m-%d %H:%M:%S'))
                print(name + ',' + lotno + ',' + process + ',' + ST_TIME.strftime('%Y-%m-%d %H:%M:%S') + ',' + ED_TIME.strftime('%Y-%m-%d %H:%M:%S') + ',' + str(abs(ST_TIME - ED_TIME)) )

                print("Quantity: ")
                quantity = input()

                cur.execute("INSERT INTO barcode2 VALUES(?, ?, ?, ?, ?, ?)", (name, lotno, process, ST_TIME, ED_TIME, quantity))
                con.commit()
                print("==== INSERT DATA ====")
                break
            else:
                print("ERR: Unknown Command")
    else:
        print("ERR: Wrong Lot No")
