import pygame
import json
import requests

pygame.init()

display_width = 750
display_height = 774

display = pygame.display.set_mode((display_width, display_height))
pygame.display.set_caption('4 в ряд')

icon = pygame.image.load('icon.png')
pygame.display.set_icon(icon)

balls = [None, pygame.image.load('red.png'), pygame.image.load('yellow.png'), pygame.image.load('red_strih.png'),
         pygame.image.load('yellow_strih.png')]
balls_options = [90, 80]

step_red = pygame.image.load('step_red.png')
step_yellow = pygame.image.load('step_yellow.png')
win_red = pygame.image.load('win_red.png')
win_yellow = pygame.image.load('win_yellow.png')

clock = pygame.time.Clock()

cordi = [
    [[15, 137], [121, 137], [226, 137], [331, 137], [436, 137], [541, 137], [645, 137]],
    [[15, 242], [121, 242], [226, 242], [331, 242], [436, 242], [541, 242], [645, 242]],
    [[15, 346], [121, 346], [226, 346], [331, 346], [436, 346], [541, 346], [645, 346]],
    [[15, 451], [121, 451], [226, 451], [331, 451], [436, 451], [541, 451], [645, 451]],
    [[15, 556], [121, 556], [226, 556], [331, 556], [436, 556], [541, 556], [645, 556]],
    [[15, 661], [121, 661], [226, 661], [331, 661], [436, 661], [541, 661], [645, 661]]
]


def otrisovka():
    global array
    for i in range(6):
        for j in range(7):
            for k in 1, 2, 3, 4:
                if array[i][j] == k:
                    display.blit(balls[k], (cordi[i][j]))


def run_game():
    game = True
    field = pygame.image.load('field.png')

    while game:
        global array
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        r = requests.get('http://localhost:1234/').content.decode("UTF8")
        file = json.loads(r)

        # with open("../gameplay/example.json", "r", encoding="utf-8") as infarmacia:
        #     file = json.load(infarmacia)
        step = file["step"]
        array = file["array"]

        display.blit(field, (0, 0))

        otrisovka()

        if step == 0:
            display.blit(step_red, (0, 0))
        elif step == 1:
            display.blit(step_yellow, (0, 0))
        elif step == 2:
            display.blit(win_red, (0, 0))
        elif step == 3:
            display.blit(win_yellow, (0, 0))

        pygame.display.update()
        clock.tick(1)


run_game()
