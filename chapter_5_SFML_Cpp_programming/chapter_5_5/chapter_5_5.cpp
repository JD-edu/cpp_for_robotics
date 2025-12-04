#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "My SFML Window");
    // 빨간 원 생성 (반지름 20) ============
    sf::CircleShape circle1(20.f);
    circle1.setFillColor(sf::Color::Red);

    // 원의 위치 설정 (창의 중앙)
    circle1.setPosition(200,200);

    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        circle1.setPosition(200, 200);
        window.clear(sf::Color::Black);
        window.draw(circle1); // 원 그리기
        window.display();
    }
    return 0;
}
