import pygame

# Pygame 초기화
pygame.init()

# 화면 크기 설정
screen_width = 800
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("나의 첫 Pygame 윈도우")

# 색상 정의
black = (0, 0, 0)

# 게임 루프
running = True
while running:
    # 이벤트 처리
    for event in pygame.event.get():
        if event.type == pygame.QUIT:  # 윈도우 닫기 버튼 클릭
            running = False

    # 화면 그리기
    screen.fill(black)  # 배경을 검은색으로 채우기

    # 화면 업데이트
    pygame.display.flip()

# Pygame 종료
pygame.quit()
