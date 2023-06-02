#include "cannon_Sprite.h"

cannon_Sprite::cannon_Sprite()
{
	spr_canon = new Sprite;
	tex_canon = new Texture;

	
	origenpoint.setFillColor(Color::Red);

	tex_canon->loadFromFile("recursos/canon.png");
	spr_canon->setTexture(*tex_canon);
	spr_canon->setScale(0.035, 0.035);
	//origenpoint.setScale(0.035, 0.035);
	origenpoint.setSize({0.25,0.25});
	spr_canon->setOrigin(0,40);
	//cout << spr_canon->getGlobalBounds().height << " este es el heigth" << endl;

}

void cannon_Sprite::dibujar(RenderWindow* ventana)
{
	int coordx = 50;
	int coordy = 525;
	spr_canon->setPosition(ventana->mapPixelToCoords({ coordx, coordy }));
	origenpoint.setPosition(ventana->mapPixelToCoords({ coordx, coordy }));
	ventana->draw(*spr_canon);
	//ventana->draw(origenpoint);
}

void cannon_Sprite::actualizar(Vector2f mouse_m, RenderWindow* ventana)
{
	float angulo = atan2f(mouse_m.y - origenpoint.getPosition().y, mouse_m.x - origenpoint.getPosition().x);
	
	angulo = angulo * 180 / 3.14159;

	//limite de rotacion del cañon
	
	//cout << angulo << endl;
	if (angulo < -90)
	{
		angulo = -90;
	}
	if (angulo > 30)
	{
		angulo = 30;
	}

	spr_canon->setRotation(angulo);

}
