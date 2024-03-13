#include "Niveles.h"

Niveles::Niveles()
{
}

void Niveles::CargarNivel1(Plataforma_movible* mov_p_forma[], ZonaGanar* &metaA, Pared_estatica* plataforma_estatica[], b2World& mundo, Caja* cajas[], cannon_Sprite* cannon2)
{
	//obstaculos
	mov_p_forma[0] = new Plataforma_movible(&mundo, 0.13, { 45, 80 });
	mov_p_forma[1] = new Plataforma_movible(&mundo, 0.20, { 50, 80 });
	mov_p_forma[2] = new Plataforma_movible(&mundo, 0.22, { 56, 80 });
	//bordes de pantalla
	plataforma_estatica[0] = new Pared_estatica("recursos/matlib.jpg", &mundo, { 50, 104 }, { 3, 1 });
	plataforma_estatica[1] = new Pared_estatica("recursos/matlib.jpg", &mundo, { 60, 82.59 }, { 3, 1 });//arriba
	plataforma_estatica[2] = new Pared_estatica("recursos/matlib.jpg", &mundo, { 52, 98.59 }, { 3, 1 });
	plataforma_estatica[3] = new Pared_estatica("recursos/matlib.jpg", &mundo, { 59, 104.1 }, { 3, 1 });
	//cajas movibles
	cajas[0] = new Caja("recursos/caja.jpg",&mundo, { 61, 80.80 }, { 0.70, 0.75 });//arriba
	cajas[1] = new Caja("recursos/caja.jpg", &mundo, { 59, 80.80 }, { 0.70, 0.75 });//arriba
	cajas[2] = new Caja("recursos/caja.jpg", &mundo, { 51.70, 96.80 }, { 0.70, 0.75 });//medio
	cajas[3] = new Caja("recursos/caja.jpg", &mundo, { 51, 102.25 }, { 0.70, 0.75 });//abajo

	if (true)
	{
		*&metaA = new ZonaGanar("recursos/bandera.png", { 63.5,101 });
		//cout << "se crea el objeto bandera" << endl;
	}


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
			arr_gallardo[i]->destruir_Ragdoll(); //cambiar nombre
			arr_gallardo[i] = NULL;
		}
	}

	//reseteo el cargador de ragdolls
	contador_ragdoll = 10;

	//reseteo el contador de objetivos
	contador_objetivo = 0;
}

void Niveles::CargarNivel2(Pared_estatica* plataforma_estatica[], b2World& mundo, Caja* cajas[], cannon_Sprite* cannon2, RenderWindow *ventana, Helice *geliGiratoria)
{
	cajas[0] = new Caja("recursos/caja.jpg", &mundo, { 60, 83 }, { 0.70, 0.75 });//derecha
	plataforma_estatica[0] = new Pared_estatica("recursos/matlib.jpg", &mundo, { 60, 84.0 }, { 1,	0.75f });

	cajas[1] = new Caja("recursos/caja.jpg", &mundo, { 50, 86.0 }, { 0.70, 0.75 });//derecha
	plataforma_estatica[1] = new Pared_estatica("recursos/matlib.jpg", &mundo, { 50, 87.0 }, { 1, 0.75f});

	cajas[2] = new Caja("recursos/caja.jpg", &mundo, { 44.9, 80.0 }, { 0.70, 0.75 });//izquierda
	plataforma_estatica[2] = new Pared_estatica("recursos/matlib.jpg", &mundo, { 44.9, 81.0 }, { 1, 0.75f });

	cajas[3] = new Caja("recursos/caja.jpg", &mundo, { 61.9, 92.0 }, { 0.70, 0.75 });//izquierda
	plataforma_estatica[3] = new Pared_estatica("recursos/matlib.jpg", &mundo, { 61.9, 93.0 }, { 1, 0.75f });
	//creo 2 cajas
	
	
	
	//reposiciono el cañon
	cannon2->Mover_cannon(ventana,cannon2->get_pos_Nivel2());

	//cargar helice en esta parte.

	//geliGiratoria = new Helice(&mundo, { 49,93 });
}

void Niveles::BorrarNivel2(Pared_estatica* plataforma_estatica[], b2World& mundo, Caja* cajas[], cannon_Sprite* cannon2, RenderWindow* ventana)
{
	//destruir cajas
	for (int i = 0; i < 4; i++)
	{
		if (cajas[i] != NULL)
		{
			cajas[i]->Destruir(&mundo);
			cajas[i] = NULL;
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
	cannon2->Mover_cannon(ventana, cannon2->get_pos_Nivel1());
}

