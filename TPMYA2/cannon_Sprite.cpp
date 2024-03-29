#include "cannon_Sprite.h"

cannon_Sprite::cannon_Sprite(RenderWindow* ventana)
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

	spr_canon->setPosition(ventana->mapPixelToCoords({ posInicial }));
	spr_rueda->setPosition(ventana->mapPixelToCoords({ posInicial }));
	origenpoint.setPosition(ventana->mapPixelToCoords({ posInicial }));

}

void cannon_Sprite::dibujar(RenderWindow* ventana)
{
	ventana->draw(*spr_canon);
	ventana->draw(*spr_rueda);
	//ventana->draw(origenpoint);
}

void cannon_Sprite::actualizar(Vector2f mouse_m, RenderWindow* ventana,bool nivel1)
{
	float angulo = atan2f(mouse_m.y - origenpoint.getPosition().y, mouse_m.x - origenpoint.getPosition().x);
	
	angulo = angulo * 180 / 3.14159;

	//limite de rotacion del ca�on
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
	
	spr_canon->setRotation(angulo);

	//en cada actualizacion, calculo la potencia de disparo del cannon

	//actualizo la potencia del disparo del ragdol
	float X1 = mouse_m.x;
	float Y1 = mouse_m.y;
	float X2 = spr_canon->getPosition().x;
	float Y2 = spr_canon->getPosition().y;
	//la potencia se calcula entre la pocicion del cannon y la mira.
	potencia_cannon = sqrtl(pow(X1 - X2, 2) + pow(Y1 - Y2, 2));

}

void cannon_Sprite::Mover_cannon(RenderWindow* ventana, Vector2i pos)
{
	spr_canon->setPosition(ventana->mapPixelToCoords({ pos }));
	spr_rueda->setPosition(ventana->mapPixelToCoords({ pos }));
	origenpoint.setPosition(ventana->mapPixelToCoords({ pos	}));
}
