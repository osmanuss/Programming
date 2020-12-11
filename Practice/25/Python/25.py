import random
def Bozosort(first, second=0, third='', fourth=True):
    if third == '':
            real_sort = first.copy()
            real_sort.sort()
            if not fourth:
                real_sort.reverse()
            while first != real_sort:
                x1 = random.randrange(0, len(first))
                x2 = random.randrange(0, len(first))
                
                while x1 == x2:
                    x2 = random.randrange(0, len(first))
                    
                first[x1], first[x2] = first[x2], first[x1] 
            return first
    else:
        return Bozosort([first, second, third], fourth=fourth)
if __name__ == "__main__":
    n = int(input())
    x = list(map(int, input().split()))
    f, s, t = x[0], x[1], x[2]
    Bozosort(x)
    x_sqr = tuple(x)
    print(" ".join(map(str, x)))
    Bozosort(x, fourth=False)
    print(" ".join(map(str, x)))
    print(" ".join(map(str, x_sqr)))
    print(" ".join(map(str, x)))
    print(" ".join(map(str, Bozosort(f, s, t))))
    print(" ".join(map(str, Bozosort(f, s, t, False))))
