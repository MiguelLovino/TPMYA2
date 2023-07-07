#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class cannon_Sprite
{
private:
	Sprite* spr_canon;
	Texture* tex_canon;
	Sprite* spr_rueda;
	Texture* tex_rueda;
	RectangleShape origenpoint;

public:
	cannon_Sprite();
	RectangleShape get_rect() { return origenpoint; }
	Sprite get_sprite() { return *spr_canon; }
	void dibujar(RenderWindow* ventana);
	void actualizar(Vector2f mouse_m, RenderWindow* ventana);

};

