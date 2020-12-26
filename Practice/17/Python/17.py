x1, x2, a, k, h, j, l, f = 0, 0, 0, 0, 0, 0, 0, 37
n = [0] * f
r = [1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36]
for i in range (f):
    n[i] = 0
while (1):
    x = int(input())
    n[x] = n[x] + 1
    for k in range (18):
        if (x == r[k]):
            x1 = x1 + 1
            break
        elif k == 17:
            x2 = x2 + 1
    for l in range (f):
        if (n[l] > a):
            a = n[l]
    for j in range (f):
        if (n[j] == a):
            print (j, end = ' ')
    print ("\n")
    for h in range (f):
        if (n[h] == 0):
            print (h, end = ' ')
    print ("\n", x1, " ", x2, "\n")
