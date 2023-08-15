#include "cannon_Sprite.h"

cannon_Sprite::cannon_Sprite()
{
	spr_canon = new Sprite;
	tex_canon = new Texture;
	spr_rueda = new Sprite;
	tex_rueda = new Texture;

	
	origenpoint.setFillColor(Color::Red);

	tex_canon->loadFromFile("recursos/canon2.png");
	spr_canon->setTexture(*tex_canon);
	spr_canon->setScale(0.035, 0.035);
	//origenpoint.setScale(0.035, 0.035);
	//origenpoint.setSize({0.50,0.50});
	spr_canon->setOrigin(0,35);
	
	tex_rueda->loadFromFile("recursos/rueda3.png");
	spr_rueda->setTexture(*tex_rueda);
	spr_rueda->setScale(0.025, 0.025);
	spr_rueda->setOrigin(spr_rueda->getTexture()->getSize().x / 2, spr_rueda->getTexture()->getSize().y / 2);

}

void cannon_Sprite::dibujar(RenderWindow* ventana)
{
	spr_canon->setPosition(ventana->mapPixelToCoords({ coordx, coordy }));
	spr_rueda->setPosition(ventana->mapPixelToCoords({ coordx, coordy }));
	origenpoint.setPosition(ventana->mapPixelToCoords({ coordx, coordy }));

	ventana->draw(*spr_canon);
	ventana->draw(*spr_rueda);
	//ventana->draw(origenpoint);
}

void cannon_Sprite::actualizar(Vector2f mouse_m, RenderWindow* ventana,bool nivel1)
{
	float angulo = atan2f(mouse_m.y - origenpoint.getPosition().y, mouse_m.x - origenpoint.getPosition().x);
	
	angulo = angulo * 180 / 3.14159;

	//limite de rotacion del cañon
	if (nivel1 && angulo <= -100)
	{
		angulo = -100;
	}
	if (!nivel1 && angulo < 180 && angulo > 90 )
	{
		angulo = 180;
	}
	if (angulo > 0 && angulo < 90)
	{
		angulo = 0;
	}
	//cout << angulo << endl;
	spr_canon->setRotation(angulo);

}
