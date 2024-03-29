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
	pWnd->setMouseCursorGrabbed(true);
	set_zoom();
	cargar_sonido();
	cargar_imagenes();
	iniciar_fisica();
	inicializar_objetos();

}
void Game::UpdateGame() //actualizo los objetos
{
	//actualizo mira
	puntero->Actualizar(pWnd);

	//actualizo el cannon
	cannon->actualizar(puntero->get_world_pos(), pWnd, Nivel_1);

	//actualizo el tiempo
	tiempo1 = reloj->getElapsedTime().asSeconds();

	//actualizo el cargador.
	actualizar_cargador_ragdoll();

	Nivel_inicial_actualizar();
	Nivel_1_actualizar();
	Nivel_2_actualizar();

	//actualizacion del texto del cargador.
	tx_cargador->setString("Disparos restantes: " + to_string(contador_ragdoll));

	
	
}

void Game::Nivel_inicial_colisiones()
{
	if (Nivel_inicio) //logica para el boton de SALIR del menu NOTA: el boton de jugar se encuentra en la parte de Eventos.
	{
		//activo el sonido del menu
		AdministradorSonido->PlayIntroMenu();
		AdministradorSonido->DesactivarAmbiente();
		
		
		// si la mira, choca con el texto salir
		if (puntero->get_sprite().getGlobalBounds().intersects(Salir->getGlobalBounds()))//true
		{
			if (salirSelec)
			{
				//resalta de color blanco el texto
				Salir->setOutlineThickness(5);
				
				AdministradorSonido->NavegarMenu();
				salirSelec = false;
			}

			//si hago click izquierdo, salgo del juego
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				
				pWnd->close();
				
			}
		}
		//de lo contrario (cuando la colicion sea falsa)
		else
		{
			//saca el resaltado
			Salir->setOutlineThickness(0);
			salirSelec = true;
		}
		
	}
}
void Game::Nivel_inicial_actualizar()
{
	
	tx_objetivo->setString("Cajas en zona: " + to_string(puntajeNivel1));
}
void Game::Nivel_inicial_dibujar()
{
	/*********** Nivel inicio **********/
	if (Nivel_inicio)
	{
		pWnd->draw(*spr_fondo);
		pWnd->draw(*spr_menu);
		pWnd->draw(*jugar);
		pWnd->draw(*Salir);
		puntero->Dibujar(pWnd);
	}
}

void Game::Nivel_1_colisiones()
{
	
	if (Nivel_1)
	{

			FloatRect piso = bordePantalla->get_rect(0).getGlobalBounds();
			FloatRect techo = bordePantalla->get_rect(1).getGlobalBounds();
			FloatRect paredI = bordePantalla->get_rect(2).getGlobalBounds();
			FloatRect paredD = bordePantalla->get_rect(3).getGlobalBounds();

		for (size_t i = 0; i < 4; i++)
		{

			FloatRect caja = cajas[i]->get_rect().getGlobalBounds();

			ColicionCaja(caja, piso, i);
			ColicionCaja(caja, techo, i + 4);
			ColicionCaja(caja, paredD, i + 8);
			ColicionCaja(caja, paredI, i + 12);
		
		}

	}
	
}
void Game::Nivel_1_actualizar()
{
	if (Nivel_1)
	{
		AdministradorSonido->Ambiente();

		for (int i = 0; i < 10; i++)
		{
			//actualizo el arreglo de ragdols
			if (bala_Ragdoll[i] != NULL)
			{
				for (int j = 0; j < 6; j++)
				{
					bala_Ragdoll[i]->get_avatar(j).actualizar_ragdol();
				}
			}
		}

		//actualiza el moviento de la plataforma y controla los limites (arriba y abajo)
		if(mov_p_forma[0] != NULL) mov_p_forma[0]->actualizar(102, 80);
		if (mov_p_forma[1] != NULL) mov_p_forma[1]->actualizar(95, 80);
		if (mov_p_forma[2] != NULL) mov_p_forma[2]->actualizar(100, 80);

		for (int i = 0; i < 4; i++)
		{
			if (cajas[i] != NULL)
			{
			  cajas[i]->Actualizar();
			}
		}
	
		//consulto si alguna de las cajas se encuentran en la meta.
		for (int i = 0; i < 4; i++)
		{
			if (cajas[i] != NULL && metaA != NULL)
			{

				if (cajas[i]->get_rect().getGlobalBounds().intersects(metaA->get_spr().getGlobalBounds()))
				{

				int c_pos_X = cajas[i]->get_rect().getPosition().x;
				int c_pos_Y = cajas[i]->get_rect().getPosition().y;

					if (c_pos_X > 61 && c_pos_X < 65 && c_pos_Y > 93 && c_pos_Y < 106)
					{
						if (cajas[i]->enPosicion == false)
						{
							//activo una bandera para saber que esta en el lugar correcto
							cajas[i]->enPosicion = true;
							//sumo un punto a la condicion de pasar de nivel
							puntajeNivel1++;
							AdministradorSonido->SumarPunto();
					
						}
					}

				}
			}
		}
		/***************************PASAR DE NIVEL*******************************************/
		//si almenos 3 cajas se encuentran en la zona de meta, se pasa de pantalla
		if (puntajeNivel1 >= 3)
		{	
			//sonido de pasar nivel.
			AdministradorSonido->ClearStage();
			//activo y desactivo las banderas correspondientes.
			Nivel_1 = false;
			Nivel_2 = true;
		
			//borro los objetos del nivel 1
			AdmNiveles->BorrarNivel1(mov_p_forma, plataforma_estatica, *mundo, cajas, bala_Ragdoll, contador_ragdoll, puntajeNivel1);

			//creo los objetos del nivel 2
			AdmNiveles->CargarNivel2(plataforma_estatica, *mundo, cajas, cannon,pWnd,heliGiratoria);
		
		
		}
	}
}

void Game::Nivel_1_dibujar()
{
	/*********** Nivel 1 **********/
	if (Nivel_1)
	{
		//fondo de la pantalla.
		pWnd->draw(*spr_fondo);

		//borde de pantalla
		bordePantalla->Dibujar(pWnd);

		//zona meta
		if (metaA != NULL)
		{
			metaA->Dibujar(pWnd);
			
		}
		

		//plataformas movibles
		for (int i = 0; i < 3; i++)
		{
			
			if (mov_p_forma[i] != NULL) mov_p_forma[i]->dibujar(pWnd);
		}
		
		//ragdols
		for (int i = 0; i < 10; i++)
		{
			if (bala_Ragdoll[i] != NULL)
			{
				//dibujo los cuerpos de los ragdols
				bala_Ragdoll[i]->dibujar_ragdol(pWnd);
			}
		}

		//canon
		cannon->dibujar(pWnd);

		//piso
		

		//pisos estaticos flotantes
		for (int i = 0; i < 4; i++)
		{
			plataforma_estatica[i]->Dibujar(pWnd);
		}

		//cajas
		for (int i = 0; i < 4; i++)
		{
			if (cajas[i] != NULL)
			{
				cajas[i]->Dibujar(pWnd);
			}

		}
		//cargador
		pWnd->draw(*tx_cargador);
		//objetivo
		pWnd->draw(*tx_objetivo);
		pWnd->draw(*misionLv1);
	}

	if (cargador_ragdol_vacio == true)
	{
		pWnd->draw(*spr_menu);
		pWnd->draw(*Reiniciar);
		pWnd->draw(*Salir);
		pWnd->draw(*Perdiste);
		if (!gameover)
		{
			gameover = true;
			AdministradorSonido->GameOver();
		}
	}

	puntero->Dibujar(pWnd);
}

void Game::Nivel_2_colisiones()
{
	if (Nivel_2)
	{
		for (int i = 0; i < 4; i++)
		{
			if (cajas[i] != NULL && bordePantalla != NULL)
			{

				if (cajas[i]->get_rect().getGlobalBounds().intersects(bordePantalla->get_rect(1).getGlobalBounds()))
				{
					//si coliciono con el piso, sumo 1 punto.
					if (cajas[i]->daPuntosN2)
					{
						puntajeNivel1++;
						AdministradorSonido->SumarPunto();
						cajas[i]->daPuntosN2 = false;
					}
				
				}
			}

		}
		//controlo las coliciones para reproducir el sonido
		FloatRect piso = bordePantalla->get_rect(0).getGlobalBounds();
		FloatRect techo = bordePantalla->get_rect(1).getGlobalBounds();
		FloatRect paredI = bordePantalla->get_rect(2).getGlobalBounds();
		FloatRect paredD = bordePantalla->get_rect(3).getGlobalBounds();

		for (size_t i = 0; i < 4; i++)
		{
			FloatRect caja = cajas[i]->get_rect().getGlobalBounds();

			ColicionCaja(caja, piso, i);
			ColicionCaja(caja, techo, i + 4);
			ColicionCaja(caja, paredD, i + 8);
			ColicionCaja(caja, paredI, i + 12);
		}

	}
		
	
}
void Game::Nivel_2_actualizar()
{
	if (Nivel_2)
	{
		
		for (int i = 0; i < 10; i++)
		{
			//actualizo el arreglo de ragdols
			if (bala_Ragdoll[i] != NULL)
			{
				for (int j = 0; j < 6; j++)
				{
					bala_Ragdoll[i]->get_avatar(j).actualizar_ragdol();
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (cajas[i] != NULL)
			{
				cajas[i]->Actualizar();
			}
		}
		
		heliGiratoria[0]->MovimientoHorizontal();
		heliGiratoria[1]->MovimientoVertical();

		if (puntajeNivel1 >= 3)
		{
			if (!win)
			{
				AdministradorSonido->ClearStage();
			}
			win = true;
			gameover = true;

		}



	}

}

void Game::Nivel_2_dibujar()
{
	/*********** Nivel 2 **********/
	if (Nivel_2)
	{
		pWnd->draw(*spr_fondo);
 
		
		//borde de pantalla
		bordePantalla->Dibujar(pWnd);

		//ragdols
		for (int i = 0; i < 10; i++)
		{
			if (bala_Ragdoll[i] != NULL)
			{
				//dibujo los cuerpos de los ragdols
				bala_Ragdoll[i]->dibujar_ragdol(pWnd);
			}
		}
		//pisos estaticos flotantes
		for (int i = 0; i < 4; i++)
		{
			if (plataforma_estatica[i] != NULL)
			{
				plataforma_estatica[i]->Dibujar(pWnd);
			}
		}

		//cajas
		for (int i = 0; i < 4; i++)
		{
			if (cajas[i] != NULL)
			{
				cajas[i]->Dibujar(pWnd);
			}
		}

			for (int i = 0; i < 2; i++)
			{
				if (heliGiratoria != NULL)
				{
					heliGiratoria[i]->Dibujar(pWnd);
				}

			}


			//dibujo el contador
			pWnd->draw(*tx_objetivo);
			//dibujar cargador
			pWnd->draw(*tx_cargador);
			//canon
			cannon->dibujar(pWnd);
			//mision
			pWnd->draw(*misionLv2);



		if (cargador_ragdol_vacio == true)
		{
			pWnd->draw(*spr_menu);
			pWnd->draw(*Reiniciar);
			pWnd->draw(*Salir);
			pWnd->draw(*Perdiste);
		}

		if (puntajeNivel1 >= 3)
		{
			//texto ganaste
			pWnd->draw(*Ganaste);
			pWnd->draw(*spr_menu);
			pWnd->draw(*Reiniciar);
			pWnd->draw(*Salir);

		}
		puntero->Dibujar(pWnd);
	}
}


void Game::DrawGame()
{

	Nivel_inicial_dibujar();
	Nivel_1_dibujar();
	Nivel_2_dibujar();		
}

void Game::ProcessCollisions()
{
	Nivel_inicial_colisiones();
	Nivel_1_colisiones();
	Nivel_2_colisiones();
}

void Game::cargar_imagenes()
{

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

void Game::cargar_sonido()
{
	AdministradorSonido = new ADMSound;
}

void Game::iniciar_fisica()
{
	//creo el mundo

	mundo = new b2World(b2Vec2(0,gravedad));

	/*****************************/ 
}

void Game::ProcessEvent(Event& evt)
{

	/***********************************reinicio nivel ***************************************/
	if (cargador_ragdol_vacio == true || (puntajeNivel1 >= 3 && !cargador_ragdol_vacio))
	{
		//si hago click en reiniciar, reseteo el nivel, si hago click en salir, salgo del juego
		if (puntero->get_sprite().getGlobalBounds().intersects(Reiniciar->getGlobalBounds()))
		{
			if (reiniciarSelec)
			{
				Reiniciar->setOutlineThickness(5);
				AdministradorSonido->NavegarMenu();
				reiniciarSelec = false;
			}
			if (mousePresionado && evt.type == Event::MouseButtonReleased && evt.mouseButton.button == Mouse::Left)
			{
				if (Nivel_1)
				{
					Nivel_1 = false;
					Nivel_inicio = true;
					gameover = false;
					win = false;
					AdmNiveles->BorrarNivel1(mov_p_forma, plataforma_estatica, *mundo, cajas, bala_Ragdoll, contador_ragdoll, puntajeNivel1);

				}

				if (Nivel_2)
				{
					AdmNiveles->BorrarNivel2(plataforma_estatica, *mundo, cajas, cannon, pWnd, heliGiratoria);
					Nivel_2 = false;
					Nivel_inicio = true;
					gameover = false;
					win = false;
				}

				//destruyo todos los ragdols y reseteo el array para volver a disparar
				for (int i = 0; i < 10; i++)
				{
					if (bala_Ragdoll[i] != NULL)
					{
						bala_Ragdoll[i]->destruir_Ragdoll(); //cambiar nombre
						bala_Ragdoll[i] = NULL;
					}
				}

				//reseteo el cargador de ragdolls
				contador_ragdoll = 10;
				puntajeNivel1 = 0;
				mousePresionado = false;
				cargador_ragdol_vacio = false;
			}
		}
		else
		{
			Reiniciar->setOutlineThickness(0);
			reiniciarSelec = true;
		}

		if (puntero->get_sprite().getGlobalBounds().intersects(Salir->getGlobalBounds()))
		{
			if (salirSelec)
			{
				Salir->setOutlineThickness(5);
				AdministradorSonido->NavegarMenu();
				salirSelec = false;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				pWnd->close();
			}
		}
		else
		{
			Salir->setOutlineThickness(0);
			salirSelec = true;
		}

	}
	//si hago click izquierdo vuelvo verdadera la variable mousePresionado
	if (evt.type == Event::MouseButtonPressed && evt.mouseButton.button == Mouse::Left)
	{
		mousePresionado = true;
		
	}


	// si hago click en el nivel 1 o 2, disparo un ragdol
	if (Nivel_1 || Nivel_2)
	{
		if (cargador_ragdol_vacio == false && mousePresionado && evt.type == Event::MouseButtonReleased && evt.mouseButton.button == Mouse::Left && !gameover)
		{
			for (int i = 0; i < 10; i++)
			{
				if (bala_Ragdoll[i] == NULL)
				{
					if (tiempo1 > tiempo2 + 1)
					{
						//alinear la punta del canon con la salida del ragdol
						// convertir grados a radianes
						float angulo_cannon = grados_a_radiannes(cannon->get_sprite().getRotation());

						// 2 calcular la distancia
						float boca_cannon_distance = 4;

						//3 calculo la nueva pocision
						float boca_x = cannon->get_rect().getPosition().x + cos(angulo_cannon) * boca_cannon_distance;
						float boca_y = cannon->get_rect().getPosition().y + sin(angulo_cannon) * boca_cannon_distance;
	
						//aca debe de ir el resultado final de la operacion
						
						bala_Ragdoll[i] = new Ragdol(mundo, { boca_x,boca_y },  (Vector2f)cannon->get_pos_Nivel1(), cannon->get_sprite().getRotation());
						bala_Ragdoll[i]->fuerza_disparo( cannon->get_potencia_cannon() * 4, grados_a_radiannes(cannon->get_sprite().getRotation() ));
					
						tiempo2 = tiempo1;
						contador_ragdoll--;
						mousePresionado = false;

						AdministradorSonido->DisparoCanion();					
						break;

					}
				}
			}
		}
		
		//actualizo la bandera del cargador que despues es tomada en cuenta para el fin del juego.
		if (cargador_ragdol_vacio == false && mousePresionado && evt.type == Event::MouseButtonReleased && evt.mouseButton.button == Mouse::Left && contador_ragdoll == 0)
		{
			cargador_ragdol_vacio = true;
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

			// teclas para debug.
			if (evt.key.code == Keyboard::Num1)
			{
				//puntajeNivel1++;
			}
			if (evt.key.code == Keyboard::Num2)
			{
				//cargador_ragdol_vacio = true;
			}

	}

	//si hago click en jugar, avanzo a nivel 1, si hago click en salir, salgo del juego
	
	//checkeo la colicion de los sprite
	if (Nivel_inicio && puntero->get_sprite().getGlobalBounds().intersects(jugar->getGlobalBounds()))
	{
		if (jugarSelec)
		{
			//agrego contorno
			jugar->setOutlineThickness(5);
			AdministradorSonido->NavegarMenu();
			jugarSelec = false;
		}
		//si mousePresionado es verdadero y suelto el boton izquierdo
		if (mousePresionado && evt.type == Event::MouseButtonReleased && evt.mouseButton.button == Mouse::Left)
		{
			//realizo el cambio de pantalla.
			Nivel_inicio = false;
			Nivel_1 = true;

			//corto el sonido del menu
			AdministradorSonido->StopIntroMenu();
			
			//cargo el nivel 1
			AdmNiveles->CargarNivel1(mov_p_forma, metaA, plataforma_estatica, *mundo, cajas, cannon);

			mousePresionado = false;
		}
	}
	else
	{
		//si no colisiono, le saco el contorno
		jugar->setOutlineThickness(0);
		jugarSelec = true;
		
	}



	if (mousePresionado && evt.type == Event::MouseButtonReleased && evt.mouseButton.button == Mouse::Left)
	{
		mousePresionado = false;
		
	}
}

void Game::set_zoom()
{
	camara1 = new View({11,0.5}, {30.f, 30.f}); // 11 0.5(center)  30 30(tama�o)
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
	AdmNiveles = new Niveles;

	//inicializo objetos generales
	
	//borde de pantalla
	bordePantalla = new BordePantalla(mundo);

	

	// mira
	puntero = new Mira(camara1, ventana_ancho, ventana_alto);


	//menu
	txt_menu = new Texture;
	txt_menu->loadFromFile("recursos/papiro2.png");
	spr_menu = new Sprite(*txt_menu);
	Vector2f spr_pos = pWnd->mapPixelToCoords({ 10, 120 });
	spr_menu->setPosition(spr_pos.x, spr_pos.y);
	spr_menu->setScale(camara1->getSize().x / ventana_ancho, camara1->getSize().y / ventana_alto);

	//inicializo objetos Nivel 1.
	cannon = new cannon_Sprite(pWnd);

	reloj = new Clock;
	
	//Menu pantalla inicial
	font_menu = new Font;
	font_menu->loadFromFile("recursos/letra.ttf");
	
	//boton jugar
	jugar = new Text;
	inicializarTexto(jugar, 35, Color::Red, Color::White, "Jugar", NULL,0);
	texto_pos(jugar, 60, 170);
	
	//boton salir
	Salir = new Text;
	inicializarTexto(Salir, 35, Color::Red, Color::White, "Salir", NULL,0);
	texto_pos(Salir, 60, 250);

	//texto del cargador de ragdols
	tx_cargador = new Text;
	inicializarTexto(tx_cargador, 15, Color::Black, Color::White, "Disparos restantes: ", contador_ragdoll,5);
	texto_pos(tx_cargador, 5, 584);
	

	//texto de objetivo
	tx_objetivo = new Text;
	inicializarTexto(tx_objetivo, 15, Color::Yellow, Color::Black, "Objetivos en zona: ", puntajeNivel1,5);
	texto_pos(tx_objetivo, 300, 584);

	//texto perdiste
	Perdiste = new Text;
	inicializarTexto(Perdiste, 35, Color::Black, Color::White, "Perdiste!!!",NULL,5);
	texto_pos(Perdiste, 300, 200);
	
	//texto ganaste
	Ganaste = new Text;
	inicializarTexto(Ganaste, 35, Color::Green, Color::White, "Ganaste!!", NULL,5);
	texto_pos(Ganaste, 300, 200);

	//boton reiniciar
	Reiniciar = new Text;
	inicializarTexto(Reiniciar, 35, Color::Black, Color::White, "Reiniciar", NULL,0);
	texto_pos(Reiniciar,35, 170);

	//texto mision 1
	misionLv1 = new Text;
	inicializarTexto(misionLv1, 13, Color::Yellow, Color::Black, "Mision:Las cajas deben llegar a la bandera.", NULL, 5);
	texto_pos(misionLv1, 26, 0);
	
	//texto mision 2
	misionLv2 = new Text;
	inicializarTexto(misionLv2, 15, Color::Yellow, Color::Black, "Mision:Las cajas deben llegar al suelo", NULL, 5);
	texto_pos(misionLv2, 26, 0);

}

void Game::texto_pos(Text* texto, int x, int y)
{
	//traslado la posicion de pixel a cordenada en el mundo de box2d
	Vector2f posicion = pWnd->mapPixelToCoords({ x,y });
	//seteo la nueva cordenada en el mundo
	texto->setPosition(posicion.x, posicion.y);
	//escalo el texto segun la camara y la ventana
	texto->setScale(camara1->getSize().x / ventana_ancho, camara1->getSize().y / ventana_alto);
}

void Game::inicializarTexto(Text* texto,int size, Color color, Color color2, string str1, int strVariable, float grosorBorde)
{
	//metodo usado para simplificar la aplicacion de texto en pantalla.

	texto->setFont(*font_menu);
	texto->setCharacterSize(size);
	texto->setFillColor(color);
	if (strVariable != NULL)
	{
		texto->setString(str1 + to_string(strVariable));
	}
	else
	{
		texto->setString(str1);
	}
	texto->setOutlineColor(color2);
	texto->setOutlineThickness(grosorBorde);
}

void Game::ColicionCaja(FloatRect quad, FloatRect caja, int it)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (caja.intersects(quad))
		{
			if (AdministradorSonido->get_ColicionCajaReproduciendo(it) == false)
			{
				AdministradorSonido->ColicionCaja();
				AdministradorSonido->set_ColicionCajaReproduciendo(true, it);
			}
		}
		else
		{
			AdministradorSonido->set_ColicionCajaReproduciendo(false, it);
		}
	}

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

void Game::actualizar_cargador_ragdoll()
{
	if (contador_ragdoll >= 10)
	{
		//cargador_ragdol_vacio = true;
}

}

