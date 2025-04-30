#include "Sonic.h"
#include "Game.h"

/// test sonic movement
//int main()
//{
//	Sonic p;
//	p.run();
//	return 0;
//}

int main() {
    using namespace SonicGame;

    CreateSonicEntity(0,0);
    CreateEnemyEntity(1,1);
    CreateRingEntity(2,2);

    MovementSystem();
    CollisionSystem();
    AnimationSystem();
    ItemCollectionSystem();
    TemporaryEffectsSystem();
    InputSystem();
    RenderSystem();
    ActionSystem();
    IntentSystem();

    return 0;
}
