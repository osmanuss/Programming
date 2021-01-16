from flask import Flask, request, jsonify
from datetime import datetime
import openpyxl

def getcell(bigData):
    i = 2
    while bigData[i][0].value != None:
        i += 1
    return i

cache = []

def Chek(info):
    global cache
    num = getcell(info)
    for i in range(len(cache)):
        for j in range(len(cache[i]['check'])):
            info[num][0].value = num - 1
            info[num][1].value = cache[i]['user_id']
            info[num][2].value = cache[i]['datetime']
            info[num][3].value = cache[i]['check'][j]['item']
            info[num][4].value = cache[i]['check'][j]['price']
            num += 1
    del num, i, j
    return info


def Excel():
    try:
        book = openpyxl.open(r'C:\Users\Inquisitor\source\repos\Programming\Lab\02\excel\data.xlsx', read_only=False)
    except:
        book = openpyxl.Workbook()
    chekinfo = book.active
    if chekinfo['A1'].value == None:
        chekinfo['A1'] = 'N'
        chekinfo['B1'] = 'User ID'
        chekinfo['C1'] = 'Datetime'
        chekinfo['D1'] = 'Item'
        chekinfo['E1'] = 'Prise'
    chekinfo = Chek(chekinfo)
    book.save(r'C:\Users\Inquisitor\source\repos\Programming\Lab\02\excel\data.xlsx')
    book.close()


def generator(data):
    global cache
    data['datetime'] = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
    cache.append(data)
    if len(cache) >= 1000:
        Excel()
        cache = []


app = Flask(__name__)

@app.route('/', methods=['POST', 'GET'])

def index():
    if request.method == 'POST':
        data = request.json
        generator(data)
        return 'OK'
    elif request.method == 'GET':
        return 'нужен POST запрос'
if __name__ == "__main__":
	app.run()