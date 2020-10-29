a = int(input())
b = int(input())
res = 1
if (b > 0):
        for k in range(1, b+1):
                res *= a
        print(res)
elif (b < 0):
        for k in range(1, abs(b)+1):
                res *= a
        print(1.0/res)
else:
	print(1)
input()
