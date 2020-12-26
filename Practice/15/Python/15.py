from random import randrange
print("Здравствуйте")
x, z = 1, 1
while x == 1:
    print("Сейчас я загадаю число от нуля до ста, и вы попробуете угадать его. Ну что ж, приступаем!")
    b = randrange(0, 101)
    a = int(input())
    while z < 5:
        z = z + 1
        if a>b:
            print("Загаданное число меньше")
        elif a < b:
            print("Загаданное число больше")
        else:
            break
        a = int(input())
    if a == b:
        print("Поздравляю! Вы угадали")
    else:
        print("Вы проиграли. Было загадано: ", b)
    print("Хотите начать сначала?")
    x = int(input())
