import pygame
import random

pygame.init()

screen_width = 800
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("슈팅 게임 - 플레이어 조종")

black = (0, 0, 0)
red = (255, 0, 0)
blue = (0, 0, 255)

# 플레이어 설정
player_x = screen_width // 2
player_y = screen_height - 50
player_radius = 25
player_speed = 5

# 적군 설정
enemy1_x = random.randint(50, 750)
enemy1_y = 100
enemy_radius = 20

# 프레임 레이트 설정
clock = pygame.time.Clock()
FPS = 60

running = True
while running:
    clock.tick(FPS)  # 초당 60프레임으로 제한

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # 키보드 입력 처리
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:  # 왼쪽 화살표
        player_x -= player_speed
        if player_x < player_radius:  # 화면 밖으로 나가지 않게
            player_x = player_radius
    if keys[pygame.K_RIGHT]:  # 오른쪽 화살표
        player_x += player_speed
        if player_x > screen_width - player_radius:
            player_x = screen_width - player_radius

    # 화면 그리기
    screen.fill(black)

    # 플레이어 그리기
    pygame.draw.circle(screen, blue, (player_x, player_y), player_radius)

    # 적군 그리기
    pygame.draw.circle(screen, red, (enemy1_x, enemy1_y), enemy_radius)

    pygame.display.flip()

pygame.quit()
