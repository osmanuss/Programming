a = int(input())
k = 0
for i in range(2,a):
    if ((a % i) == 0):
        k = k + 1
        break
if (k > 0):
    print("Составное")
else:
    print("Простое")
    
        
