#pragma once
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include <iostream>
#include "Avatar.h"


using namespace std;
using namespace sf;

class BordePantalla
{
private:

	RectangleShape* piso[4];
	b2Vec2 piso_posicion[4];

	b2Body* bod_piso[4];
	b2BodyDef boddef_piso[4]; //no puede ser puntero
	b2Fixture* fix_piso[4];
	b2FixtureDef fixdef_piso[4]; //no puede ser puntero

	Avatar* pisolino[4];

	Texture* tex_piso;
	Texture* tex_pared;

public:
	BordePantalla(b2World* mundo);
	void Dibujar(RenderWindow* ventana);
	//b2Body get_body(int num) { return *bod_piso[num]; }
};

