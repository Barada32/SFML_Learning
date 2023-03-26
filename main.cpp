

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include"map.h"//���������� �����-��� ������ � ������
#include "view.h"//���������� ��� � ����� ������
#include "mission.h"//���������� ������ ��� �������� ���
using namespace sf;//��������� ����������� ����
using std::cin;
using std::cout;
using std::endl;


////////////////////����� ������////////////////////////
class Player { 

private: //�������� ����������, ���� ��� � ������ ������ ��� ��� 
	//��� ��������� �������� ����� ������ ������������� ����� ����(���� ������������� �����)
	//���� ����� �� ��������
protected:

public:
	bool  isMove, isSelect;//�������� ���������� ��������� �������� � ������ �������
	float x, y, w, h, dx, dy, speed = 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int playerScore, health;//����� ����������, �������� ���� ������ � �����
	bool life;//���������� �����, ����������
	int dir; //����������� (direction) �������� ������
	String File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������

	/*���- ������*/

	float getplayercoordinateX() {	//���� ������� ����� ������ ���������� �	
		return x;
	}
	float getplayercoordinateY() {	//���� ������� ����� ������ ���������� Y 	
		return y;
	}


	/*������������*/
	Player(String F, float X, float Y, float W, float H) {  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		dir = 0; speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false; isSelect = false; // ���������������� ���������� ����� � ������������

		File = F;//��� �����+����������
		w = W; h = H;//������ � ������
		image.loadFromFile("images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(41, 33, 59));//������� �������� �����-����� ����, ��� ���� ��� ���������� �� ��������.
		texture.loadFromImage(image);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������
		x = X; y = Y;//���������� ��������� �������
		sprite.setTextureRect(IntRect(0, 0, w, h));  //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
		sprite.setOrigin(w / 2, h / 2);//�������� �������
	}

	/*Methods*/
	//����� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	void update(float time)
	{
		switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
		{
		case 0: dx = speed; dy = 0;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
		case 1: dx = -speed; dy = 0;   break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
		case 2: dx = 0; dy = speed;   break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
		case 3: dx = 0; dy = -speed;   break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
		}

		x += dx * time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
		y += dy * time;//���������� �� ������

		speed = 0;//�������� ��������, ����� �������� �����������.
		sprite.setPosition(x, y); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.

		interactionWithMap();//�������� �������, ���������� �� �������������� � ������	
		if (health <= 0) { life = false; speed = 0; cout << "GameOVER"; }//���� ������ ������ ���� ����� 0, �� ������� � ��������� �������� ������ ����� ������
	}

	//����� �������������� � ������
	void interactionWithMap()
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
			for (int j = x / 32; j < (x + w) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy > 0)//���� �� ��� ����,
					{
						y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
					}
					if (dy < 0)
					{
						y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
					}
					if (dx > 0)
					{
						x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//���������� ���� �����
					}
				}

				if (TileMap[i][j] == 's') { //���� ������ ����� 's' (������)
					playerScore++;//���� ����� ������, ���������� playerScore=playerScore+1;
					TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
				}
				if (TileMap[i][j] == 'f') {
					health -= 40;//���� ����� ����������� � ���� ������,�� ���������� health=health-40;
					TileMap[i][j] = ' ';//������ ������
				}

				if (TileMap[i][j] == 'h') {
					health += 20;//���� ����� ��������,�� ���������� health=health+20;
					TileMap[i][j] = ' ';//������ ��������
				}
			}

	}

};


 

//#define MOVE_SELECTED_WITH_MOUSE //���������� ��� ������ �����
#define TAB_PRESSED_MISSION_SCORE_HEALTH_REALISE
#define MAP_TEXTURE
#define MISSION_SPRITE_PART_1
#define MISSION_SPRITE_PART_2
#define FONTS
#define VARIABLES
#define GAME_SPEED
#define PLAYER_MOUSE_MOOVE_PART_1
#define PLAYER_MOUSE_MOOVE_PART_2
//#define SPRITE_MOUSE_ROTATE // ���������� ��� ������ �����
#define SPRITE_ROTATE_MOVING_RIGHT_MOUSE
#define PLAYER_WSAD_MOVING
#define MOUSE_SCROLLING_WINDOW
#define CREATING_MAP_LEVELS
#define CAMERA_VIEW
#define MOUSE_CURSOR_VECTOR_POSITION
int main()
{
	randomMapGenerate();//�������� ���������� ������ � ������


	RenderWindow window(sf::VideoMode(640, 480), "����� ���� ����������"/*, Style::Fullscreen*/);//���������� ����� ������� ����
	////////////////_______________���������� �������_____________////////////////////////////
	view.reset(sf::FloatRect(0, 0, 640, 480));//������ "����" ������ ��� �������� ������� ���� ������. (����� ����� ������ ��� �����) ��� �� ���� �������������.


#ifdef FONTS
	Font font;//����� 
	font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setFillColor(Color::Black);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text.setStyle(Text::Regular);//������ �����.  
#endif //_______________�����_____________//


#ifdef MISSION_SPRITE_PART_1
	///��� ������ � ������� �� ������ �� ������� tab
	bool showMissionText = true;//���������� ����������, ���������� �� ��������� ������ ������ �� ������
	Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //���������� �����, ������� �������� ��������
	s_quest.setScale(0.6f, 0.6f);//���� ��������� ��������, => ������ ���� ������  
#endif //_______________������ � ������� ������ ������_____________//


#ifdef MAP_TEXTURE
	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/map.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������  
#endif //_______________������� �������� �����_____________//


#ifdef VARIABLES
	float CurrentFrame = 0;//���������� ������ ������� ����
	Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//���������� ������� �����, ����������������.
	int createObjectForMapTimer = 0;//���������� ������ ��� �������


	//���������� ��� �������������� ���������
	bool isMove = false;//���������� ��� ������ ���� �� �������
	float dX = 0;//���������� ������������� ������� �� �
	float dY = 0;//���������� �� �

	//���������� ���  �������� �� ������ �� ����� ��� � RTS
	int tempX = 0;//��������� ���������� ����� �.������� �� ����� ������� ���� ���� ����
	int tempY = 0;//��������� ���������� ����� Y 
	float distance = 0;//���������� ���������� �� ������� �� ���� �������  

	
	

#endif //_______________����������_____________//



	Player p("hero.png", 250, 250, 40.0, 50.0);//������� ������ p ������ player,������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.

	while (window.isOpen())
	{
#ifdef GAME_SPEED
		float time = clock.getElapsedTime().asMicroseconds();//������ ����� � �������������
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//������� ����� � �������� ��� ������, ���� ��� �����, ������������� ��� time ��� �� ����. ��� �� ��������� ������ ����
		clock.restart();
		time = time / 800;//�������� �� ������� � ��������� �������� �������� ���������
#endif //�������� ����

#ifdef MOUSE_CURSOR_VECTOR_POSITION
		Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
		Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)
		//std::cout << pixelPos.x << "\n";//������� �� ���������� � ������� ������� � ������� (��� �� ����� ������ ������ ����)
		//std::cout << pos.x << "\n";//������� �� �,������� ��������������� � ������� ����������
#endif // ������� ��� �������������� ��������� �����_


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		
#ifdef PLAYER_MOUSE_MOOVE_PART_1
			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
				if (event.key.code == Mouse::Left) {//� ������ �����
					if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
					{
						p.sprite.setColor(Color::Green);//������ ������ � �������,��� ����� ������ ������,��� �� ������ ��������� � ����� ������� ���
						p.isSelect = true;
					}
				}


			if (p.isSelect)//���� ������� ������
				if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
					if (event.key.code == Mouse::Right) {//� ������ ������
						p.isMove = true;//�� �������� ��������
						p.isSelect = false;//������ ��� �� ������
						p.sprite.setColor(Color::White);//���������� ������� ���� �������
						tempX = pos.x;//�������� ���������� ������� ������� �
						tempY = pos.y;//� Y

					}

#endif //____���������� ��������  ��������� �� ����� ������� 

#ifdef MOVE_SELECTED_WITH_MOUSE
			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
				if (event.key.code == Mouse::Left)//� ������ �����
					if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
					{
						std::cout << "isClicked!\n";//������� � ������� ��������� �� ����
						dX = pos.x - p.sprite.getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
						dY = pos.y - p.sprite.getPosition().y;//���� ����� �� ������
						isMove = true;//����� ������� ������							
					}
			if (event.type == Event::MouseButtonReleased)
			{//���� ��������� �������
				if (event.key.code == Mouse::Left) //� ������ �����
					isMove = false; //�� �� ����� ������� ������
				p.sprite.setColor(Color::White);//� ���� ��� ������� ����
			}
			if (isMove)
			{//���� ����� �������
				p.sprite.setColor(Color::Green);//������ ������ � ������� 
				p.x = pos.x - dX;//������� ������ �� �
				p.y = pos.y - dY;//������� �� Y	
			}
#endif //____���������� ������� �� �������������� ��������� ������

#ifdef TAB_PRESSED_MISSION_SCORE_HEALTH_REALISE
			if (event.type == Event::KeyPressed)//������� ������� �������
				if ((event.key.code == Keyboard::Tab)) {//���� ������� ���


					switch (showMissionText) {//�������������, ����������� �� ���������� ���������� showMissionText

					case true: {
						std::ostringstream playerHealthString;//������ �������� ������
						playerHealthString << p.health; //������� � ������ �������� 
						std::ostringstream playerScoreString;//������ ���� ������
						playerScoreString << p.playerScore; //������� � ������ ���� 

						std::ostringstream task;//������ ������ ������
						task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//���������� ������� getTextMission (��� ���������� ����� ������), ������� ��������� � �������� ��������� ������� getCurrentMission(������������ ����� ������), � ��� ��� �-��� ��������� � �������� ��������� ������� p.getplayercoordinateX() (��� �-��� ���������� ��� ���������� ������)
						text.setString("��������: " + playerHealthString.str() + "\n" + "����: " + playerScoreString.str() + task.str());
						showMissionText = false;//��� ������ ��������� ������ ��� ��� �� ������ �� ������
						break;//������� , ����� �� ��������� ������� "false" (������� ����)
					}
					case false: {
						text.setString("");//���� �� ������ ������� ���, �� ���� ���� ����� ������
						showMissionText = true;// � ��� ������ ��������� ����� ������ ������� ��� � �������� ����� �� �����
						break;
					}
					}
				}
#endif //____���������� ������� �� ������� ������� TAB
		}
#ifdef PLAYER_MOUSE_MOOVE_PART_2
		if (p.isMove)
		{
			distance = sqrt((tempX - p.x) * (tempX - p.x) + (tempY - p.y) * (tempY - p.y));//������� ��������� (���������� �� ����� � �� ����� �). ��������� ������� ����� �������

			if (distance > 2) {//���� �������� ������� �������� �� ����� �������� ������� �������

				p.x += 0.1 * time * (tempX - p.x) / distance;//���� �� ���� � ������� ������� �������
				p.y += 0.1 * time * (tempY - p.y) / distance;//���� �� ������ ��� ��
			}
			else { p.isMove = false; std::cout << "priehali\n"; }//������� ��� ��� ������ �� ���� � ������� ������� ��������� � �������
		}
#endif //____���������� ��������  ��������� �� ����� ������� 


#ifdef SPRITE_MOUSE_ROTATE
		float dX = pos.x - p.x;//������ , ����������� ������, ������� ���������� ������ � ������
		float dY = pos.y - p.y;//�� ��, ���������� y
		float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
		std::cout << rotation << "\n";//������� �� ������� � ���������
		p.sprite.setRotation(rotation);//������������ ������ �� ��� �������  
#endif // SPRITE_MOUSE_ROTATE


#ifdef SPRITE_ROTATE_MOVING_RIGHT_MOUSE
		if (event.key.code == Mouse::Right)
{//� ������ ������
	p.isMove = true;//�� �������� ��������
	p.isSelect = false;//������ ��� �� ������
	p.sprite.setColor(Color::White);//���������� ������� ���� �������
	tempX = pos.x;//�������� ���������� ������� ������� �
	tempY = pos.y;//� Y
	float dX = pos.x - p.x;//������ , ����������� ������, ������� ���������� ������ � ������
	float dY = pos.y - p.y;//�� ��, ���������� y
	float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
	std::cout << rotation << "\n";//������� �� ������� � ���������
	p.sprite.setRotation(rotation);//������������ ������ �� ��� �������				
}  
#endif // SPRITE_ROTATE_MOVING_RIGHT_MOUSE



#ifdef PLAYER_WSAD_MOVING
		if (p.life)
		{
			if ((Keyboard::isKeyPressed(Keyboard::A))) {
				p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(40 * int(CurrentFrame) + 40, 245, -40, 50));//����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
			}

			if ((Keyboard::isKeyPressed(Keyboard::D))) {
				p.dir = 0; p.speed = 0.1;//����������� ������, �� ����
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 245, 40, 50));  //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
			}

			if ((Keyboard::isKeyPressed(Keyboard::W)))
			{
				p.dir = 3; p.speed = 0.1;//����������� ����, �� ����
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 245, 40, 50));  //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)

			}

			if ((Keyboard::isKeyPressed(Keyboard::S))) { //���� ������ ������� ������� ����� ��� ���� ����� �
				p.dir = 2; p.speed = 0.1;//����������� �����, �� ����
				CurrentFrame += 0.005 * time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
				if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
				p.sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 245, 40, 50)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96

			}

			//	getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());//�������� ������ �� ������
		}
#endif //____���������� ���������� � ���������
	
#ifdef MOUSE_SCROLLING_WINDOW
		sf::Vector2i localPosition = Mouse::getPosition(window);//������� � ������ ���������� ���� ������������ ���� (�,�)
		std::cout << "locPos " << localPosition.x << "\n";//���������� ��� ���� ����� ������� ������� �

		createObjectForMapTimer += time;//���������� ������
		if (createObjectForMapTimer > 6000) {
			randomMapGenerate();//��������� ���� ������
			createObjectForMapTimer = 0;//�������� ������
		}

		if (localPosition.x < 3) { view.move(-0.2 * time, 0); }//���� ������ �������� � ����� ���� ������,�� ������� ������ �����
		if (localPosition.x > window.getSize().x - 3) { view.move(0.2 * time, 0); }//������ ����-������
		if (localPosition.y > window.getSize().y - 3) { view.move(0, 0.2 * time); }//������ ���� - ����
		if (localPosition.y < 3) { view.move(0, -0.2 * time); }//������� ���� - �����



#endif //____�������� ������ ������������ ����

		

		window.clear(Color(128, 106, 89));//��������� ����� �����
		
#ifdef CAMERA_VIEW
		window.setView(view);//"��������" ������ � ���� sfml

		changeview();//������������� � �������  
#endif //____���������� �������____//


		
#ifdef CREATING_MAP_LEVELS
		if ((getCurrentMission(p.getplayercoordinateX())) == 0) { //���� ������� ������ 0, �� ������ ����� ��� ���
			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
					if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
					if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
					if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
					if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
					s_map.setPosition(j * 32, i * 32);

					window.draw(s_map);
				}
		}

		if ((getCurrentMission(p.getplayercoordinateX())) >= 1) { //���� ������� ������ 1, �� ������ ����� ��� ���
			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 0, 32, 32));//��� ������� ������� ������� ����� ������� ��� ����� ������� �..
					if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
					if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//� ��� ��� �����. ���������-������� ����� �� ������� ����� ��
					if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
					if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
					s_map.setPosition(j * 32, i * 32);

					window.draw(s_map);
				}
		}
#endif //������ ����� � ����������� �� �������//

		p.update(time);//�������� ������ p ������ Player � ������� ������� sfml, ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������

		viewmap(time);//������� ���������� �����, �������� �� ����� sfml


			
#ifdef MISSION_SPRITE_PART_2
		if (!showMissionText)
		{
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//������� ����� ����� ���������� �����
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//������� ���� ��� �����			
			window.draw(s_quest); window.draw(text); //������ ������ ������ (��� ��� ������ ������). � ����� � �����. ��� ��� �������� �� ���������� ����������, ������� ������ ���� ��������� �� ������� ������� ���
		}
#endif // �������������� ������ �� ������� TAB 

		window.draw(p.sprite);//������ ������ ������� p ������ player
		window.display();
	}

	return 0;
}