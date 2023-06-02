#include "Game.h"

Game::Game(int alto, int ancho, string titulo)
{
	pWnd = new RenderWindow(VideoMode(alto, ancho), titulo);
	fps = 60.f;
	tiempoFrame = 1.f / fps;
	pWnd->setFramerateLimit(fps);
	pWnd->setMouseCursorGrabbed(true);
	set_zoom();
	cargar_imagenes();
	iniciar_fisica();
	
	//inicializo objetos
	cannon2 = new cannon_Sprite;

	reloj = new Clock;
	
	gallardo = new Ragdol(mundo, b2Vec2(52, 90), cannon2->get_sprite().getRotation());

	for (int i = 0; i < 6; i++)
	{
		Ragdolino[i] = new Avatar(bod_ragdol[i], fig_ragdol[i]);
	}


	for (int i = 0; i < 4; i++)
	{
		pisolino[i] = new Avatar(bod_piso[i], piso[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		Plataforma_mov[i] = new Avatar(bod_mov_plat[i], mov_plat[i]);
	}


}

void Game::UpdateGame() //actualizo los objetos
{

	pixel_pos = Mouse::getPosition(*pWnd);
	world_pos = pWnd->mapPixelToCoords(pixel_pos);
	
	//actualizo el cannon
	cannon2->actualizar(world_pos, pWnd);

	//actualizo la potencia del disparo del ragdol
	float X1 = world_pos.x;
	float Y1 = world_pos.y;
	float X2 = cannon2->get_sprite().getPosition().x;
	float Y2 = cannon2->get_sprite().getPosition().y;

	potencia_cannon = sqrtl(pow(X1 - X2,2) + pow(Y1 - Y2,2));

	//actualizo el tiempo
	tiempo1 = reloj->getElapsedTime().asSeconds();
	
	for (int i = 0; i < 6; i++)
	{
		Ragdolino[i]->actualizar_ragdol();
	}

	for (int i = 0; i < 6; i++)
	{
		
		gallardo->get_avatar(i).actualizar_ragdol();
		gallardo->bod_ragdol[i]->SetTransform(gallardo->bod_ragdol[i]->GetPosition(), grados_a_radiannes(cannon2->get_sprite().getRotation() + 90));
	}


	for (int i = 0; i < 10; i++)
	{
		//actualizo el arreglo de ragdols
		if (arr_gallardo[i] != NULL)
		{
			for (int j = 0; j < 6; j++)
			{
				arr_gallardo[i]->get_avatar(j).actualizar_ragdol();
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		pisolino[i]->actualizar_ragdol();
	}

	for (int i = 0; i < 4; i++)
	{
		Plataforma_mov[i]->actualizar_ragdol();
	}

	
	
}

void Game::DrawGame()
{

	pWnd->draw(*spr_fondo);
	cannon2->dibujar(pWnd);
	for (int i = 0; i < 4; i++)
	{
		Plataforma_mov[i]->dibujar_ragdol(*pWnd);
	}
	for (int i = 0; i < 6; i++)
	{
		Ragdolino[i]->dibujar_ragdol(*pWnd);
	}

	gallardo->dibujar_ragdol(pWnd);

	for (int i = 0; i < 10; i++)
	{
		if (arr_gallardo[i] != NULL)
		{
			//dibujo los cuerpos de los ragdols
			arr_gallardo[i]->dibujar_ragdol(pWnd);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		pisolino[i]->dibujar_ragdol(*pWnd);
	}
}

void Game::ProcessCollisions()
{
	movimiento_plataformas();
}

void Game::cargar_imagenes()
{
	//imagen del piso
	for (int i = 0; i < 4; i++)
	{
		piso[i] = new RectangleShape(Vector2f(1, 1));
		piso[i]->setFillColor(Color::Blue);

	}
	for (int i = 0; i < 4; i++)
	{
		mov_plat[i] = new RectangleShape({ 2, 4 });
		mov_plat[i]->setFillColor(Color::Black);
	}

	//imagen del fondo
	tex_fondo = new Texture;
	tex_fondo->loadFromFile("recursos/fondo_pantalla_mya.png");
	spr_fondo = new Sprite(*tex_fondo);

	//escalo el fondo y lo posiciono
	Vector2f fondopos = pWnd->mapPixelToCoords({ 0, 0 });
	spr_fondo->setPosition(fondopos.x, fondopos.y);
	spr_fondo->setScale(camara1->getSize().x / spr_fondo->getGlobalBounds().width, camara1->getSize().y / spr_fondo->getGlobalBounds().height);
	
	for (int i = 0; i < 6; i++)
	{
		fig_ragdol[i] = new RectangleShape;
	}
	
	/************************/
	fig_ragdol[0]->setFillColor(Color::White);
	fig_ragdol[1]->setFillColor(Color::Color(15, 50, 59));
	fig_ragdol[2]->setFillColor(Color::Yellow);
	fig_ragdol[3]->setFillColor(Color::Green);
	fig_ragdol[4]->setFillColor(Color::Color(170, 50, 59));
	fig_ragdol[5]->setFillColor(Color::Red);
}

void Game::iniciar_fisica()
{
	//creo el mundo

	mundo = new b2World(b2Vec2(0,gravedad));

	/*****************************/

	//creacion de plataformas movibles
	for (int i = 0; i < 4; i++)
	{
		boddef_mov_plat->type = b2_staticBody; //def
	}
	//posiciones
	boddef_mov_plat[0].position = b2Vec2(46.f, 80.f); //primera plataforma
	boddef_mov_plat[1].position = b2Vec2(50.f, 90.f);
	boddef_mov_plat[2].position = b2Vec2(53.f, 95.f);
	boddef_mov_plat[3].position = b2Vec2(62.f, 92.f);

	//body en el mundo
	for (int i = 0; i < 4; i++)
	{
		bod_mov_plat[i] = mundo->CreateBody(&boddef_mov_plat[i]);
	}
	
	b2PolygonShape shape_mov_plat;
	shape_mov_plat.SetAsBox(0.5f, 2.5f);

	for (int i = 0; i < 4; i++)
	{
		fixdef_mov_plat[i].shape = &shape_mov_plat;
		fixdef_mov_plat[i].density = 0.1f;
		fixdef_mov_plat[i].friction = 0.3f;
		fixdef_mov_plat[i].restitution = 0.1;
	}

	for (int i = 0; i < 4; i++)
	{
		fix_mov_plat[i] = bod_mov_plat[i]->CreateFixture(&fixdef_mov_plat[i]);
	}

	/****************************************/

	//definicion_body (piso)
	for (int i = 0; i < 4; i++)
	{
		boddef_piso[i].type = b2_staticBody; //def
	}
	boddef_piso[0].position = b2Vec2(50.f, 76.f); //def techo
	boddef_piso[1].position = b2Vec2(50.f, 106.f); //def suelo

	boddef_piso[2].position = b2Vec2(66.f, 105.f); //def pared derecha 
	boddef_piso[3].position = b2Vec2(35.5f, 105.f); //def pared izquierda

	//body del piso en el mundo
	for (int i = 0; i < 4; i++)
	{
		bod_piso[i] = mundo->CreateBody(&boddef_piso[i]); // linkeo el body a su definicion creada por el mundo
	}

	//creo una shape para asignar al fixture
	b2PolygonShape shape_piso; //techo
	shape_piso.SetAsBox(50.f, 1.f); // tiene que ser la mitad de la caja (en x, y)

	b2PolygonShape shape_pared;
	shape_pared.SetAsBox(1.f, 50.f);



	 //definicion fixture piso
	for (int i = 0; i < 2; i++)
	{
		fixdef_piso[i].shape = &shape_piso;
	}

	//definicion fixture piso
	for (int i = 2; i < 4; i++)
	{
		fixdef_piso[i].shape = &shape_pared;
	}

	for (int i = 0; i < 4; i++)
	{
		fixdef_piso[i].density = 0.1f; // densidad = masa / volumen
		fixdef_piso[i].friction = 0.3f;
		fixdef_piso[i].restitution = 0.1f; //rebote (1.0 = infinito el rebote)
	}
	//fix
	for (int i = 0; i < 4; i++)
	{
		fix_piso[i] = bod_piso[i]->CreateFixture(&fixdef_piso[i]); //uno las propiedades fisicas al body.
	}

	//ragdoll

	//posicion de los cuerpos del ragdol en el mundo
	boddef_ragdol[0].position = b2Vec2(50.f, 90.1f); //cabeza
	boddef_ragdol[1].position = b2Vec2(50.f, 90.65f); //torzo
	boddef_ragdol[2].position = b2Vec2(50.32f, 90.5f); //brazod
	boddef_ragdol[3].position = b2Vec2(49.68f, 90.5f); //brazoi
	boddef_ragdol[4].position = b2Vec2(50.09f, 91.5f); //piernad
	boddef_ragdol[5].position = b2Vec2(49.91f, 91.5f); //piernai

	for (int i = 0; i < 6; i++)
	{
		boddef_ragdol[i].type = b2_dynamicBody;
		bod_ragdol[i] = mundo->CreateBody(&boddef_ragdol[i]);
	}

	b2PolygonShape shape_ragdol[6];

	shape_ragdol[0].SetAsBox(0.1, 0.1); //cabeza
	shape_ragdol[1].SetAsBox(0.2, 0.4); //torzo
	shape_ragdol[2].SetAsBox(0.07, 0.3); //brazod
	shape_ragdol[3].SetAsBox(0.07, 0.3); //brazoi
	shape_ragdol[4].SetAsBox(0.07, 0.4); //piernad
	shape_ragdol[5].SetAsBox(0.07, 0.4); //piernai

	for (int i = 0; i < 6; i++)
	{
		fixdef_ragdol[i].shape = &shape_ragdol[i];
		fixdef_ragdol[i].density = 0.5f;
		fixdef_ragdol[i].friction = 0.1f;
		fixdef_ragdol[i].restitution = 0.7f;
		fix_ragdol[i] = bod_ragdol[i]->CreateFixture(&fixdef_ragdol[i]);

	}

	//inicializacion de resortes
		//union de resortes

		//cabeza[0] a pecho [1]
	joint_def_ragdolino[0].Initialize(bod_ragdol[0], bod_ragdol[1], b2Vec2(bod_ragdol[0]->GetPosition().x, bod_ragdol[0]->GetPosition().y + 0.08), b2Vec2(bod_ragdol[1]->GetPosition().x, bod_ragdol[1]->GetPosition().y - 0.4));
	//pecho[1] a brazo derecho[2]
	joint_def_ragdolino[1].Initialize(bod_ragdol[1], bod_ragdol[2], b2Vec2(bod_ragdol[1]->GetPosition().x + 0.18, bod_ragdol[1]->GetPosition().y - 0.38), b2Vec2(bod_ragdol[2]->GetPosition().x - 0.05, bod_ragdol[2]->GetPosition().y - 0.28));
	//pecho[1] a brazo izquierdo[3]
	joint_def_ragdolino[2].Initialize(bod_ragdol[1], bod_ragdol[3], b2Vec2(bod_ragdol[1]->GetPosition().x - 0.18, bod_ragdol[1]->GetPosition().y - 0.38), b2Vec2(bod_ragdol[3]->GetPosition().x + 0.05, bod_ragdol[3]->GetPosition().y - 0.28));
	//pecho[1] a pierna  derecha[4]
	joint_def_ragdolino[3].Initialize(bod_ragdol[1], bod_ragdol[4], b2Vec2(bod_ragdol[1]->GetPosition().x + 0.09, bod_ragdol[1]->GetPosition().y + 0.38), b2Vec2(bod_ragdol[4]->GetPosition().x, bod_ragdol[4]->GetPosition().y - 0.38));
	//pecho[1] a pierna izquierda[5]
	joint_def_ragdolino[4].Initialize(bod_ragdol[1], bod_ragdol[5], b2Vec2(bod_ragdol[1]->GetPosition().x + 0.09, bod_ragdol[1]->GetPosition().y + 0.38), b2Vec2(bod_ragdol[5]->GetPosition().x, bod_ragdol[5]->GetPosition().y - 0.38));

	for (int i = 0; i < 5; i++)
	{
		joint_def_ragdolino[i].dampingRatio = 0.3f; //rebote
		joint_def_ragdolino[i].frequencyHz = 4.0f;
		joint_def_ragdolino->collideConnected = true;
		//joint_def_ragdolino[i].length = 0.025f;
		joint_ragdolino[i] = (b2DistanceJoint*)mundo->CreateJoint(&joint_def_ragdolino[i]); //hay que castear
	}

}

void Game::ProcessEvent(Event& evt)
{

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		for (int i = 0; i < 10; i++)
		{
			if (arr_gallardo[i] == NULL)
			{
				if (tiempo1 > tiempo2 + 1)
				{
					
					//alinear la punta del canon con la salida del ragdol
					// convertir grados a radianes
					float angulo_cannon = grados_a_radiannes(cannon2->get_sprite().getRotation());

					// 2 calcular la distancia
					float boca_cannon_distance = 4;

					//3 calculo la nueva pocision
					float boca_x = cannon2->get_rect().getPosition().x + cos(angulo_cannon) * boca_cannon_distance;
					float boca_y = cannon2->get_rect().getPosition().y + sin(angulo_cannon) * boca_cannon_distance;
	
					//aca debe de ir el resultado final de la operacion
					arr_gallardo[i] = new Ragdol(mundo, {boca_x,boca_y}, grados_a_radiannes(cannon2->get_sprite().getRotation()+ 90));
					arr_gallardo[i]->fuerza_disparo(potencia_cannon * 4, grados_a_radiannes(cannon2->get_sprite().getRotation()));
					//cout << "se crean nuevos ragdols" << endl;
					tiempo2 = tiempo1;
					break;
				}
			}
		}
	}

	if (Mouse::isButtonPressed(Mouse::Right))
	{
		//mundo->DestroyBody(bod_piso);
		for (int i = 0; i < 10; i++)
		{
			if (arr_gallardo[i] != NULL)
			{
				arr_gallardo[i]->sacar_cabeza(); //cambiar nombre
				arr_gallardo[i] = NULL;
			}
		}

	}

	switch (evt.type)
	{
	case Event::Closed:
		pWnd->close();
		break;

		//evento de teclado
	case Event::KeyPressed:

		if (evt.key.code == Keyboard::Escape)
		{
			pWnd->close();
		}

		if (evt.key.code == Keyboard::A)
		{
			
		}
		else if (evt.key.code == Keyboard::D)
		{
			
		}
		else if (evt.key.code == Keyboard::S)
		{
			
		}
		break;
	}

}

void Game::set_zoom()
{
	camara1 = new View({11,0.5}, {30.f, 30.f}); // 11 0.5(center)  30 30(tamaño)
	camara1->move(40.f, 90.5f);
	pWnd->setView(*camara1);
}

void Game::actualizar_fisica()
{
	mundo->Step(tiempoFrame, 8, 8);
	mundo->ClearForces();
}

float Game::grados_a_radiannes(float grados)
{
	float pi = 3.14;



	return grados * pi / 180;
}

float Game::radianes_a_grados(float radianes)
{
	float pi = 3.14;

	return radianes / pi * 180;
}

void Game::movimiento_plataformas()
{
	float vel = 0.10;

	if (mov_plat[0]->getGlobalBounds().intersects(piso[1]->getGlobalBounds()))
	{
		vel = -0.10;
		Plataforma_mov[0]->set_pos_y(80.5);
	}
	Plataforma_mov[0]->mover(vel);
}

void Game::Go() {
	//objeto para recibir eventos
	Event evt;
	while (pWnd->isOpen()) {
		//procesar eventos
		while (pWnd->pollEvent(evt))
			ProcessEvent(evt);
		//procesar colisiones
		ProcessCollisions();
		//actualizar estados de objetos
		UpdateGame();
		pWnd->clear();
		actualizar_fisica();
		DrawGame();
		pWnd->display();
	}
}

Game::~Game()
{
}