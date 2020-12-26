class drink:
    def __init__(self, name, price, V):
        self.price = int(price)
        self.name = name
        self.V = int(V)
        self.quantity = int(V) / int(price)
Si_cash = int(input())
menu = []
res = {}
cash_dos = False
cash = [Si_cash]
used = 0
for i in range(int(input())):
    a, b, c = input().split()
    menu.append(drink(a, b, c))
    if int(b) <= Si_cash:
        cash_dos = True
def alcomarket(x):
    mmax = 0
    flag = False
    for i in x:
        if i.quantity > mmax:
            mmax = i.quantity
            temp = i
    products = cash[0] // temp.price
    cash[0] = cash[0] % temp.price
    res[temp.name] = products, temp.V
    for i in x:
        if i.price <= cash[0]:
            flag = True
    if flag == True:
        x.pop(x.index(temp))
        alcomarket(x)
if cash_dos == False:
    print(-1)
else:
    alcomarket(menu)
    for i, j in res.items():
        if j[0] != 0:
            print(i, j[0])
            used += j[0] * j[1]
    print(used)
    print(''.join(map(str, cash)))
