
#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;//�������� sfml ������ "���", ������� � �������� �������

//������� ��� ���������� ��������� ������
void getplayercoordinateforview(float x, float y)
{ 


	view.setCenter(x + 100, y); //������ �� �������, ��������� ��� ���������� ������. +100 - �������� ������ �� ���� ������. �����������������


}
//������� ��� ����������� ������ �� �����. ��������� ����� sfml
void viewmap(float time)
{ 


	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view.move(0.1 * time, 0);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view.move(0, 0.1 * time);//�������� ����� ���� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view.move(-0.1 * time, 0);//�������� ����� ����� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view.move(0, -0.1 * time);//�������� ����� ����� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}


}
void changeview() {


	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view.zoom(1.0100f); //������������, ����������
		//view.zoom(1.0006f); //���� ����� ����������� ��������������
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//����� �� ������ ������� ������
		view.rotate(1);//���������� ������������ ������ (������������� �������� - � �������� �������)
	}
	if (Keyboard::isKeyPressed(Keyboard::T)) {
		//view.setRotation(90);//����� �� ������ ������� ������
		view.rotate(-1);//���������� ������������ ������ (������������� �������� - � �������� �������)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(640, 480);//������������� ������ ������ (��� ��������)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(540, 380);//�������� ������ ������
	}


	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//����� ������� �������� ���������� ����� ��� ���� �� �����. ����� ������ ������� ��� ���� ������ View � ����������� � ���� ���������� ������ 2.
	}



}