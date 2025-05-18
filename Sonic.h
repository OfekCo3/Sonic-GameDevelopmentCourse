#pragma once
#include <SDL3/SDL.h>
#include <box2d/box2d.h>

class Sonic
{
public:
	Sonic();
	~Sonic();

	void run();
private:
	static constexpr int FPS = 60;
	static constexpr float BOX_SCALE = 10;
	static constexpr float TEX_SCALE = 2.0f;
	//static constexpr SDL_FRect SONIC_TEX = {46, 144, 48, 48}; //superrun
    static constexpr SDL_FRect SONIC_TEX = {190, 97, 48, 48}; //run
    static constexpr int TOTAL_FRAMES = 8;

    SDL_Texture* walkingTex;
    int currentFrame = 0;
    int frameCounter = 0;

	SDL_Renderer* ren;
	SDL_Window* win;

	b2WorldId world;
	b2BodyId ballBody;
};

