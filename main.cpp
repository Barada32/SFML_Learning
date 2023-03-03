#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
//#define TELEPOR_HERO
#define TIME_BINDING
#define MOVE_KEYBOARD_MOUSE
#define CREATE_SPRITE
#define VARIABLES
int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML_Learning!"/*,sf::Style::Fullscreen*/);//����� RenderWindow �������  ���� ��� VideoMode ������ ����������


#ifdef CREATE_SPRITE
	sf::Image heroimage;//create object Image
	heroimage.loadFromFile("images/hero.png");//load file hero to object heroimage
	heroimage.createMaskFromColor(sf::Color(0, 0, 0));//RGB filter of transparent(����������) backside from file of hero.png
	//if backside of picture is not transparent this function can do this

	sf::Texture herotexture;//create texture
	herotexture.loadFromImage(heroimage);//transfer to texture image from herimage

	sf::Sprite herosprite;//create Sprite
	herosprite.setTexture(herotexture);//transfer to herosprite image from herotexture
	herosprite.setTextureRect(sf::IntRect(0, 245, 40, 50));//������ ������� �,�,������,������.
	float currentframe = 0;//������ ���������� �������� �����
#endif // CREATE_SPRITE 

#ifdef VARIABLES
	herosprite.setPosition(100, 50);//set a coordinates to start position 
	float heroteleporttimer = 0;//teleport  hero after 3 second
	sf::Clock clock;//create variable  of time, to binding(��������) speed to time and not to use processor or loading


#endif // VARIABLES

	while (window.isOpen())//���� ���� ������� �������� �������.��� ������������ ����
	{
#ifdef TIME_BINDING

		float time = clock.getElapsedTime().asMicroseconds();//get a last time in microseconds
		clock.restart();//restart time
		time /= 700;//speed of game   

#endif // TIME_BINDING


		sf::Event event;//������������ ��� ��� �������� ���� 
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
#ifdef TELEPORT_HERO
		heroteleporttimer += time;//add time to variable time
		if (heroteleporttimer > 3000)//after 3000 seconds change position of hero and zero timer
		{
			herosprite.setPosition(0, 120);
			heroteleporttimer = 0;
		}
#endif // TELEPORT_HERO


#ifdef MOVE_KEYBOARD_MOUSE 

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			currentframe += 0.005 * time;//���������� ��� ����������� �� ������ ���������� ������� �� 6 
			if (currentframe > 6)currentframe -= 6;//���� ������ � ����� 6 �� ������������ �����
			herosprite.setTextureRect(sf::IntRect(40  * int(currentframe), 245, 40, 50));/*���������� �� ����������� � ������ �������������� ��������
			���������� �������� ��������� � ����� currentframe ������� �� ������ ���������� ����� ���� � �.� */
			herosprite.move(0.1 * time, 0);//���������� ���� �������� ��������� ������
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{  
			currentframe += 0.005 * time;//���������� ��� ����������� �� ������ ���������� ������� �� 6 
			if (currentframe > 6)currentframe -= 6;//���� ������ � ����� 6 �� ������������ �����
			herosprite.setTextureRect(sf::IntRect(40 * int(currentframe)+40, 245, -40, 50));
			/*������ ������� �,�,������,������.
			���������� �� ����������� � ������ �������������� ��������
			���������� �������� ��������� � ����� currentframe ������� �� ������ ���������� ����� ���� � �.�
			*/
			herosprite.move(-0.1 * time, 0);}//���������� ���� �������� ��������� �����

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { herosprite.move(0, -0.1 * time); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { herosprite.move(0, 0.1 * time); }
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { herosprite.setColor(sf::Color::Red); }
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) { herosprite.setColor(sf::Color::Blue); }
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) { herosprite.setColor(sf::Color::Green); }
#endif // MOVE_KEYBOARD_MOUSE



		window.clear();//������� ����
		window.draw(herosprite);//������ ������
		window.display();//
	}

	return 0;
}
//sf::CircleShape shape(100.f);//��������� ������� ������ ������ ���� 
//shape.setFillColor(sf::Color::Green);//������� ������� ������� ������