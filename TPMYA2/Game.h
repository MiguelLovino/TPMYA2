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

using namespace sf;
using namespace std;
class Game {
private:
	RenderWindow* pWnd;
	void ProcessEvent(Event& evt);
	void DrawGame();
	void UpdateGame();
	void ProcessCollisions();

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

	//plataformas movibles.
	RectangleShape* mov_plat[4];
	b2Vec2 mov_plat_posicion[4];

	b2Body* bod_mov_plat[4];
	b2BodyDef boddef_mov_plat[4];
	b2Fixture* fix_mov_plat[4];
	b2FixtureDef fixdef_mov_plat[4];



	//ragdoll

	b2Body* bod_ragdol[6];
	b2BodyDef boddef_ragdol[6];
	b2Fixture* fix_ragdol[6];
	b2FixtureDef fixdef_ragdol[6];

	RectangleShape* fig_ragdol[6];

	float fps, tiempoFrame;

	//avatares
	Avatar* Ragdolino[6];
	Avatar* pisolino[4];
	Avatar* Plataforma_mov[4];
	//**************//
	Avatar* puente_blando[5];
	//**************//
	
	// Resortes del ragdoll
	b2DistanceJoint* joint_ragdolino[5];
	b2DistanceJointDef joint_def_ragdolino[5];

	//clase ragdoll
	Ragdol* gallardo;
	Ragdol* arr_gallardo[10];
	int cant_arr_gallardo = 0;

	//clase cannon
	Cannon* cannon_ragdoll;
	//clase cannon sprite

	cannon_Sprite* cannon2;

	//mouse coord to world
	Vector2i pixel_pos;
	Vector2f world_pos;

	Clock* reloj;
	float tiempo1 = 0;
	float tiempo2 = 0;

	//fuerza del cannon
	float potencia_cannon = 0;

public: Game(int alto, int ancho, string titulo);
	  ~Game(void);
	  void Go();
	  void cargar_imagenes();
	  void set_zoom();
	  void iniciar_fisica();
	  void actualizar_fisica();
	  float grados_a_radiannes(float grados);
	  float radianes_a_grados(float radianes);
	  void movimiento_plataformas();
	  //TODO 
	  //a este proyecto queda empeza a realizar las clases.
};