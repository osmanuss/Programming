z = ("hallo", "klempner", "das", "ist", "fantastisch", "fluggegecheimen")
x = str(input())
chars = [0] * 26
a = ord('a')
for word in z:
    for c in word:
        chars[ord(c) - a] += 1
res = 1
total = sum(chars)
for c in x:
    res *= chars[ord(c) - a] / total
    if (res == 0): break
print(res)
