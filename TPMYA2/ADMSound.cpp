#include "ADMSound.h"

ADMSound::ADMSound()
{
	//disparo de canion
	bufferCanion.loadFromFile("recursos/Audio/canon.wav");
	soundcanion.setBuffer(bufferCanion);

	//navegarMenu
	bufferMenu.loadFromFile("recursos/Audio/menu.wav");
	soundMenu.setBuffer(bufferMenu);

	//sumarPunto

	bufferpoint.loadFromFile("recursos/Audio/point.wav");
	soundpoint.setBuffer(bufferpoint);
}

void ADMSound::DisparoCanion()
{
	soundcanion.play();

}

void ADMSound::NavegarMenu()
{
	soundMenu.play();
	//cout << "hola" << endl;
}

void ADMSound::SumarPunto()
{
	soundpoint.play();
}

