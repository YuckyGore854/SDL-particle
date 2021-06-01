/*
#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_color.h>
*/
#include<SDL.h>
#include<vector>
#include <iostream>
#include "dot.h"
#include "rgbhsv.h"
using namespace std;
float distance(float x, float y, float x1, float y1);
//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 500;
const int SCREEN_H = 500;
int range = 0;

void drawGradient();
//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

SDL_Window* window = SDL_CreateWindow("Particles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

int xMousePos, yMousePos, R;
int mousePos[2] = { 0,0 };
bool mouseButtons[3] = { false, false, false };
bool input();
int main(int argc, char* argv[]) {
	vector<dot*> space;
	vector<dot*>::iterator iter;
	vector<dot*> lines;
	vector<dot*>::iterator iter2;
	for (int i = 0; i <= 10; i++) {
		dot* newDot = new dot();
		space.push_back(newDot);
	}

	//set up SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//al_init();
	//al_install_keyboard();
	//al_init_primitives_addon();
	//al_install_mouse();

	//drawGradient();

	//set up game screen, event queue, and timer
	
	int fps = 60;//these variables are for manually capping the framerate
	int frameDelay = 1000 / fps;//this is the frameDelay variable, or approximately how long each frame should take

	Uint32 frameStart;//this variable holds the amount of time at the beginning of a frame
	int frameTime;//this variable calculates the actual time of the current frame

	//ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
	//ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	//ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	//al_start_timer(timer);

	//game variables
	bool key[4] = { false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop


	//tell event queue what to look for
	/*al_set_target_bitmap(al_get_backbuffer(display));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	*/

	int lastX = 0;
	int lastY = 0;
	int delayTimer = 0;
	bool spawn = false;
	bool destroy = false;
	int counter = 0;
	while (!doexit)//game loop!
	{
		//ALLEGRO_EVENT ev;
		//al_wait_for_event(event_queue, &ev);
		frameStart = SDL_GetTicks();

		//timer (physics) section////////////////////////////////////////
		
		input();
		if (mouseButtons[0]) {
			spawn = true;
		}
		else {
			spawn = false;
		}
		if (mouseButtons[2]) {
			destroy = true;
		}
		else {
			destroy = false;
		}

		if (spawn) {
			dot* newDot = new dot();
			(newDot)->setPosition(mousePos[0], mousePos[1]);
			space.push_back(newDot);
		}
		if (destroy && space.size() > 1) {
			space.erase(space.end()- 1);
		}
		
		
		//render section//////////////////////////////////////////////////
			
			delayTimer = 0;
			//al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing (without this things smear)
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			//inCircle
			//cout << "Range: " << range << ", X: " << xMousePos << " , Y: " << yMousePos << ", Amount Of Particles: " << space.size() << endl;
			
			//al_draw_filled_circle(xMousePos, yMousePos, range, al_map_rgba(255, 255, 255, 1));
			for (iter = space.begin(); iter != space.end(); iter++) {
				(*iter)->move();
				(*iter)->draw(renderer);
				//if ((*iter)->collision(xMousePos, yMousePos))
				(*iter)->rainbow();
				//else
				//(*iter)->setColor(al_map_rgb(255, 255, 255));
				for (int j = 0; j < space.size(); j++) {
					
					if ((*iter)->distanceTo(space.at(j)->getX(), space.at(j)->getY()) < 100/* && (*iter)->collision(xMousePos, yMousePos)*/) {
						SDL_Color newColor = (*iter)->getColor();
						space.at(j)->setColor((*iter)->getColor());
						SDL_SetRenderDrawColor(renderer, newColor.r, newColor.g, newColor.b, newColor.a);
						SDL_RenderDrawLine(renderer,(*iter)->getX(), (*iter)->getY(), space.at(j)->getX(), space.at(j)->getY());
					}
				}
			}
			counter = 0;
			lines.clear();
			SDL_RenderPresent(renderer);
			//al_flip_display(); //flip everything from memory to gamescreen
		//end render
			frameTime = SDL_GetTicks() - frameStart;//calculates how long a frame has been rendered for

			if (frameDelay > frameTime)//if the wanted amount of time between frames is bigger than the current amount of time it took to render the last frame
				SDL_Delay(frameDelay - frameTime);//delay the game until 16.66... miliseconds have passed

	}//end game loop

	//clean up memory
/*	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
*/
	//SDL_DestroyWindow(window);
	//SDL_DestroyRenderer(renderer);
	
	return 0;
}



float distance(float x, float y, float x1, float y1) {
	return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
}

void drawGradient() {
	//ALLEGRO_DISPLAY* DISPLAY = al_create_display(361, 10);
	int hue1 = 0;
	for (int i = 0; i < 360; i++) {
		hue1++;
		for (int j = 0; j < 10; j++) {
			hsv color;
			color.h = hue1;
			color.s = 1;
			color.v = 1;

			rgb rgbColor = (hsv2rgb(color));
			SDL_SetRenderDrawColor(renderer, rgbColor.r*255, rgbColor.g, rgbColor.b, 255);
			SDL_RenderDrawPoint(renderer, i, j);
			//al_draw_pixel(i, j, al_color_hsv(hue1, 1, 1));
			//al_flip_display();
		}
	}
}

bool input() {
	//Event handler
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {
		//User requests quit         
		if (event.type == SDL_QUIT) {//if the button says quit, set quit to true and end the gameloop
			return true;
		}

		//if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) { // if there is mouse movement
			SDL_GetMouseState(&mousePos[0], &mousePos[1]); // update the position of the mouse's x and y

			if (event.button.button == SDL_BUTTON_LEFT) // if you click the left button
				mouseButtons[0] = true; // updates mouse button variable
			else mouseButtons[0] = false;

			if (event.button.button == SDL_BUTTON_RIGHT)
				mouseButtons[2] = true;
			else mouseButtons[2] = false;

		//}
	}
	return false;
}


/*
for (iter = space.begin(); iter != space.end(); iter++) {
(*iter)->move();
(*iter)->draw();
if((*iter)->collision(xMousePos, yMousePos)) {

(*iter)->rainbow();

lines.push_back(*iter);
}
else {
(*iter)->setColor(al_map_rgb(255, 255, 255));
}
}
for (iter2 = lines.begin(); iter2 != lines.end(); iter2++) {
int newX = (*iter2)->getX();
int newY = (*iter2)->getY();
//cout << "OLD X: " << oldX << ", OLD Y: " << oldY << "\nNEW X: " << newX << ", NEW Y: " << newY << endl << endl;
ALLEGRO_COLOR newColor = (*iter2)->getColor();
al_draw_line(newX, newY, xMousePos, yMousePos, newColor, 1);
counter++;
}

*/
