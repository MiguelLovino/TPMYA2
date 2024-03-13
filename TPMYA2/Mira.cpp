#include "Mira.h"

Mira::Mira(View* camara1, int ventana_ancho, int ventana_alto)
{
	/*MIRA*/
	txt_mira = new Texture;
	txt_mira->loadFromFile("recursos/mira.png");
	spr_mira = new Sprite(*txt_mira);
	spr_mira->setOrigin(spr_mira->getGlobalBounds().width / 2, spr_mira->getGlobalBounds().height / 2);
	spr_mira->setScale(camara1->getSize().x / ventana_ancho, camara1->getSize().y / ventana_alto);

	
}

void Mira::Dibujar(RenderWindow* ventana)
{
	ventana->draw(*spr_mira);
}

void Mira::Actualizar(RenderWindow* ventana)
{
	
	//posicion el pantalla (pixeles)
	pixel_pos = Mouse::getPosition(*ventana);

	//posicion en el mundo(cordenadas)
	world_pos = ventana->mapPixelToCoords(pixel_pos);

	//seteo la posicion correcta.
	spr_mira->setPosition(world_pos);
	
}
