#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Mira
{
private:
	Sprite* spr_mira;
	Texture* txt_mira;
	Vector2i pixel_pos;
	Vector2f world_pos;
public:
	Mira(View* camara1, int ventana_ancho, int ventana_alto);
	void Dibujar(RenderWindow* ventana);
	void Actualizar(RenderWindow* ventana);
	Sprite get_sprite() { return *spr_mira; }
	Vector2f get_world_pos() { return world_pos; }
};

