
#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;//объявили sfml объект "вид", который и является камерой

//функция для считывания координат игрока
void getplayercoordinateforview(float x, float y)
{ 


	view.setCenter(x + 100, y); //следим за игроком, передавая его координаты камере. +100 - сместили камеру по иксу вправо. эксперементируйте


}
//функция для перемещения камеры по карте. принимает время sfml
void viewmap(float time)
{ 


	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view.move(0.1 * time, 0);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view.move(0, 0.1 * time);//скроллим карту вниз (см урок, когда мы двигали героя - всё тоже самое)
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view.move(-0.1 * time, 0);//скроллим карту влево (см урок, когда мы двигали героя - всё тоже самое)
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view.move(0, -0.1 * time);//скроллим карту вверх (см урок, когда мы двигали героя - всё тоже самое)
	}


}
void changeview() {


	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view.zoom(1.0100f); //масштабируем, уменьшение
		//view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//сразу же задает поворот камере
		view.rotate(1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}
	if (Keyboard::isKeyPressed(Keyboard::T)) {
		//view.setRotation(90);//сразу же задает поворот камере
		view.rotate(-1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(640, 480);//устанавливает размер камеры (наш исходный)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(540, 380);//например другой размер
	}


	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//таким образом делается раздельный экран для игры на двоих. нужно только создать ещё один объект View и привязывать к нему координаты игрока 2.
	}



}