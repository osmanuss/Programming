import re

bilets = input()
s = input()
case1 = r"a[0-9]{2}[a-z]55661"
case2 = r"a[a-z][0-9]{2}55661"
case3 = r"a[0-9][a-z][0-9]55661"
answer = re.findall(case1, s)
answer.extend(re.findall(case2, s))
answer.extend(re.findall(case3, s))
print(' '.join(answer) if answer != [] else -1)
