# -*- coding:utf-8 -*
from datetime import datetime

TODAY = datetime.now().strftime('%y%m%d') + '.csv'

# Lot No 入力
while True:
    print("Input Lot No:")
    lotno = input()
    
    if lotno[0:2] == 'LT' :

        while True:
            print("Process? :")
            process = input()
            if process[0:2] == 'PS' :
                break
            else :
                print("Wrong Process ID")

        ST_FLAG = False

        while True:
            print("INPUT: operate command?")
            command = input()

            # 開始
            if command == 'ST001' :
                print("CMD: Start make")
                ST_FLAG = True
                ST_TIME = datetime.now()

            # 終了
            elif command == 'ED001' and ST_FLAG == True:
                print("CMD: End make")
                ED_TIME = datetime.now()
                print(lotno + ',' + process + ',' + ST_TIME.strftime('%Y-%m-%d %H:%M:%S') + ',' + ED_TIME.strftime('%Y-%m-%d %H:%M:%S') + ',' + str(abs(ST_TIME - ED_TIME)) )

                file_ob = open(TODAY, 'a')
                file_ob.write(lotno + ',' + process + ',' + ST_TIME.strftime('%Y-%m-%d %H:%M:%S') + ',' + ED_TIME.strftime('%Y-%m-%d %H:%M:%S') + ',' + str(abs(ST_TIME - ED_TIME)) + '\n' )
                file_ob.close()
                break
            elif command == 'CN001':
                print("CMD: Cancel")
                break
            else:
                print("ERR: Unknown Command")
    else:
        print("ERR: Wrong Lot No")

