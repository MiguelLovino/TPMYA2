#pragma once
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Avatar.h"
#include "SFML/Window.hpp"

using namespace std;
using namespace sf;

class Helice
{
private:

	RectangleShape* rec_helice[2];

	Texture* txt_helice;
	Texture* text_centroHelice;

	b2Body* bod_helice[2];
	b2BodyDef def_bod_helice[2];

	b2Fixture* fix_helice[2];
	b2FixtureDef def_fix_helice[2];

	b2DistanceJoint* joint_heli;
	b2DistanceJointDef def_join_heli;

	Avatar* Av_heleice[2];
	float vel = 0.12f;

public:
	Helice(b2World* mundo, b2Vec2 m);
	void Dibujar(RenderWindow* ventana);
	Avatar get_avatar(int i) { return *Av_heleice[i]; }
	void Actualizar();
	void Destruir();
	void MovimientoHorizontal();
	void MovimientoVertical();
};

