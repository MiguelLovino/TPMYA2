#pragma once
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 
#include <Box2D/Box2D.h>
#include "Avatar.h"
#include <string> 
#include <iostream>

using namespace sf;
using namespace std;
class Ragdol
{
private:
	b2BodyDef boddef_ragdol[6];
	b2FixtureDef fixdef_ragdol[6];

	RectangleShape* fig_ragdol[6];

	//avatares
	Avatar* Ragdolino[6];

	// Resortes del ragdoll
	b2DistanceJointDef joint_def_ragdolino[5];

public:
	b2Body* bod_ragdol[6];
	b2Fixture* fix_ragdol[6];
	b2DistanceJoint* joint_ragdolino[5];
	Ragdol(b2World* mundo, b2Vec2 m, float rot_cannon);
	~Ragdol();
	Avatar get_avatar(int i) { return *Ragdolino[i]; }
	b2Fixture get_fixture(int i) { return *bod_ragdol[i]->GetFixtureList(); }
	void dibujar_ragdol(RenderWindow *ventana);
	void destruir_Ragdoll();
	void fuerza_disparo(float fuerza, float angulo);
	void rotar_Ragdoll();

};

