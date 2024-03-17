#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace std;
using namespace sf;

class Avatar
{
private:
	
	RectangleShape* rec_shape;
	b2Vec2 posicion;
	b2Body* bod_avatar;

public:
	
	Avatar(b2Body* cuerpo, RectangleShape* figura, float angulo);
	float radianes_a_grados(float radianes);
	void destruir_avatar(b2World* mundo);
	float get_body_pos() { return bod_avatar->GetPosition().y; }
	void dibujar_ragdol(RenderWindow& ventana);
	void set_texture(Texture* teture) { rec_shape->setTexture(teture); }
	void actualizar_ragdol();
	void mover(float vel_y);
	void set_rot(float rot) { bod_avatar->SetTransform({ bod_avatar->GetPosition().x, bod_avatar->GetPosition().y }, rot); }
};

