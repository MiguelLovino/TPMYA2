#pragma once
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 
#include <Box2D/Box2D.h>
#include "Avatar.h"
#include <string> 
#include <iostream>

class Cannon
{
private:
	//cañon
	RectangleShape* canno;
	b2Vec2 cannon_pos;
	Texture* text_cannon;
	Sprite* spr_cannon;

	//creo el cuerpo
	b2Body* bod_cannon;
	//creo la definicion
	b2BodyDef boddef_cannon; //no puede ser puntero
	//creo su fixture (propiedades fisicas)
	b2Fixture* fix_cannon;
	b2FixtureDef fixdef_cannon;

	//creo el avatar
	Avatar* cannolino;


public:
	Cannon(b2World* mundo);
	void dibujar(RenderWindow *ventana);
	void actualizar(Vector2f mouse_m);
	b2Vec2 get_pos() { return bod_cannon->GetPosition(); }
	float get_angle() { return bod_cannon->GetAngle(); }
};

