#include "Caja.h"

Caja::Caja(String textura, b2World* mundo, b2Vec2 pos, Vector2f tam, View* camara1)
{
	//type
	boddef_caja.type = b2_dynamicBody;

	//pos
	boddef_caja.position = pos;

	//en mundo
	bod_caja = mundo->CreateBody(&boddef_caja);

	//shape
	b2PolygonShape shape_pared;
	shape_pared.SetAsBox(tam.x, tam.y);

	//fixdef
	fixdef_caja.shape = &shape_pared;
	fixdef_caja.density = 0.1f;
	fixdef_caja.friction = 0.3f;
	fixdef_caja.restitution = 0.1f;

	//creo el fix
	fix_caja = bod_caja->CreateFixture(&fixdef_caja);


	//tex
	tex_caja = new Texture;
	tex_caja->loadFromFile(textura);

	//rectangulo
	rec_caja = new RectangleShape();
	rec_caja->setTexture(tex_caja);



	//rec_pared->scale( / tex_pared->getSize().x, tam.y / tex_pared->getSize().y );
	//avatar
	caja_dinamica = new Avatar(bod_caja, rec_caja);

}

void Caja::Dibujar(RenderWindow* ventana)
{
	caja_dinamica->dibujar_ragdol(*ventana);
}

void Caja::Actualizar()
{
	caja_dinamica->actualizar_ragdol();
}
