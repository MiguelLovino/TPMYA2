#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class ZonaGanar
{
private:
	Texture* tex_zona;
	Sprite* spr_zona;

public:
	ZonaGanar(String url, Vector2f pos);
	~ZonaGanar();
	void Dibujar(RenderWindow *ventana);
	Sprite get_spr() { return *spr_zona; }
};

