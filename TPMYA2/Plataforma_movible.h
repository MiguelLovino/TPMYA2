#pragma once
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 
#include <Box2D/Box2D.h>
#include "Avatar.h"
#include <string> 
#include <iostream>

using namespace std;
using namespace sf;

class Plataforma_movible
{
private:
	RectangleShape* mov_plat;
	b2Vec2 mov_plat_posicion;

	b2Body* bod_mov_plat;
	b2BodyDef boddef_mov_plat;
	b2Fixture* fix_mov_plat;
	b2FixtureDef fixdef_mov_plat;
	Texture* regla;
	Avatar* Plataforma_mov;

	float vel = 0;

public:
	Plataforma_movible(b2World* mundo, float velo, b2Vec2 pos);
	void destruir_plataforma();
	void dibujar(RenderWindow* ventana);
	void actualizar(float x1, float x2);
	void colicion(RectangleShape* rect[]);
	b2Vec2 get_pos() { return  bod_mov_plat->GetPosition(); }
	void mover(float x1, float x2);
	void set_pos_y(float posy) { bod_mov_plat->SetTransform({ bod_mov_plat->GetPosition().x, posy }, 0);
	}
};

