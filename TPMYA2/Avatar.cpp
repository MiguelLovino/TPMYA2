#include "Avatar.h"


Avatar::Avatar(b2Body* cuerpo, RectangleShape* figura, float angulo) : bod_avatar(cuerpo), rec_shape(figura)
{
	//guardo la posicion del body en una variable para despues asignarsela al sprite
	posicion = bod_avatar->GetPosition();
	angulo = bod_avatar->GetAngle();
	//dimenciones del body
	b2AABB dimension;
	dimension.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dimension.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

	//recorro todos los fixture y los alojo en aabb
	for (b2Fixture* f = bod_avatar->GetFixtureList(); f; f = f->GetNext())
	{
		dimension = f->GetAABB(0);
	}
	//asigno el size
	rec_shape->setSize({ dimension.GetExtents().x * 2, dimension.GetExtents().y * 2 });

	//seteo el origen en el medio para que coincida con el body, (se hace antes de asignarle la posicion)
	rec_shape->setOrigin(rec_shape->getSize().x / 2.f, rec_shape->getSize().y / 2.f);

	//asigo la posicion al sprite
	rec_shape->setPosition(posicion.x, posicion.y);
	rec_shape->setRotation(angulo);

}
/*
Avatar::Avatar(b2Body* cuerpo, Sprite* figura, Texture* texfig ) : bod_avatar(cuerpo), spr_shape(figura), tex_shape(texfig)
{
	//guardo la posicion del body en una variable para despues asignarsela al sprite
	posicion = bod_avatar->GetPosition();

	//dimenciones del body
	b2AABB dimension;
	dimension.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
	dimension.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);

	//recorro todos los fixture y los alojo en aabb
	for (b2Fixture* f = bod_avatar->GetFixtureList(); f; f = f->GetNext())
	{
		dimension = f->GetAABB(0);
	}
	spr_shape->setTexture(*texfig);
	//asigno el size
	spr_shape->setScale({ dimension.GetExtents().x * 2, dimension.GetExtents().y * 2 });

	//seteo el origen en el medio para que coincida con el body, (se hace antes de asignarle la posicion)
	spr_shape->setOrigin(tex_shape->getSize().x / 2.f, tex_shape->getSize().y / 2.f);

	//asigo la posicion al sprite
	spr_shape->setPosition(posicion.x, posicion.y);
}

*/
float Avatar::radianes_a_grados(float radianes)
{
	return radianes * 180 / 3.1415;
}

void Avatar::destruir_avatar(b2World* mundo)
{
	mundo->DestroyBody(bod_avatar);
}


void Avatar::dibujar_ragdol(RenderWindow& ventana)
{
	ventana.draw(*rec_shape);
}


void Avatar::actualizar_ragdol()
{
	posicion = bod_avatar->GetPosition();
	rec_shape->setPosition(posicion.x, posicion.y);
	rec_shape->setRotation(radianes_a_grados(bod_avatar->GetAngle()));

}

void Avatar::mover(float vel_y)
{
	bod_avatar->SetTransform({ bod_avatar->GetPosition().x, bod_avatar->GetPosition().y + vel_y}, 0);
}
