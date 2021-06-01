#pragma once
#include<SDL.h>
#include<iostream>
#include"rgbhsv.h"
class dot
{
private:
	const int SCREEN_W = 500;
	const int SCREEN_H = 500;
	SDL_Rect dotRect;
	float xPos;
	float yPos;
	int hue = 0;
	float xVel;
	float yVel;
	SDL_Color color;

public:
	dot();
	float getX();
	float getY();
	void move();
	void draw(SDL_Renderer* renderer);
	void setColor(SDL_Color newColor);
	SDL_Color getColor();

	void rainbow();
	void setPosition(int x, int y);
	float distanceTo(float x, float y);
};

