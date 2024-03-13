#include "Helice.h"

Helice::Helice(b2World* mundo, b2Vec2 m)
{
	for (int i = 0; i < 2; i++)
	{
		rec_helice[i] = new RectangleShape;
	}

	//textura del rectangulo

	txt_helice = new Texture;
	txt_helice->loadFromFile("recursos/sierra2.png");
	rec_helice[1]->setTexture(txt_helice);

	text_centroHelice = new Texture;
	text_centroHelice->loadFromFile("recursos/centrosierra.png");
	rec_helice[0]->setTexture(text_centroHelice);
	

	//la poscicion en el mundo
	def_bod_helice[0].position = b2Vec2(m.x, m.y);
	def_bod_helice[1].position = b2Vec2(m.x, m.y + 1.9f);

	//definicio del cuerpo
	for (int i = 0; i < 2; i++)
	{
		//def_bod_helice[i].angle = 0;
		if (i == 0) { def_bod_helice[i].type = b2_staticBody; }
		if (i == 1) { def_bod_helice[i].type = b2_dynamicBody;; }
		bod_helice[i] = mundo->CreateBody(&def_bod_helice[i]);
	}

	//creo las formas que van a tener las partes de la helice

	b2PolygonShape shape_helice[2];

	shape_helice[0].SetAsBox(0.30, 0.30);
	shape_helice[1].SetAsBox(0.5, 1.2);

	//asigno las opciones del fixture

	for (int i = 0; i < 2; i++)
	{
		if (i == 0) { def_fix_helice[i].shape = &shape_helice[0]; }
		if (i == 1) { def_fix_helice[i].shape = &shape_helice[1]; }
		
		def_fix_helice[i].density = 0.1f;
		def_fix_helice[i].friction = 1;
		def_fix_helice[i].restitution = 0.1f;
		fix_helice[i] = bod_helice[i]->CreateFixture(&def_fix_helice[i]);

	}

	// resortes y sus propiedades

	//centro helice [0], aleta [1]
	def_join_heli.Initialize(bod_helice[0], bod_helice[1], b2Vec2(bod_helice[0]->GetPosition().x, bod_helice[0]->GetPosition().y), b2Vec2( bod_helice[1]->GetPosition().x, bod_helice[1]->GetPosition().y - 1.45f ));

	//propiedades del resorte
	def_join_heli.dampingRatio = 0.0f;
	def_join_heli.frequencyHz = 0.0f;
	def_join_heli.collideConnected = true;
	def_join_heli.length = 0.25;
	joint_heli = (b2DistanceJoint*)mundo->CreateJoint(&def_join_heli);


	//creacion del avatar

	for (int i = 0; i < 2; i++)
	{
		Av_heleice[i] = new Avatar(bod_helice[i], rec_helice[i],0);
	}
	
}

void Helice::Dibujar(RenderWindow* ventana)
{
	for (int i = 0; i < 2; i++)
	{
		if (Av_heleice[i] != NULL)
		{
			Av_heleice[i]->dibujar_ragdol(*ventana);
			//actualizo
			get_avatar(i).actualizar_ragdol();
			//angulo
			
			
		}
		else
		{
			cout << " no se dibujar la helice" << endl;
		}
	}
	Actualizar();
}

void Helice::Actualizar()
{
	//Movimiento tipo helice
	float angulo = bod_helice[1]->GetAngle();
	//aplico fuerza
	float fuerzaMagnitude = 10.0f;
	b2Vec2 fuerza = fuerzaMagnitude * b2Vec2(cos(angulo), sin(angulo));
	bod_helice[1]->ApplyForceToCenter({ fuerza }, true);

	bod_helice[0]->SetTransform(b2Vec2 (bod_helice[0]->GetPosition().x + vel, bod_helice[0]->GetPosition().y),0);

	if (bod_helice[0]->GetPosition().x > 58) vel *= -1;
	if (bod_helice[0]->GetPosition().x < 40) vel *= -1;
	
	cout << bod_helice[0]->GetPosition().x << endl;
}


