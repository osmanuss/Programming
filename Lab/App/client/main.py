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


class Button:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.inactive_color = (13, 162, 58)
        self.active_color = (23, 204, 58)

    def draw(self, x, y, message):
        mouse = pygame.mouse.get_pos()
        click = pygame.mouse.get_pressed()

        if (x < mouse[0] < x + self.width) and (y < mouse[1] < y + self.height):
            pygame.draw.rect(display, self.active_color, (x, y, self.width, self.height))

            if click[0] == 1:
                p = requests.get('http://localhost:1234/new').content.decode("UTF8")
        else:
            pygame.draw.rect(display, self.inactive_color, (x, y, self.width, self.height))
        print_text(message, x, y)


def otrisovka():
    global array
    for i in range(6):
        for j in range(7):
            for k in range(1, 5):
                if array[i][j] == k:
                    display.blit(balls[k], (cordi[i][j]))


def print_text(message, x, y, font_size=30, font_color=(0, 0, 0), font_type='PingPong.ttf'):
    font_type = pygame.font.Font(font_type, font_size)
    text = font_type.render(message, True, font_color)
    display.blit(text, (x, y))


def run_game():
    game = True
    field = pygame.image.load('field.png')
    button = Button(100, 50)

    while game:
        global array
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        r = requests.get('http://localhost:1234/').content.decode("UTF8")
        file = json.loads(r)
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

        koef = 1
        for i in range(6):
            for j in range(7):
                if array[i][j] != 0:
                    koef = 1
                else:
                    koef = 0
                    break
            if koef == 0:
                break

        if step > 1 or koef == 1:
            button.draw(650, 76, 'Again?')

        pygame.display.update()
        clock.tick(7)


run_game()
