import math
h1, m1 = map(int, input("Введите время прибытия первого человека ").split(':'))
h2, m2 = map(int, input("Введите время прибытия второго человека ").split(':'))
m1 = m1 + 60*h1
m2 = m2 + 60*h2
r = m1 -m2
k = math.fabs(r)
if k <= 15:
	print("Встреча состоится")
else:
	print("Встреча не состоится")
input()
