#include "ADMSound.h"

ADMSound::ADMSound()
{
	//disparo de canion
	bufferCanion.loadFromFile("recursos/Audio/canon.wav");
	soundcanion.setBuffer(bufferCanion);
	soundcanion.setVolume(100);

	//navegarMenu
	bufferMenu.loadFromFile("recursos/Audio/menu.wav");
	soundMenu.setBuffer(bufferMenu);
	soundMenu.setVolume(100);

	//sumarPunto
	bufferpoint.loadFromFile("recursos/Audio/point.wav");
	soundpoint.setBuffer(bufferpoint);
	soundpoint.setVolume(50);

	//gameover
	buffergameover.loadFromFile("recursos/Audio/gameover.wav");
	soundgameover.setBuffer(buffergameover);
	soundgameover.setVolume(100);

	//menu intro
	bufferIntromenu.loadFromFile("recursos/Audio/intromenu.wav");
	soundIntromenu.setBuffer(bufferIntromenu);
	soundIntromenu.setLoop(true);
	soundIntromenu.setVolume(25);

	//cleastage
	bufferClearStage.loadFromFile("recursos/Audio/clearStage.wav");
	soundClearStage.setBuffer(bufferClearStage);
	
	//colicion caja
	bufferColicionCaja.loadFromFile("recursos/Audio/colicionCaja.wav");
	soundColicionCaja.setBuffer(bufferColicionCaja);

	//sonido ambiente de niveles
	bufferAmbiente.loadFromFile("recursos/Audio/sonidoAmbiente.wav");
	soundAmbiente.setBuffer(bufferAmbiente);

	//sonido de victoria de juego
	bufferVictoria.loadFromFile("recursos/Audio/win.wav");
	soundVictoria.setBuffer(bufferVictoria);

}

void ADMSound::DisparoCanion()
{
	soundcanion.play();

}

void ADMSound::NavegarMenu()
{
	soundMenu.play();
	
}

void ADMSound::SumarPunto()
{
	soundpoint.play();
}

void ADMSound::GameOver()
{
	soundgameover.play();
}

void ADMSound::PlayIntroMenu()
{
	if (activarIntroMenu)
	{
		soundIntromenu.setLoop(true);
		soundIntromenu.play();
		activarIntroMenu = false;
	}
}

void ADMSound::StopIntroMenu()
{
	soundIntromenu.setLoop(false);
	soundIntromenu.stop();
	activarIntroMenu = true;
}

void ADMSound::ClearStage()
{
	soundClearStage.play();
}

void ADMSound::ColicionCaja()
{
	soundColicionCaja.play();
}

void ADMSound::Ambiente()
{
	if (!activarSonidoAmbiente)
	{
		soundAmbiente.setLoop(true);
		soundAmbiente.play();
		activarSonidoAmbiente = true;
	}
}

void ADMSound::DesactivarAmbiente()
{
	if (activarSonidoAmbiente)
	{
		soundAmbiente.setLoop(false);
		activarSonidoAmbiente = false;
		soundAmbiente.stop();
	}
}

void ADMSound::Victoria()
{
	soundVictoria.play();
}
