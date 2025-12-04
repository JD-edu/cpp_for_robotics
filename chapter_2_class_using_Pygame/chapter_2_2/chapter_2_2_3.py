import pygame
import random

pygame.init()

screen_width = 800
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("빨간 공 여러 개")

black = (0, 0, 0)
red = (255, 0, 0)

# 빨간 공 4개의 위치 (변수가 벌써 8개!)
enemy1_x = random.randint(50, 750)
enemy1_y = random.randint(50, 200)
enemy2_x = random.randint(50, 750)
enemy2_y = random.randint(50, 200)
enemy3_x = random.randint(50, 750)
enemy3_y = random.randint(50, 200)
enemy4_x = random.randint(50, 750)
enemy4_y = random.randint(50, 200)
enemy_radius = 20

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill(black)

    # 빨간 공 4개 그리기 (코드 반복!)
    pygame.draw.circle(screen, red, (enemy1_x, enemy1_y), enemy_radius)
    pygame.draw.circle(screen, red, (enemy2_x, enemy2_y), enemy_radius)
    pygame.draw.circle(screen, red, (enemy3_x, enemy3_y), enemy_radius)
    pygame.draw.circle(screen, red, (enemy4_x, enemy4_y), enemy_radius)

    pygame.display.flip()

pygame.quit()
