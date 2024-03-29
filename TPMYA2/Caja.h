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
	b2Vec2 posicion_inicial;
	b2Body* bod_caja;
	b2BodyDef boddef_caja;
	b2Fixture* fix_caja;
	b2FixtureDef fixdef_caja;

	Avatar* caja_dinamica;
public:
	Caja(String textura, b2World* mundo, b2Vec2 pos, Vector2f tam);
	void Dibujar(RenderWindow* ventana);
	void Actualizar();
	RectangleShape get_rect() { return *rec_caja; }
	bool enPosicion = false;
	bool daPuntosN2 = true;
	bool enMovimiento();
	void Destruir(b2World *mundo);
	void reiniciar_pos();
};

