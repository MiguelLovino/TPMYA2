#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace std;
using namespace sf;

class Avatar
{
private:
	
	RectangleShape* rec_shape;
	//Texture* tex_shape;
	//Sprite* spr_shape;
	b2Vec2 posicion;
	b2Body* bod_avatar;

public:
	
	Avatar(b2Body* cuerpo, RectangleShape* figura);
	//Avatar(b2Body* cuerpo, Sprite* figura, Texture* texfig);
	float radianes_a_grados(float radianes);
	void destruir_avatar(b2World* mundo);
	//b2Body get_body() { return *bod_avatar; }
	float get_body_pos() { return bod_avatar->GetPosition().y; }
	void dibujar_ragdol(RenderWindow& ventana);
	void set_texture(Texture* teture) { rec_shape->setTexture(teture); }
	void actualizar_ragdol();
	void mover(float vel);
	void set_pos_y(float posy) { bod_avatar->SetTransform({ bod_avatar->GetPosition().x, posy }, 0); }
};

