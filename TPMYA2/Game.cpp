#include "Game.h"

Game::Game(int ancho, int alto, string titulo)
{
	ventana_ancho = ancho;
	ventana_alto = alto;
	pWnd = new RenderWindow(VideoMode(ventana_ancho, ventana_alto), titulo);
	fps = 60.f;
	tiempoFrame = 1.f / fps;
	pWnd->setFramerateLimit(fps);
	pWnd->setMouseCursorVisible(false);
	//pWnd->setMouseCursorGrabbed(true);
	set_zoom();
	cargar_imagenes();
	iniciar_fisica();
	inicializar_objetos();

}
void Game::UpdateGame() //actualizo los objetos
{
	//la posicion del mouse en el mundo 
	pixel_pos = Mouse::getPosition(*pWnd);
	world_pos = pWnd->mapPixelToCoords(pixel_pos);

	spr_mira->setPosition(pWnd->mapPixelToCoords(Mouse::getPosition(*pWnd)));

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

	Nivel_inicial_actualizar();
	Nivel_1_actualizar();
	Nivel_2_actualizar();

}

void Game::Nivel_inicial_actualizar()
{

}

void Game::Nivel_1_actualizar()
{

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

	mov_p_forma[0]->actualizar(102, 80);
	mov_p_forma[1]->actualizar(95, 80);
	mov_p_forma[2]->actualizar(100, 80);

	for (int i = 0; i < 4; i++)
	{
		cajas[i]->Actualizar();
	}
}

void Game::Nivel_2_actualizar()
{
}

void Game::DrawGame()
{
	Nivel_inicial_dibujar();
	Nivel_1_dibujar();
	Nivel_2_dibujar();		
}

void Game::Nivel_inicial_dibujar()
{
	/*********** Nivel inicio **********/
	if (Nivel_inicio)
	{
		pWnd->draw(*spr_fondo);
		pWnd->draw(*jugar);
		pWnd->draw(*Salir);
		pWnd->draw(*spr_mira);
	}
}

void Game::Nivel_1_dibujar()
{
	/*********** Nivel 1 **********/
	if (Nivel_1)
	{
		//fondo de la pantalla.
		pWnd->draw(*spr_fondo);

		//zona meta
		metaA->Dibujar(pWnd);

		//plataformas movibles
		for (int i = 0; i < 3; i++)
		{
			mov_p_forma[i]->dibujar(pWnd);
		}

		//ragdols
		for (int i = 0; i < 10; i++)
		{
			if (arr_gallardo[i] != NULL)
			{
				//dibujo los cuerpos de los ragdols
				arr_gallardo[i]->dibujar_ragdol(pWnd);
			}
		}

		//piso
		for (int i = 0; i < 4; i++)
		{
			pisolino[i]->dibujar_ragdol(*pWnd);
		}

		//canon
		cannon2->dibujar(pWnd);

		//libros
		for (int i = 0; i < 4; i++)
		{
			libro[i]->Dibujar(pWnd);
		}

		//cajas
		for (int i = 0; i < 4; i++)
		{
			cajas[i]->Dibujar(pWnd);
		}
	}
	pWnd->draw(*spr_mira);
}

void Game::Nivel_2_dibujar()
{
	/*********** Nivel 2 **********/
	if (Nivel_2)
	{

	}
}

void Game::ProcessCollisions()
{
	Nivel_inicial_colisiones();
	Nivel_1_colisiones();
	Nivel_2_colisiones();
}

void Game::Nivel_inicial_colisiones()
{
	if (Nivel_inicio)
	{
		//si hago click en jugar, avanzo a nivel 1, si hago click en salir, salgo del huego
		if (spr_mira->getGlobalBounds().intersects(jugar->getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
		{
			Nivel_inicio = false;
			Nivel_1 = true;
		}
		if (spr_mira->getGlobalBounds().intersects(Salir->getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
		{
			pWnd->close();
		}
	}
}

void Game::Nivel_1_colisiones()
{
	if (Nivel_1)
	{
		//controlo la colicion de las plataformas en movimiento con el piso
		for (int i = 0; i < 3; i++)
		{
			mov_p_forma[i]->colicion(piso);
		}
	}
}

void Game::Nivel_2_colisiones()
{
	if (Nivel_2)
	{

	}
}

void Game::cargar_imagenes()
{
	tex_piso = new Texture;
	tex_piso->loadFromFile("recursos/pared2.png");
	tex_pared = new Texture;
	tex_pared->loadFromFile("recursos/pared3.png");
	//imagen del piso
	
		piso[0] = new RectangleShape;
		piso[0]->setTexture(tex_piso);
		piso[1] = new RectangleShape;
		piso[1]->setTexture(tex_piso);
		piso[2] = new RectangleShape;
		piso[2]->setTexture(tex_pared);
		piso[3] = new RectangleShape;
		piso[3]->setTexture(tex_pared);

	//imagen del fondo
	tex_fondo = new Texture;
	tex_fondo->loadFromFile("recursos/fondo_pantalla_mya4.jpg");
	spr_fondo = new Sprite(*tex_fondo);

	//escalo el fondo y lo posiciono
	Vector2f fondopos = pWnd->mapPixelToCoords({ 0, 0 });
	spr_fondo->setPosition(fondopos.x, fondopos.y);
	spr_fondo->setScale(camara1->getSize().x / spr_fondo->getGlobalBounds().width, camara1->getSize().y / spr_fondo->getGlobalBounds().height );

	//cargo y posiciono las letras del menu.

}

void Game::iniciar_fisica()
{
	//creo el mundo

	mundo = new b2World(b2Vec2(0,gravedad));

	/*****************************/

	//definicion_body (piso)
	for (int i = 0; i < 4; i++)
	{
		boddef_piso[i].type = b2_staticBody; //def
	}
	boddef_piso[0].position = b2Vec2(50.f, 76.f); //def techo
	boddef_piso[1].position = b2Vec2(50.f, 106.f); //def suelo

	boddef_piso[2].position = b2Vec2(66.f, 91.f); //def pared derecha 
	boddef_piso[3].position = b2Vec2(36.f, 91.f); //def pared izquierda

	//body del piso en el mundo
	for (int i = 0; i < 4; i++)
	{
		bod_piso[i] = mundo->CreateBody(&boddef_piso[i]); // linkeo el body a su definicion creada por el mundo
	}

	//creo una shape para asignar al fixture
	b2PolygonShape shape_piso; //techo
	shape_piso.SetAsBox(15.f, 1.f); // tiene que ser la mitad de la caja (en x, y)

	b2PolygonShape shape_pared;
	shape_pared.SetAsBox(1.f, 15.f);

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

}

void Game::ProcessEvent(Event& evt)
{
	// si hago click en el nivel 1 o 2, disparo un ragdol
	if (Nivel_1 || Nivel_2)
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

void Game::inicializar_objetos()
{
	//inicializo objetos generales
		/*MIRA*/
	txt_mira = new Texture;
	txt_mira->loadFromFile("recursos/mira.png");
	spr_mira = new Sprite(*txt_mira);
	spr_mira->setOrigin(spr_mira->getGlobalBounds().width / 2, spr_mira->getGlobalBounds().height / 2);
	spr_mira->setScale(camara1->getSize().x / ventana_ancho, camara1->getSize().y / ventana_alto);


	//inicializo objetos Nivel 1.
	cannon2 = new cannon_Sprite;

	reloj = new Clock;

	for (int i = 0; i < 4; i++)
	{
		pisolino[i] = new Avatar(bod_piso[i], piso[i]);
	}
	//obstaculos
	mov_p_forma[0] = new Plataforma_movible(mundo, 0.13, { 45, 80 });
	mov_p_forma[1] = new Plataforma_movible(mundo, 0.20, { 50, 80 });
	mov_p_forma[2] = new Plataforma_movible(mundo, 0.22, { 56, 80 });
	//bordes de pantalla
	libro[1] = new Pared_estatica("recursos/matlib.jpg", mundo, { 60, 82.59 }, { 3, 1 }, camara1);//arriba
	libro[2] = new Pared_estatica("recursos/matlib.jpg", mundo, { 52, 98.59 }, { 3, 1 }, camara1);
	libro[0] = new Pared_estatica("recursos/matlib.jpg", mundo, { 50, 104 }, { 3, 1 }, camara1);
	libro[3] = new Pared_estatica("recursos/matlib.jpg", mundo, { 59, 104.1 }, { 3, 1 }, camara1);
	//bajas movibles
	cajas[0] = new Caja("recursos/caja.jpg", mundo, { 60.5, 82.59 }, { 0.70, 0.75 }, camara1);//arriba
	cajas[1] = new Caja("recursos/caja.jpg", mundo, { 59.5, 82.59 }, { 0.70, 0.75 }, camara1);//arriba
	cajas[2] = new Caja("recursos/caja.jpg", mundo, { 51.70, 98.59 }, { 0.70, 0.75 }, camara1);
	cajas[3] = new Caja("recursos/caja.jpg", mundo, { 51, 102 }, { 0.70, 0.75 }, camara1);

	metaA = new ZonaGanar("recursos/bandera.png", { 63.5,101 });

	//Menu pantalla inicial
	font_menu = new Font;
	font_menu->loadFromFile("recursos/letra.ttf");
	jugar = new Text;
	jugar->setFont(*font_menu);
	jugar->setCharacterSize(45);
	jugar->setFillColor(Color::Red);
	jugar->setString("Jugar");

	Salir = new Text;
	Salir->setFont(*font_menu);
	Salir->setCharacterSize(45);
	Salir->setFillColor(Color::Red);
	Salir->setString("Salir");
	Salir->setPosition(5, 10);
	
	//transformo las cordenadas 
	Vector2f jugar_pos = pWnd->mapPixelToCoords({ 300, 200 });
	jugar->setPosition(jugar_pos.x, jugar_pos.y);
	//escalo el texto tomando la camara (lo que estoy viendo) divido el ancho y alto de la ventana.
	jugar->setScale(camara1->getSize().x / ventana_ancho , camara1->getSize().y / ventana_alto);

	Vector2f salir_pos = pWnd->mapPixelToCoords({ 300, 300 });
	Salir->setPosition(salir_pos.x, salir_pos.y);
	Salir->setScale(camara1->getSize().x / ventana_ancho, camara1->getSize().y / ventana_alto);

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