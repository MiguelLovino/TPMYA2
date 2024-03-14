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
	

public:
	ADMSound();
	void DisparoCanion();
	void NavegarMenu();
	void SumarPunto();
	void GameOver();
	void PlayIntroMenu();
	void StopIntroMenu();
	void ClearStage();
};

