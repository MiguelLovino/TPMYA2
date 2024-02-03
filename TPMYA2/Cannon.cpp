#include "Cannon.h"

Cannon::Cannon(b2World* mundo)
{
	//imagen del cannon
	canno = new RectangleShape({ 1,1 });
	//canno->setFillColor(Color::Red);
	text_cannon = new Texture;
	text_cannon->loadFromFile("recursos/canon.png");

	//propiedades fisicas del cannon

	boddef_cannon.type = b2_staticBody;
	boddef_cannon.position = b2Vec2(42.f, 100.f);
	//canon en el mundo
	bod_cannon = mundo->CreateBody(&boddef_cannon);

	b2PolygonShape shape_cannon;
	shape_cannon.SetAsBox(2.5f, 1.25f);

	fixdef_cannon.shape = &shape_cannon;
	fixdef_cannon.density = 0.1f;
	fixdef_cannon.friction = 0.3f;
	fixdef_cannon.restitution = 0.1f;

	fix_cannon = bod_cannon->CreateFixture(&fixdef_cannon);

	cannolino = new Avatar(bod_cannon, canno,0);
	cannolino->set_texture(text_cannon);
	
	//cambio el centro de la masa
	

}


void Cannon::dibujar(RenderWindow* ventana)
{
	cannolino->dibujar_ragdol(*ventana);
}

void Cannon::actualizar(Vector2f mouse_m)
{
	cannolino->actualizar_ragdol();
	
	
	bod_cannon->SetTransform(bod_cannon->GetPosition(), atan2f(mouse_m.y - bod_cannon->GetPosition().y, mouse_m.x - bod_cannon->GetPosition().x));
}
