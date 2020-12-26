def factorise(x):
    mults = []
    i = 2
    while i <= x + 1:
        if x % i == 0:
            mults.append(i)
            x //= i
            i -= 1
        i += 1
    ans = [str(i) + "^" + str(mults.count(i)) if mults.count(i) > 1 else str(i) for i in set(mults)]
    return "*".join(ans)
n = int(input())
print (factorise(n))
