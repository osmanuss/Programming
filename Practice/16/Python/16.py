import re

def match(ticket):
    return re.match("^a(?:(?:[a-z][0-9]{2})|(?:[0-9][a-z][0-9])|(?:[0-9]{2}[a-z]))55661$", ticket)

def validator():
    return [x for x in map(str, input().split(" ")) if match(x)]

while True:
    try:
        n = int(input("Введите число: "))

        if n < 1:
            print("Число меньше 1. Повторите ввод.")
            continue

        bilet = validator()

        print(' '.join(bilet) if bilet else -1)

        break

    except KeyboardInterrupt:
        break
