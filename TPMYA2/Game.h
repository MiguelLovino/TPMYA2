#pragma once
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 
#include <Box2D/Box2D.h>
#include "Avatar.h"
#include <string> 
#include "Ragdol.h"
#include "Cannon.h"
#include "cannon_Sprite.h"
#include <iostream>
#include "Plataforma_movible.h"
#include "Pared_estatica.h"
#include "Caja.h"
#include "ZonaGanar.h"

using namespace sf;
using namespace std;
class Game {
private:
	RenderWindow* pWnd;
	void ProcessEvent(Event& evt);
	void DrawGame();
	void Nivel_inicial_dibujar();
	void Nivel_1_dibujar();
	void Nivel_2_dibujar();
	void UpdateGame();
	void Nivel_inicial_actualizar();
	void Nivel_1_actualizar();
	void Nivel_2_actualizar();
	void ProcessCollisions();
	void Nivel_inicial_colisiones();
	void Nivel_1_colisiones();
	void Nivel_2_colisiones();
	Texture* tex_piso;
	Texture* tex_pared;
	Texture* text_cannon;
	Sprite* spr_fondo;
	Texture* tex_fondo;

	View* camara1;
	b2World* mundo;
	float gravedad = 9.8f;

	// 
	//piso
	RectangleShape* piso[4];
	b2Vec2 piso_posicion[4];

	b2Body* bod_piso[4];
	b2BodyDef boddef_piso[4]; //no puede ser puntero
	b2Fixture* fix_piso[4];
	b2FixtureDef fixdef_piso[4]; //no puede ser puntero

	Avatar* pisolino[4];

	float fps, tiempoFrame;

	//clase ragdoll
	Ragdol* arr_gallardo[10];
	int cant_arr_gallardo = 0;

	//clase cannon
	Cannon* cannon_ragdoll;
	//clase cannon sprite
	cannon_Sprite* cannon2;

	//clase plataformas movibles verticales
	Plataforma_movible* mov_p_forma[3];

	//mouse coord to world
	Vector2i pixel_pos;
	Vector2f world_pos;

	Clock* reloj;
	float tiempo1 = 0;
	float tiempo2 = 0;

	//fuerza del cannon
	float potencia_cannon = 0;

	//paredes estaticas
	Pared_estatica* libro[4];

	//cajas dinamicas
	Caja* cajas[4];

	//zona de ganar
	ZonaGanar* metaA;

	//Bandera de Niveles.
	bool Nivel_inicio = true;
	bool Nivel_1 = false;
	bool Nivel_2 = false;

	Font *font_menu;
	Text* jugar;
	Text* Salir;
	Sprite* spr_mira;
	Texture* txt_mira;

	int ventana_ancho;
	int ventana_alto;

public: Game(int ancho, int alto, string titulo);
	  ~Game(void);
	  void Go();
	  void cargar_imagenes();
	  void set_zoom();
	  void iniciar_fisica();
	  void actualizar_fisica();
	  float grados_a_radiannes(float grados);
	  float radianes_a_grados(float radianes);
	  void inicializar_objetos();
	  
};