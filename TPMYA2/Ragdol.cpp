#include "Ragdol.h"

Ragdol::Ragdol(b2World* mundo, b2Vec2 m, float rot_cannon)
{
	//la imagen de cada parte del ragdoll
	for (int i = 0; i < 6; i++)
	{
		fig_ragdol[i] = new RectangleShape;
	}

	fig_ragdol[0]->setFillColor(Color::White);
	
	fig_ragdol[1]->setFillColor(Color::Color(15, 50, 59));

	fig_ragdol[2]->setFillColor(Color::Yellow);
	fig_ragdol[3]->setFillColor(Color::Green);
	fig_ragdol[4]->setFillColor(Color::Color(170, 50, 59));
	fig_ragdol[5]->setFillColor(Color::Red);

	//posicion de los cuerpos del ragdol en el mundo
							//referencia m.x = 50 my = 90
	boddef_ragdol[0].position = b2Vec2(m.x, m.y + 0.1f); //cabeza 50 90.1
	boddef_ragdol[1].position = b2Vec2(m.x, m.y + 0.65f); //torzo 50 90.65
	boddef_ragdol[2].position = b2Vec2(m.x + 0.32f, m.y + 0.5f); //brazod 50.32 90.5
	boddef_ragdol[3].position = b2Vec2(m.x - 0.32f, m.y + 0.5f); //brazoi 49.68 90.5
	boddef_ragdol[4].position = b2Vec2(m.x + 0.09f, m.y + 1.5f); //piernad 50.09 91.5
	boddef_ragdol[5].position = b2Vec2(m.x - 0.09f, m.y + 1.5f); //piernai 49.91 91.5

	for (int i = 0; i < 6; i++)
	{
		//asigno el angulo
		boddef_ragdol[i].angle = 0.0f;
		//asigno el tipo del cuerpo (dinamico para que se mueva con las fuerzas)
		boddef_ragdol[i].type = b2_dynamicBody;
		//le asigno a cada cuerpo, su definicion que va a tener en el mundo.
		bod_ragdol[i] = mundo->CreateBody(&boddef_ragdol[i]);
	}

	//creo las formas que van a tener las partes del ragdoll
	b2PolygonShape shape_ragdol[6];

	shape_ragdol[0].SetAsBox(0.1, 0.1); //cabeza
	shape_ragdol[1].SetAsBox(0.2, 0.4); //torzo
	shape_ragdol[2].SetAsBox(0.07, 0.3); //brazod
	shape_ragdol[3].SetAsBox(0.07, 0.3); //brazoi
	shape_ragdol[4].SetAsBox(0.07, 0.4); //piernad
	shape_ragdol[5].SetAsBox(0.07, 0.4); //piernai

	//asigno las opciones de la definicion del fixture a gusto.
	for (int i = 0; i < 6; i++)
	{
		//asigno la forma previamente creada
		fixdef_ragdol[i].shape = &shape_ragdol[i];
		//densidad
		fixdef_ragdol[i].density = 0.5f;
		//friccion
		fixdef_ragdol[i].friction = 0.1f;
		//restitucion (rebote)
		fixdef_ragdol[i].restitution = 0.7f;
		//creo el fixture con la definiciones previamente creadas y la asigno la fixture.
		fix_ragdol[i] = bod_ragdol[i]->CreateFixture(&fixdef_ragdol[i]);
	}

	//inicializacion de resortes
		//union de resortes

		//cabeza[0] apecho [1]
	joint_def_ragdolino[0].Initialize(bod_ragdol[0], bod_ragdol[1], b2Vec2(bod_ragdol[0]->GetPosition().x, bod_ragdol[0]->GetPosition().y + 0.08), b2Vec2(bod_ragdol[1]->GetPosition().x, bod_ragdol[1]->GetPosition().y - 0.4));
	//pecho[1] a brazo derecho[2]
	joint_def_ragdolino[1].Initialize(bod_ragdol[1], bod_ragdol[2], b2Vec2(bod_ragdol[1]->GetPosition().x + 0.18, bod_ragdol[1]->GetPosition().y - 0.38), b2Vec2(bod_ragdol[2]->GetPosition().x - 0.05, bod_ragdol[2]->GetPosition().y - 0.28));
	//pecho[1] a brazo izquierdo[3]
	joint_def_ragdolino[2].Initialize(bod_ragdol[1], bod_ragdol[3], b2Vec2(bod_ragdol[1]->GetPosition().x - 0.18, bod_ragdol[1]->GetPosition().y - 0.38), b2Vec2(bod_ragdol[3]->GetPosition().x + 0.05, bod_ragdol[3]->GetPosition().y - 0.28));
	//pecho[1] a pierna  derecha[4]
	joint_def_ragdolino[3].Initialize(bod_ragdol[1], bod_ragdol[4], b2Vec2(bod_ragdol[1]->GetPosition().x + 0.09, bod_ragdol[1]->GetPosition().y + 0.38), b2Vec2(bod_ragdol[4]->GetPosition().x, bod_ragdol[4]->GetPosition().y - 0.38));
	//pecho[1] a pierna izquierda[5]
	joint_def_ragdolino[4].Initialize(bod_ragdol[1], bod_ragdol[5], b2Vec2(bod_ragdol[1]->GetPosition().x - 0.09, bod_ragdol[1]->GetPosition().y + 0.38), b2Vec2(bod_ragdol[5]->GetPosition().x, bod_ragdol[5]->GetPosition().y - 0.38));

	for (int i = 0; i < 5; i++)
	{
		joint_def_ragdolino[i].dampingRatio = 0.9f; //rebote
		joint_def_ragdolino[i].frequencyHz = 0.0f;
		joint_def_ragdolino->collideConnected = true;
		joint_def_ragdolino[i].length = 0.060f;
		joint_ragdolino[i] = (b2DistanceJoint*)mundo->CreateJoint(&joint_def_ragdolino[i]); //hay que castear
	}

	
	//bod_ragdol[2]->SetTransform(bod_ragdol[2]->GetPosition(), rot_cannon);

	//inicializo el ragdoll con su cuerpo(con fixture y definiciones ya implementadas, y su figura a utilizar)
	for (int i = 0; i < 6; i++)
	{
		
		Ragdolino[i] = new Avatar(bod_ragdol[i], fig_ragdol[i], rot_cannon);
	}
}

Ragdol::~Ragdol()
{
	
}


void Ragdol::dibujar_ragdol(RenderWindow *ventana)
{
	for (int i = 0; i < 6; i++)
	{
		get_avatar(i).dibujar_ragdol(*ventana);
	}
}

void Ragdol::destruir_Ragdoll() //destruir ragdoll
{
	for (int i = 0; i < 6; i++)
	{
			bod_ragdol[i]->GetWorld()->DestroyBody(bod_ragdol[i]);
			bod_ragdol[i] = NULL;
	}
}

void Ragdol::fuerza_disparo(float fuerza, float angulo)
{
	for (int i = 0; i < 6; i++)
	{

		bod_ragdol[i]->ApplyForceToCenter(b2Vec2(fuerza * cos(angulo), fuerza * sin(angulo)),false);
		
	}
}

