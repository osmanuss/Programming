import math
a, b, c = map(int, input("Вас приветствует программа по нахождению корня квадратного уравнения. Прошу вас ввести все переменные ").split())
if (a != 0) and (b != 0) and (c != 0) :
	d = (b * b) - (4 * a * c)
	if (d > 0):
		x1 = (-b + math.sqrt(d)) / (2*a)
		x2 = (-b - math.sqrt(d)) / (2*a)
		print("Корни вашего уравнения: ", x1, " " ,x2)
	if (d == 0):
		x1 = -b / 2*a
		print("Корень ашего уравнения: ", x1)
	if (d<0):
		print("Ваше уравнение не имеет корней")
if (a == 0 and b != 0 and c != 0):
	x1 = -(c / b) 
	print("Корень вашего уравнения: ", x1)
if (a != 0 and b == 0 and c != 0):
	if (c <= 0):
		x1 = math.sqrt(-c)
		x2 = -(math.sqrt(-c))
		print("Корни вашего уравнения: ", x1, " " ,x2)
	else:
		print("Ваше уравнение не имеет корней")
if (a != 0 and b != 0 and c == 0):
	x1 = 0
	x2 = -b
	print("Корни вашего уравнения: ", x1, " " ,x2)
if (a == 0 and b == 0 and c != 0):
	print("Ваше уравнение может иметь любой корень")
if ((a != 0 and b == 0 and c == 0) or (a == 0 and b != 0 and c == 0)):
	print("Корень вашего уравнения равен нулю")
