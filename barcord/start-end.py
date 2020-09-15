# -*- coding:utf-8 -*-
from datetime import datetime
from os import makedirs

dir_='./data/'
makedirs(dir_, exist_ok=True)

dataID='01'

while True:
    ans=input()

    now_ = datetime.now()
    date_ = now_.strftime('%y%m%d')
    file_name = dir_+ dataID + date_ + '.csv'

    try:
        file_object = open(file_name,'r')
    except:
        file_object = open(file_name,'w')
        file_object.write(dataID+'_Date,'+now_.strftime('%Y/%m/%d')+'¥r¥n')
    file_object.close()

    file_object = open(file_name,'a')
    file_object.write(ans+','+ now_.strftime('%H:%M:%S') +'¥r¥n')
    file_object.close()