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
	int coordx = 75;
	int coordy = 550;
	Vector2i posInicial = Vector2i(75, 550);
	Vector2i posNivel2 = Vector2i(75, 550);
	int potencia_cannon = 0;

public:
	cannon_Sprite(RenderWindow* ventana);
	RectangleShape get_rect() { return origenpoint; }
	Sprite get_sprite() { return *spr_canon; }
	void dibujar(RenderWindow* ventana);
	void actualizar(Vector2f mouse_m, RenderWindow* ventana, bool nivel1);
	void Mover_cannon(RenderWindow* ventana, Vector2i pos);
	Vector2i get_pos_Nivel1() { return posInicial; }
	Vector2i get_pos_Nivel2() { return posNivel2; }
	int get_potencia_cannon() { return potencia_cannon; }
};

