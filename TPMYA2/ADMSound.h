#pragma once
#include "SFML/Audio.hpp"
#include <iostream>
using namespace sf;
using namespace std;

class ADMSound
{
private:
	SoundBuffer bufferCanion;
	Sound soundcanion;

	SoundBuffer bufferMenu;
	Sound soundMenu;

	SoundBuffer bufferpoint;
	Sound soundpoint;

	SoundBuffer buffergameover;
	Sound soundgameover;

	SoundBuffer bufferIntromenu;
	Sound soundIntromenu;
	bool activarIntroMenu = true;

	SoundBuffer bufferClearStage;
	Sound soundClearStage;
	
	SoundBuffer bufferColicionCaja;
	Sound soundColicionCaja;
	bool colicionCajaActivo[16]{};

	SoundBuffer bufferAmbiente;
	Sound soundAmbiente;
	bool activarSonidoAmbiente = false;

	SoundBuffer bufferVictoria;
	Sound soundVictoria;


public:
	ADMSound();
	void DisparoCanion();
	void NavegarMenu();
	void SumarPunto();
	void GameOver();
	void PlayIntroMenu();
	void StopIntroMenu();
	void ClearStage();
	void ColicionCaja();
	bool get_ColicionCajaReproduciendo(int num) { return colicionCajaActivo[num]; }
	void set_ColicionCajaReproduciendo(bool estado, int num) { colicionCajaActivo[num] = estado; }
	void Ambiente();
	void DesactivarAmbiente();
	void Victoria();
};

