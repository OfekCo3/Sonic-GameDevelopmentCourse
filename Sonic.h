#pragma once
#include <SDL3/SDL.h>
#include <box2d/box2d.h>
#include <vector>
#include <map>

enum class AnimationState { Idle, Run, SuperRun, Roll, Jump };

struct Animation {
    std::vector<SDL_FRect> frames;
    int frameDelay = 5;
};

class Sonic {
public:
    Sonic(SDL_Renderer* renderer);
    ~Sonic();

    void update();
    void render(SDL_Renderer* renderer);

private:
    void loadAnimations();

    SDL_Texture* tex;
    b2WorldId world;
    b2BodyId body;

    std::map<AnimationState, Animation> animations;
    AnimationState currentState = AnimationState::Run;

    int frameTimer = 0;
    int currentFrame = 0;

    static constexpr float BOX_SCALE = 10.0f;
    static constexpr float TEX_SCALE = 0.5f;
};
