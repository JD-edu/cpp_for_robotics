import pygame
import random

pygame.init()

screen_width = 800
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("슈팅 게임 - 적군 이동")

black = (0, 0, 0)
red = (255, 0, 0)
blue = (0, 0, 255)

# 플레이어 설정
player_x = screen_width // 2
player_y = screen_height - 50
player_radius = 25
player_speed = 5

# 적군 설정
enemy_x = random.randint(50, 750)
enemy_y = 0
enemy_radius = 20
enemy_speed = 2

clock = pygame.time.Clock()
FPS = 60

running = True
while running:
    clock.tick(FPS)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # 키보드 입력 처리
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:
        player_x -= player_speed
        if player_x < player_radius:
            player_x = player_radius
    if keys[pygame.K_RIGHT]:
        player_x += player_speed
        if player_x > screen_width - player_radius:
            player_x = screen_width - player_radius

    # 적군 이동
    enemy_y += enemy_speed

    # 적군이 화면 아래로 나가면 다시 위에서 시작
    if enemy_y > screen_height + enemy_radius:
        enemy_y = -enemy_radius
        enemy_x = random.randint(enemy_radius, screen_width - enemy_radius)

    # 화면 그리기
    screen.fill(black)
    pygame.draw.circle(screen, blue, (player_x, player_y), player_radius)
    pygame.draw.circle(screen, red, (enemy_x, int(enemy_y)), enemy_radius)

    pygame.display.flip()

pygame.quit()
