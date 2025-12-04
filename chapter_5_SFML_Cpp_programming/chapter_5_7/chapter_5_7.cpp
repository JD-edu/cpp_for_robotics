#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    int y1 = 0;
    int x1 = 100;
    int y2 = 0;
    int x2 = 200;

    sf::RenderWindow window(sf::VideoMode(640, 480), "My SFML Window");

    // 빨간 원 생성 (반지름 20)
    sf::CircleShape circle1(20.f);
    circle1.setFillColor(sf::Color::Red);
    sf::CircleShape circle2(20.f);
    circle2.setFillColor(sf::Color::Red);

    // 아군 우주선 
    sf::CircleShape blue(30.f);
    blue.setFillColor(sf::Color::Blue);

    // 원의 위치 설정
    circle1.setPosition(300, y1);
    circle2.setPosition(200, y2);
    blue.setPosition(320, 430);

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }

            // 아래의 키보드처리 코드는 event 방식
            /*else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)
                    blue.move(-10.f, 0.f); // 왼쪽으로 이동
                else if (event.key.code == sf::Keyboard::D)
                    blue.move(10.f, 0.f); // 오른쪽으로 이동
            }*/
        }

        // 아래 키보드 처리 코드는 polling 방식
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            blue.move(-5.0f, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            blue.move(5.0f, 0);
        }

        // 빨간 원들의 움직임 처리
        y1++;
        if (y1 > 480) {
            y1 = (rand() % 200)*-1;
            x1 = rand() % 640;
        }

        y2++;
        if (y2 > 480) {
            y2 = (rand() % 200) * -1;
            x2 = rand() % 640;
        }

        circle1.setPosition(x1, y1);
        circle2.setPosition(x2, y2);

        window.clear(sf::Color::Black);
        window.draw(circle1);
        window.draw(circle2);
        window.draw(blue);
        window.display();
    }

    return 0;
}
