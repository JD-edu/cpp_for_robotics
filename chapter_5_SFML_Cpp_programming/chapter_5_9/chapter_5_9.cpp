#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy();
    void update(sf::RenderWindow& win);
    sf::CircleShape c;
private:

};
Enemy::Enemy() {
    c.setFillColor(sf::Color::Yellow);
    c.setPosition(rand()%640, 0);
    c.setRadius(40);
}

void Enemy::update(sf::RenderWindow& win) {
    int y = c.getPosition().y;
    if (y > 600) {
        y = 0;
        c.setPosition(rand() % 800, y);
    }
    c.move(0, 5);
    win.draw(c);
}

class Zigzag : public Enemy { 
public:
    int i = 1;
    void update(sf::RenderWindow& win) {
        int y = c.getPosition().y;
        if (y > 600) {
            y = 0;
            c.setPosition(rand() % 800, y);
        }
        i *= -1;
        c.move(20 * i, 5);
        win.draw(c);
    }
};

int main()
{
    Enemy e1;
    Zigzag z1;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    sf::Texture texture;
    texture.loadFromFile("./ddong.png");

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        e1.update(window);
        z1.update(window);
        window.display();
    }

    return 0;
}