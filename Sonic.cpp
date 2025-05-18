#include "Sonic.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <box2d/box2d.h>
using namespace std;

Sonic::Sonic()
{
    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        cout << SDL_GetError() << endl;
        return;
    }

    // Create the window and renderer
    if (!SDL_CreateWindowAndRenderer(
            "Sonic Game", 800, 600, 0, &win, &ren)) {
        cout << SDL_GetError() << endl;
        return;
    }

    // Load Sonic texture
    SDL_Surface* walkSurf = IMG_Load("res/245841-removebg-preview.png");
    if (walkSurf == nullptr) {
        cout << SDL_GetError() << endl;
        return;
    }
    // Load walking sprite sheet
    walkingTex = SDL_CreateTextureFromSurface(ren, walkSurf);
    if (walkingTex == nullptr) {
        cout << SDL_GetError() << endl;
        return;
    }
    SDL_DestroySurface(walkSurf);

    // Create the physics world with normal gravity
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, 9.8f };
    world = b2CreateWorld(&worldDef);

    // Create Sonic's body
    b2BodyDef sonicBodyDef = b2DefaultBodyDef();
    sonicBodyDef.type = b2_dynamicBody;
    sonicBodyDef.position = { 100 / BOX_SCALE, 500 / BOX_SCALE };
    ballBody = b2CreateBody(world, &sonicBodyDef);

    // Define Sonic's shape
    b2ShapeDef sonicShapeDef = b2DefaultShapeDef();
    sonicShapeDef.density = 1.0f;
    sonicShapeDef.material.friction = 0.5f;
    sonicShapeDef.material.restitution = 0.0f;
    b2Circle sonicCircle = { 0, 0, SONIC_TEX.w * TEX_SCALE / BOX_SCALE };
    b2CreateCircleShape(ballBody, &sonicShapeDef, &sonicCircle);

    // Create the ground (floor)
    b2BodyDef floorBodyDef = b2DefaultBodyDef();
    floorBodyDef.type = b2_staticBody;
    floorBodyDef.position = { 800 / 2 / BOX_SCALE, 600 / BOX_SCALE };
    b2BodyId floorBody = b2CreateBody(world, &floorBodyDef);

    b2Polygon groundBox = b2MakeBox(800 / 2 / BOX_SCALE, 1.0f);
    b2CreatePolygonShape(floorBody, &sonicShapeDef, &groundBox);
}

Sonic::~Sonic()
{
    if (walkingTex != nullptr)
        SDL_DestroyTexture(walkingTex);
    if (ren != nullptr)
        SDL_DestroyRenderer(ren);
    if (win != nullptr)
        SDL_DestroyWindow(win);

    SDL_Quit();
}

void Sonic::run()
{
    SDL_SetRenderDrawColor(ren, 135, 206, 235, 255);
    SDL_RenderClear(ren);
    SDL_FRect sonicRect{ 0, 0, SONIC_TEX.w * TEX_SCALE, SONIC_TEX.h * TEX_SCALE };

    constexpr float STEP_TIME = 1.f / FPS;
    constexpr float RAD_TO_DEG = 57.2958f;

    for (int frame = 0; frame < 1000; ++frame) {
        // Physics update
        b2World_Step(world, STEP_TIME, 4);

        // Sonic moves right by setting x velocity
        b2Vec2 sonicVelocity = b2Body_GetLinearVelocity(ballBody);
        sonicVelocity.x = 2.0f;
        b2Body_SetLinearVelocity(ballBody, sonicVelocity);

        // Get Sonic's new position
        b2Vec2 sonicPosition = b2Body_GetPosition(ballBody);
        sonicRect.x = sonicPosition.x * BOX_SCALE;
        sonicRect.y = sonicPosition.y * BOX_SCALE - (SONIC_TEX.h * TEX_SCALE / 2);

//        // Get Sonic's rotation
//        b2Rot sonicRotation = b2Body_GetRotation(ballBody);
//        float sonicAngle = RAD_TO_DEG * b2Rot_GetAngle(sonicRotation);

        // Rendering
        SDL_RenderClear(ren);

        // Animate Sonic walking
        frameCounter++;
        if (frameCounter >= 5) { // slows animation speed
            currentFrame = (currentFrame + 1) % TOTAL_FRAMES;
            frameCounter = 0;
        }

        SDL_FRect srcFrameF = {
                SONIC_TEX.x + currentFrame * SONIC_TEX.w,
                SONIC_TEX.y,
                SONIC_TEX.w,
                SONIC_TEX.h
        };

        SDL_FRect destRect = {
                sonicRect.x,
                sonicRect.y,
                SONIC_TEX.w * TEX_SCALE,
                SONIC_TEX.h * TEX_SCALE
        };

        SDL_RenderTexture(ren, walkingTex, &srcFrameF, &destRect);

//        SDL_RenderTextureRotated(
//                ren, tex, &SONIC_TEX, &sonicRect, sonicAngle,
//                nullptr, SDL_FLIP_NONE);

        SDL_RenderPresent(ren);

        SDL_Delay(5);
    }
}
