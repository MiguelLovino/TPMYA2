#include "Pared_estatica.h"

Pared_estatica::Pared_estatica(String textura, b2World *mundo, b2Vec2 pos, Vector2f tam, View *camara1)
{
	//type
	boddef_pared.type = b2_staticBody;

	//pos
	boddef_pared.position = pos;

	//en mundo
	bod_pared = mundo->CreateBody(&boddef_pared);
	
	//shape
	b2PolygonShape shape_pared;
	shape_pared.SetAsBox(tam.x,tam.y);

	//fixdef
	fixdef_pared.shape = &shape_pared;
	fixdef_pared.density = 0.1f;
	fixdef_pared.friction = 0.3f;
	fixdef_pared.restitution = 0.1f;

	//creo el fix
	fix_pared = bod_pared->CreateFixture(&fixdef_pared);


	//tex
	tex_pared = new Texture;
	tex_pared->loadFromFile(textura);

	//rectangulo
	rec_pared = new RectangleShape();
	rec_pared->setTexture(tex_pared);

	

	//rec_pared->scale( / tex_pared->getSize().x, tam.y / tex_pared->getSize().y );
	//avatar
	pared_fija = new Avatar(bod_pared, rec_pared);

	
}

void Pared_estatica::rotar(float grado)
{
	bod_pared->SetTransform({ bod_pared->GetPosition()}, grado);
}

void Pared_estatica::Dibujar(RenderWindow *ventana)
{
	pared_fija->dibujar_ragdol(*ventana);
}
