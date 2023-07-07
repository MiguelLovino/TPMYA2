#include "ZonaGanar.h"

ZonaGanar::ZonaGanar(String url, Vector2f pos)
{
	tex_zona = new Texture;
	tex_zona->loadFromFile(url);
	spr_zona = new Sprite(*tex_zona);
	spr_zona->setPosition(pos);
	spr_zona->setOrigin(spr_zona->getGlobalBounds().width / 2, spr_zona->getGlobalBounds().height / 2);
	spr_zona->setScale(0.02,0.02);
}

ZonaGanar::~ZonaGanar()
{
	delete spr_zona;
	delete tex_zona;
}

void ZonaGanar::Dibujar(RenderWindow *ventana)
{
	ventana->draw(*spr_zona);
}
