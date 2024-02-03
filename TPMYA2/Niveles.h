#pragma once
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 
#include <Box2D/Box2D.h>
#include "Avatar.h"
#include <string> 
#include "Ragdol.h"
#include "cannon_Sprite.h"
#include <iostream>
#include "Plataforma_movible.h"
#include "Pared_estatica.h"
#include "Caja.h"
#include "ZonaGanar.h"

class Niveles
{
	//clase encargada de administrar la carga y destruccion  de los objetos de cada nivel.

private:
	//banderas de los niveles activos
	bool
		NivelInicial = false,
		Nivel1 = false,
		Nivel2 = false;
	//puntajes
	int
		puntaje_nivel1 = 0,
		puntaje_nivel2 = 0;

public:
	Niveles();

	void CargarNivel1(Plataforma_movible* mov_p_forma[], ZonaGanar* &metaA, Pared_estatica* plataforma_estatica[], b2World& mundo, Caja* cajas[], View& camara1, cannon_Sprite* cannon2);
	void BorrarNivel1(Plataforma_movible* mov_p_forma[], Pared_estatica* plataforma_estatica[], b2World &mundo, Caja* cajas[], Ragdol* arr_gallardo[], int &contador_ragdoll, int& contador_objetivo);
	void CargarNivel2(Pared_estatica* plataforma_estatica[], b2World& mundo, Caja* cajas[], View &camara1, cannon_Sprite* cannon2, RenderWindow* ventana);
	void BorrarNivel2(Pared_estatica* plataforma_estatica[], b2World& mundo, Caja* cajas[], View& camara1, cannon_Sprite* cannon2, RenderWindow* ventana);

	//geter y seter de los puntajes
	//n1
	void set_puntajeNivel1(int num) { puntaje_nivel1 + num; }
	int get_puntajeNivel1() { return puntaje_nivel1; }
	//n2
	void set_puntajeNivel2(int num) { puntaje_nivel2 + num; }
	int get_puntajeNivel2() { return puntaje_nivel2; }

};

