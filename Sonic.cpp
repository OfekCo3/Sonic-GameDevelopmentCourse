//
// Created by User on 25/04/2025.
//

#include "Sonic.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

Sonic::Sonic(SDL_Renderer* renderer)
{
    SDL_Surface* surf = IMG_Load("res/sonic_sprite.png");
    if (!surf) {
        std::cerr << "Failed to load sprite: " << SDL_GetError() << std::endl;
        return;
    }

    tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_DestroySurface(surf);
    if (!tex) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0, 0 };
    world = b2CreateWorld(&worldDef);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = { 400 / BOX_SCALE, 300 / BOX_SCALE };
    body = b2CreateBody(world, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1;
    shapeDef.material.friction = 0.f;
    shapeDef.material.restitution = 1.5f;

    b2Circle circle = { 0, 0, 40 * TEX_SCALE / BOX_SCALE };
    b2CreateCircleShape(body, &shapeDef, &circle);

    b2Body_SetLinearVelocity(body, { 2, -3 });
    b2Body_SetAngularVelocity(body, 1.2f);

    loadAnimations();
}

Sonic::~Sonic()
{
    if (tex) SDL_DestroyTexture(tex);
    b2DestroyWorld(world);
}

void Sonic::loadAnimations()
{
    const int spriteWidth = 750;
    const int spriteHeight = 685;
    const int rowHeight = spriteHeight / 8;

    animations[AnimationState::Idle].frameDelay = 6;
    animations[AnimationState::Run].frameDelay = 4;
    animations[AnimationState::SuperRun].frameDelay = 3;
    animations[AnimationState::Roll].frameDelay = 3;
    animations[AnimationState::Jump].frameDelay = 5;

    std::vector<std::pair<AnimationState, std::pair<int, int>>> config = {
            { AnimationState::Idle, {0, 15} },
            { AnimationState::Run, {2, 14} },
            { AnimationState::SuperRun, {3, 14} },
            { AnimationState::Roll, {6, 10} },
            { AnimationState::Jump, {7, 10} }
    };

    for (auto& [state, row_frames] : config) {
        int row = row_frames.first;
        int count = row_frames.second;
        int frameWidth = spriteWidth / count;
        for (int i = 0; i < count; ++i) {
            SDL_FRect frame = {
                    static_cast<float>(i * frameWidth),
                    static_cast<float>(row * rowHeight),
                    static_cast<float>(frameWidth),
                    static_cast<float>(rowHeight)
            };
            animations[state].frames.push_back(frame);
        }
    }
}

void Sonic::update()
{
    if (++frameTimer >= animations[currentState].frameDelay) {
        frameTimer = 0;
        currentFrame = (currentFrame + 1) % animations[currentState].frames.size();
    }

    b2World_Step(world, 1.0f / 60.0f, 4);
}

void Sonic::render(SDL_Renderer* renderer)
{
    b2Vec2 pos = b2Body_GetPosition(body);
    b2Rot rot = b2Body_GetRotation(body);
    float angle = 57.2958f * b2Rot_GetAngle(rot);

    const SDL_FRect& src = animations[currentState].frames[currentFrame];
    SDL_FRect dest = {
            pos.x * BOX_SCALE,
            pos.y * BOX_SCALE,
            src.w * TEX_SCALE,
            src.h * TEX_SCALE
    };

    SDL_RenderTextureRotated(renderer, tex, &src, &dest, angle, nullptr, SDL_FLIP_NONE);
}
