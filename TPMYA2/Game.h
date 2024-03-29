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
#include "Niveles.h"
#include "ADMSound.h"
#include "Mira.h"
#include "BordePantalla.h"
#include "Helice.h"

using namespace sf;
using namespace std;
class Game {
private:
	RenderWindow* pWnd;
	void ProcessEvent(Event& evt);
	
	//Inicio de pantalla
	void Nivel_inicial_dibujar();
	void Nivel_inicial_actualizar();
	void Nivel_inicial_colisiones();

	//nivel 1
	void Nivel_1_dibujar();
	void Nivel_1_actualizar();
	void Nivel_1_colisiones();
	
	//nivel 2
	void Nivel_2_dibujar();
	void Nivel_2_actualizar();
	void Nivel_2_colisiones();
	
	void DrawGame();
	void UpdateGame();
	void ProcessCollisions();
	
	Texture* text_cannon;
	Sprite* spr_fondo;
	Texture* tex_fondo;

	View* camara1;
	b2World* mundo;
	float gravedad = 9.8f;

	//niveles
	Niveles* AdmNiveles;

	float fps, tiempoFrame;

	//calse mira (puntero del mouse)
	Mira* puntero;

	//clase ragdoll
	Ragdol* bala_Ragdoll[10];
	int cant_arr_gallardo = 0;

	//prueba de ragdoll
	Ragdol* ragdolPrueba;


	//borde de pantalla
	BordePantalla* bordePantalla;
	
	//clase cannon sprite
	cannon_Sprite* cannon;

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
	Pared_estatica* plataforma_estatica[4];

	//cajas dinamicas
	Caja* cajas[4];

	//heliceGiratoria
	Helice* heliGiratoria[2];
	

	//zona de ganar
	ZonaGanar* metaA;

	//Bandera de Niveles.
	bool Nivel_inicio = true;
	bool Nivel_1 = false;
	bool Nivel_2 = false;
	bool mousePresionado = false;
	bool gameover = false;
	bool win = false;

	//cargador de ragdolls
	bool cargador_ragdol_vacio = false;
	int contador_ragdoll = 10;
	Text* tx_cargador;

	//texto objetivo
	Text* tx_objetivo;

	//texto del menu
	Font *font_menu;
	Text* jugar;
	Text* Salir;
	Text* Reiniciar;
	Text* Perdiste;
	Text* Ganaste;
	Text* misionLv1;
	Text* misionLv2;

	Sprite* spr_menu;
	Texture* txt_menu;

	int ventana_ancho;
	int ventana_alto;
	int puntajeNivel1 = 0;

	//bandera de menu
	bool salirSelec = true;
	bool jugarSelec = true;
	bool reiniciarSelec = true;

	//sonido
	ADMSound *AdministradorSonido;

public: Game(int ancho, int alto, string titulo);
	  ~Game(void);
	  void actualizar_cargador_ragdoll();
	  void Go();
	  void cargar_imagenes();
	  void cargar_sonido();
	  void set_zoom();
	  void iniciar_fisica();
	  void actualizar_fisica();
	  float grados_a_radiannes(float grados);
	  float radianes_a_grados(float radianes);
	  void inicializar_objetos();
	  void texto_pos(Text* texto, int x, int y);
	  void inicializarTexto(Text* texto, int size, Color color, Color color2, string str1, int strVariable, float grosorBorde);
	  void ColicionCaja(FloatRect quad, FloatRect caja, int it);
};