import itertools

x = int(input())
def count(a, syst):
    res = ['']
    while a > 0:
        res.append(str(a % syst))
        a //= syst
    res.reverse()
    xres = list('0' for i in range((x - len(res)+1)))
    xres.extend(res)
    xres.pop()
    return ''.join(xres)
letts = [i for i in input()]
letts_cop = set(letts)
array_opt = list(str(i) for i in range(x-1, 0, -1))
list_opt = []
if len(letts_cop) == x:
    print(' '.join([''.join(i) for i in itertools.permutations(r=x, iterable=''.join(letts))]))
else:
    for i in range(len(letts_cop) ** x):
        temp = count(i, len(letts_cop))
        if set(letts[int(i)] for i in temp).intersection(letts_cop) == letts_cop:
            list_opt = [letts[int(i)] for i in temp]
            print(''.join(list_opt), end = ' ')
        if list_opt == array_opt:
            break
input()
