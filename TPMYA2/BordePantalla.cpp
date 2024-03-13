#include "BordePantalla.h"

BordePantalla::BordePantalla(b2World *mundo)
{
	//definicion_body (piso)
	for (int i = 0; i < 4; i++)
	{
		boddef_piso[i].type = b2_staticBody; //def
	}
	boddef_piso[0].position = b2Vec2(50.f, 76.f); //def techo
	boddef_piso[1].position = b2Vec2(50.f, 106.f); //def suelo

	boddef_piso[2].position = b2Vec2(66.f, 91.f); //def pared derecha 
	boddef_piso[3].position = b2Vec2(36.f, 91.f); //def pared izquierda

	//body del piso en el mundo
	for (int i = 0; i < 4; i++)
	{
		bod_piso[i] = mundo->CreateBody(&boddef_piso[i]); // linkeo el body a su definicion creada por el mundo
	}

	//creo una shape para asignar al fixture
	b2PolygonShape shape_piso; //techo
	shape_piso.SetAsBox(15.f, 1.f); // tiene que ser la mitad de la caja (en x, y)

	b2PolygonShape shape_pared;
	shape_pared.SetAsBox(1.f, 15.f);

	//definicion fixture piso
	for (int i = 0; i < 2; i++)
	{
		fixdef_piso[i].shape = &shape_piso;
	}

	//definicion fixture piso
	for (int i = 2; i < 4; i++)
	{
		fixdef_piso[i].shape = &shape_pared;
	}

	for (int i = 0; i < 4; i++)
	{
		fixdef_piso[i].density = 0.1f; // densidad = masa / volumen
		fixdef_piso[i].friction = 0.3f;
		fixdef_piso[i].restitution = 0.1f; //rebote (1.0 = infinito el rebote)
	}
	//fix
	for (int i = 0; i < 4; i++)
	{
		fix_piso[i] = bod_piso[i]->CreateFixture(&fixdef_piso[i]); //uno las propiedades fisicas al body.
	}

	//cargo las imagenes a usar en los botdes
	tex_piso = new Texture;
	tex_piso->loadFromFile("recursos/pared2.png");
	tex_pared = new Texture;
	tex_pared->loadFromFile("recursos/pared3.png");

	//imagen del piso
	piso[0] = new RectangleShape;
	piso[0]->setTexture(tex_piso);
	piso[1] = new RectangleShape;
	piso[1]->setTexture(tex_piso);
	piso[2] = new RectangleShape;
	piso[2]->setTexture(tex_pared);
	piso[3] = new RectangleShape;
	piso[3]->setTexture(tex_pared);

	for (int i = 0; i < 4; i++)
	{
		pisolino[i] = new Avatar(bod_piso[i], piso[i], 0);
	}
}

void BordePantalla::Dibujar(RenderWindow* ventana)
{
	for (int i = 0; i < 4; i++)
	{
		pisolino[i]->dibujar_ragdol(*ventana);
	}
}
