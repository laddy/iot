import csv
from escpos.printer import Usb
from escpos import *
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

filepath = 'unitlist.csv'

def print_bar(name) :
    width = 580
    height = 100

    image = Image.new('1', (width, height), 255)
    draw = ImageDraw.Draw(image)
    #font1 = ImageFont.truetype('clamp-1m-w4-regular.ttf', 50, encoding='unic')
    #draw.text((0, 0), "Barcode" + " ", font=font1, fill=0)
    font2 = ImageFont.truetype('Code39Barcode.ttf', 55)
    draw.text((0, 00), "*"+name+"*" + " ", font=font2, fill=0)

    p = Usb(0x0416, 0x5011, 0, 0x81, 0x03)
    p.text(" "+name+"\n")
    p.image(image)
    p.qr(name, size=6)
    #p.barcode("1324354", "CODE39")
    #p.barcode("{B012ABCDabcd", "CODE39", function_type="B")
    p.cut()
    return ''

def counter(parts) :
    count = input('個数を読み込んでください>>')

    for subno in range(1, int(count)+1) :
        print(parts+'-'+str(subno))
        print_bar(parts+'-'+str(subno))
    
    return ''
 

#main = ['TANJIRO123', 'INOSUKE567','ZENITU8901', 'ZENITU8904', 'UROKODAKI5', 'INOSUKE864', 'RENGOKU256', 'UBUYASIKI8', 'TANJIRO678', 'TANJIRO561']
#sub = ['AOI2856348', 'NEZUKO1234', 'KOCHO12345', 'UBUYASIKI4','KOCHO98765', 'NEZUKO9268', 'RENGOKU872','ZENITU8543', 'KOCHO52856', 'NEZUKO9876']
# ここまでをCSVファイルからの読み込みとしたい
with open(filepath) as f:
    reader = csv.reader(f)
    ulist = [row for row in reader]

print("csv done\n")

while True :
    parts = input('パーツナンバーを読み込んでください>>')#ここからは全てバーコードリーダーからの読み込みとしたい

    # 正パーツ0 枝1 無し2
    branch = 2
    for i in ulist:
        if parts in i and "0" == i[2] :
            name = i[1]
            branch = 0
            break
        elif parts in i and "1" == i[2] :
            branch = 1
            break

    if 0 == branch :
        print_bar(parts)
    elif 1 == branch :
        print('枝番が必要です')
        counter(parts)

    else:
        print('未登録のパーツです。バーコードを仮発行します')
        counter(parts)

        ## CSVファイルへ追記
        with open(filepath, 'a') as f:
            writer = csv.writer(f)
            writer.writerow(['0', parts, 'UNKNOWN'])
        print("未登録コード登録しました")


"""
draw.text((0, 0), "日本語" + " ", font=font, fill=0)
font = ImageFont.truetype('clamp-1m-w4-regular.ttf', 28, encoding='unic')
draw.text((0, 82), "abcdefghijklmnopqrstuvwxyz", font=font, fill=0)
draw.text((0, 112), "ABCDEFGHIJKLMNOPQRSTUVWXYZ", font=font, fill=0)
draw.text((0, 142), "1234567890" + " ", font=font, fill=0)
draw.text((0, 172), "!\"#$%&'()=~|+*<>?_{}" + " ", font=font, fill=0)

p = Usb(0x0416, 0x5011, 0, 0x81, 0x03)
p.text(" Hello World\n")
p.barcode("{B012ABCDabcd", "CODE128", function_type="B")
p.image("google.jpg")
#p.qr("You can readme from your smartphone")
# Print barcode
p.barcode('1324354657687','EAN13',64,2,'','')
"""


 
