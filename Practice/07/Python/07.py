import math
x = input()
if x == '1':
	a, b, c = map(float, [input(), input(), input()])
	p = ((a+b+c)/2)
	s = math.sqrt(p*(p - a) * (p - b) * (p - c))
	print("S = ", s)
elif x == '2':
        a1, a2, b1, b2, c1, c2 = map(int, input("Введите a1, a2, b1, b2, c1, c2 через пробел: ").split())
        a = math.sqrt((a1 - b1) * (a1 - b1) + (a2 - b2) * (a2 - b2))
        b = math.sqrt((c1 - b1) * (c1 - b1) + (c2 - b2) * (c2 - b2))
        c = math.sqrt((c1 - a1) * (c1 - a1) + (c2 - a2) * (c2 - a2))
        p = ((a+b+c)/2)
        s = math.sqrt(p*(p - a) * (p - b) * (p - c))
        print("S = ", s)
else:
	print("Ошибочный ввод")
input()
