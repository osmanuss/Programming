out = print

def create(ln, x0 = 0, c = 0):
    arr = []
    arr.append(x0)
    for i in range(1, ln):
        arr.append(arr[i-1] + c)
    return arr

def sort(arr):
    for i in range(1, len(arr)):
        a = arr[i]
        b = i-1
        while b >=0 and a < arr[b]:
                arr[b+1] = arr[b]
                b -= 1
        arr[b+1] = a
    return arr

def print(arr):
    out('[', end='')
    for i in range(len(arr) - 1):
        out(arr[i], end=', ')
    out(arr[len(arr) - 1], ']', sep='')
    return arr

out('Введите длину массива, и два числа: начальный член и шаг арифметической прогрессии')
ln = int(input())
x0 = int(input())
c = int(input())
arr = create(ln, x0, c)
sort(arr)
print(arr)
