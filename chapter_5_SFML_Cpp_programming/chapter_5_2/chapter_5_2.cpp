// main.cpp
#include <SFML/Graphics.hpp>

int main()
{
    // 800x600 해상도의 윈도우 생성
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML 환경 설정 테스트");

    // 메인 루프
    while (window.isOpen())
    {
        // 이벤트 처리
        sf::Event event;
        while (window.pollEvent(event))
        {
            // 윈도우 닫기 이벤트
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 화면을 파란색으로 지우기
        window.clear(sf::Color::Blue);

        // 화면 표시
        window.display();
    }

    return 0;
}
