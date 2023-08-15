#include "Niveles.h"

Niveles::Niveles()
{
}

void Niveles::CargarNivel1()
{
}

void Niveles::BorrarNivel1(Plataforma_movible *mov_p_forma[],Pared_estatica* plataforma_estatica[],b2World &mundo, Caja* cajas[], Ragdol* arr_gallardo[], int &contador_ragdoll, int &contador_objetivo)
{
	//Se eliminan los objetos del nivel 1
		
	//plataformas en movimiento
	for (int i = 0; i < 3; i++)
	{
		if (mov_p_forma[i] != NULL)
		{
			mov_p_forma[i]->destruir_plataforma();
			mov_p_forma[i] = NULL;
		}
	}
	
	//destruir piso estaticos
	for (int i = 0; i < 4; i++)
	{
		if (plataforma_estatica[i] != NULL)
		{
			plataforma_estatica[i]->Destruir(&mundo);
			plataforma_estatica[i] = NULL;
		}
	}

	//destruir cajas
	for (int i = 0; i < 4; i++)
	{
		if (cajas[i] != NULL)
		{
			cajas[i]->Destruir(&mundo);
			cajas[i] = NULL;
		}
	}

	
	//destruyo todos los ragdols y reseteo el array para volver a disparar
	for (int i = 0; i < 10; i++)
	{
		if (arr_gallardo[i] != NULL)
		{
			arr_gallardo[i]->sacar_cabeza(); //cambiar nombre
			arr_gallardo[i] = NULL;
		}
	}

	//reseteo el cargador de ragdolls
	contador_ragdoll = 10;

	//reseteo el contador de objetivos
	contador_objetivo = 0;
}

void Niveles::CargarNivel2(Pared_estatica* plataforma_estatica[], b2World& mundo, Caja* cajas[], View &camara1, cannon_Sprite* cannon2)
{
	plataforma_estatica[1] = new Pared_estatica("recursos/matlib.jpg", &mundo, { 60, 82.59 }, { 2, 1 }, &camara1);
	plataforma_estatica[2] = new Pared_estatica("recursos/matlib.jpg", &mundo, { 41.9, 82.59 }, { 2, 1 }, &camara1);
	//creo 2 cajas
	cajas[0] = new Caja("recursos/caja.jpg", &mundo, { 60.5, 81 }, { 0.70, 0.75 }, &camara1);//derecha
	cajas[1] = new Caja("recursos/caja.jpg", &mundo, { 41.5, 81 }, { 0.70, 0.75 }, &camara1);//izquierda

	//reposiciono el cañon
	cannon2->Mover_cannon(350, 550);
}

void Niveles::BorrarNivel2()
{
}
