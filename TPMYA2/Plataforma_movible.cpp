#include "Plataforma_movible.h"

Plataforma_movible::Plataforma_movible(b2World *mundo, float velo, b2Vec2 pos)
{
	vel = velo;
	boddef_mov_plat.type = b2_staticBody; //def
	
	//posiciones
	boddef_mov_plat.position =pos; //primera plataforma
	

	//body en el mundo
	
	bod_mov_plat = mundo->CreateBody(&boddef_mov_plat);

	b2PolygonShape shape_mov_plat;
	shape_mov_plat.SetAsBox(0.5f, 2.5f);

		fixdef_mov_plat.shape = &shape_mov_plat;
		fixdef_mov_plat.density = 0.1f;
		fixdef_mov_plat.friction = 0.3f;
		fixdef_mov_plat.restitution = 0.1;
	
		fix_mov_plat = bod_mov_plat->CreateFixture(&fixdef_mov_plat);

		//rectangulo
		regla = new Texture;
		regla->loadFromFile("recursos/regla.png");
		mov_plat = new RectangleShape({ 2, 4 });
		//mov_plat->setFillColor(Color::Black);
		mov_plat->setTexture(regla);
		
		//avatar

		Plataforma_mov = new Avatar(bod_mov_plat, mov_plat);

}

void Plataforma_movible::dibujar(RenderWindow* ventana)
{
	Plataforma_mov->dibujar_ragdol(*ventana);
}

void Plataforma_movible::actualizar(float x1, float x2)
{
	Plataforma_mov->actualizar_ragdol();	
	mover(x1,x2);
	
}

void Plataforma_movible::colicion(RectangleShape *rect[])
{
	if (mov_plat->getGlobalBounds().intersects(rect[1]->getGlobalBounds()))
	{
		vel = -vel;
	}
	else if (mov_plat->getGlobalBounds().intersects(rect[0]->getGlobalBounds()))
	{
		vel = +vel;
	}
	
}

void Plataforma_movible::mover(float x1, float x2)
{
	bod_mov_plat->SetTransform({ bod_mov_plat->GetPosition().x,bod_mov_plat->GetPosition().y + vel }, 0);
	if (bod_mov_plat->GetPosition().y > x1)
	{
		vel *= -1; //baja
	}

	if (bod_mov_plat->GetPosition().y < x2)
	{
		vel *= -1; //sube
	}
}
