#pragma once
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 
#include <Box2D/Box2D.h>
#include "Avatar.h"
#include <string> 
#include <iostream>

using namespace std;
using namespace sf;

class Pared_estatica
{

private:
	Texture* tex_pared;
	RectangleShape* rec_pared;

	b2Body* bod_pared;
	b2BodyDef boddef_pared;
	b2Fixture* fix_pared;
	b2FixtureDef fixdef_pared;

	Avatar* pared_fija;

public:
	//@brief Url text, mundo, pos en mundo, tamaño.
	Pared_estatica(String textura,b2World* mundo, b2Vec2 pos, Vector2f tam);
	void rotar(float grado);
	void Dibujar(RenderWindow *ventana);
	void Destruir(b2World* mundo);
};

