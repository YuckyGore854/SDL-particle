#include "dot.h"


dot::dot() {
	xPos = rand() % SCREEN_W;
	yPos = rand() % SCREEN_H;
	hue = rand() % 361;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	xVel = .5 + (rand() % 10) / 10;
	yVel = .5 + (rand() % 10) / 10;
	(rand() % 2) ? xVel *= -1 : xVel *= 1;
	(rand() % 2) ? yVel *= 1 : yVel *= -1;

}
float dot::getX() {
	return xPos;
}
float dot::getY() {
	return yPos;
}
void dot::setPosition(int x, int y) {
	xPos = x;
	yPos = y;
}
void dot::move() {
	xPos += xVel;
	yPos += yVel;
	dotRect.x = xPos;
	dotRect.y = yPos;
	dotRect.w = 5;
	dotRect.h = 5;
	if (xPos >= SCREEN_W || 0 >= xPos)
		xVel *= -1;
	if (yPos >= SCREEN_H || 0 >= yPos)
		yVel *= -1;
}
void dot::setColor(SDL_Color newColor) {
	color = newColor;
}
SDL_Color dot::getColor() {
	return color;
}
void dot::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawRect(renderer, &dotRect);
	SDL_RenderFillRect(renderer, &dotRect);
	//al_draw_filled_circle(xPos, yPos, 5, color);
}

void dot::rainbow() {
	if (hue < 360) {
		hue++;
	}
	else {
		hue = 0;
	}
	hsv dotRainbow;
	dotRainbow.h = hue;
	dotRainbow.s = 1;
	dotRainbow.v = 1;
	rgb dotRainbowrgb;
	dotRainbowrgb = (hsv2rgb(dotRainbow));
	color.r = dotRainbowrgb.r*255;
	color.g = dotRainbowrgb.g*255;
	color.b = dotRainbowrgb.b*255;
}
float dot::distanceTo(float x, float y) {
	return sqrt((xPos - x) * (xPos - x) + (yPos - y) * (yPos - y));
}