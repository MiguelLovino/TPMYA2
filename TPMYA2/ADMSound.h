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

public:
	ADMSound();
	void DisparoCanion();
	void NavegarMenu();
	void SumarPunto();
};

