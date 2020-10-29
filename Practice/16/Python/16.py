a = int(input())

arr = []

for i in range(a):
    arr.append(input())

vec = []
is_existed = 0

for i in range(a):
    if arr[i][0] == 'a' and arr[i][8] == '1' and arr[i][7] == '6' and arr[i][6] == '6' and arr[i][5] == '5' and arr[i][4] == '5':
        vec.append(arr[i])
        is_existed = 1

if is_existed:
    for i in range(len(vec)):
        print(vec[i])
else:
    print("-1\n")
