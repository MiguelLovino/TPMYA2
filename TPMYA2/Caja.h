#pragma once
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 
#include <Box2D/Box2D.h>
#include "Avatar.h"
#include <string> 
#include <iostream>

class Caja
{
private:

	Texture* tex_caja;
	RectangleShape* rec_caja;

	b2Body* bod_caja;
	b2BodyDef boddef_caja;
	b2Fixture* fix_caja;
	b2FixtureDef fixdef_caja;

	Avatar* caja_dinamica;
public:
	Caja(String textura, b2World* mundo, b2Vec2 pos, Vector2f tam, View* camara1);
	void Dibujar(RenderWindow* ventana);
	void Actualizar();
};

