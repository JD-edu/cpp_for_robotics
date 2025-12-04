import pygame

pygame.init()

# 화면 설정
screen_width = 800
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("빨간 공 띄우기")

# 색상 정의
black = (0, 0, 0)
red = (255, 0, 0)

# 빨간 공 설정
enemy_x = 400
enemy_y = 100
enemy_radius = 20

# 게임 루프
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # 화면 그리기
    screen.fill(black)

    # 빨간 공 그리기
    pygame.draw.circle(screen, red, (enemy_x, enemy_y), enemy_radius)

    pygame.display.flip()

pygame.quit()
