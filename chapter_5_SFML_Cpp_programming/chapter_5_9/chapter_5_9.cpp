#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"vector"
#include<time.h>

using namespace sf;

int main()
{

	srand(time(NULL));
	//화면
	VideoMode vd(640, 480);
	RenderWindow window(vd, "this is test");
	window.setFramerateLimit(60);

	//플레이어
	Texture doodugi_tx;
	Sprite doodugi;
	doodugi_tx.loadFromFile("./doodugi.png");
	doodugi.setTexture(doodugi_tx);
	doodugi.setScale(0.4, 0.4);
	int px = 320;
	int py = 380;
	doodugi.setPosition(px, py);



	//미사일
	/*CircleShape laser(10.f);
	laser.setFillColor(Color::Green);
	laser.setPosition(300, 300);*/

	//적군
	Texture ddong_tx;
	Sprite ddong;
	ddong_tx.loadFromFile("./ddong.png");
	ddong.setTexture(ddong_tx);
	ddong.setScale(0.3, 0.3);
	int dx = rand() % 640;
	int dy = 0;
	ddong.setPosition(dx, dy);

	std::vector <Sprite> enemies;

	int enemyCool = 0;

	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.KeyPressed && event.key.code == Keyboard::Escape) {
				window.close();
			}
		}
		//키보드 입력
		if (Keyboard::isKeyPressed(Keyboard::Left) == true) {
			px -= 5;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) == true) {
			px += 5;
		}

		// 적군 배열에 카피해서 넣기 
		enemyCool++;
		if (enemyCool > 1) {
			ddong.setPosition(rand() % 640, 0);
			enemies.push_back(ddong);
			enemyCool = 0;
		}
		//배경
		Color cr(0, 0, 0);
		window.clear(cr);
		// 적군 움직이기 
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].move(0, 5.f);
		}
		//적군 그리기
		for (int i = 0; i < enemies.size(); i++) {
			window.draw(enemies[i]);
		}
		// 바운더리 체크 제거하기 
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].getPosition().y > 480) {
				enemies.erase(enemies.begin() + i);
				std::cout << enemies.size() << std::endl;
			}
		}
		// 적군 - 플레이어 충돌체크 
		for (int i = 0; i < enemies.size(); i++) {
			// 충돌체크 1단계: 내 플레이어 사각형 얻기
			FloatRect rect_Player = doodugi.getGlobalBounds();
			// 충돌체크 2단계: 적군의 사격형 얻기 
			FloatRect rect_Enemy = enemies[i].getGlobalBounds();
			// 충돌체크 3단계: intersect 이용해서 두 사각형이 겹치는지 점검 
			if (rect_Player.intersects(rect_Enemy)) {
				std::cout << "collide" << std::endl;
				enemies.erase(enemies.begin() + i);
			}
		}

		// 플레이어 그리기 
		doodugi.setPosition(px, py);
		window.draw(doodugi);
		window.display();
	}
}