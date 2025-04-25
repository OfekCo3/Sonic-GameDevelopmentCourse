#include <iostream>
#include <cassert>
#include "bagel.h"
using namespace std;
using namespace bagel;


void test1() {
	ent_type e0 = World::createEntity();
	assert(e0.id == 0 && "First id is not 0");

	ent_type e1 = World::createEntity();
	assert(e1.id == 1 && "Second id is not 1");

	World::destroyEntity(e0);
	e0 = World::createEntity();
	assert(e0.id == 0 && "Id 0 not recycled after destroy & create");

	cout << "Test 1 passed\n";
}

void testDynamicBag() {
    struct Sprite {
        int width;
        int height;
        const char* name;
    };

    DynamicBag<Sprite, 2> bag;

    // Check adding elements
    bag.push({64, 64, "Sonic"});
    bag.push({128, 128, "Enemy"});

    assert(bag.size() == 2);

    // Check reading by index
    assert(bag[0].width == 64 && bag[0].height == 64);
    assert(std::string(bag[0].name) == "Sonic");

    assert(bag[1].width == 128 && bag[1].height == 128);
    assert(std::string(bag[1].name) == "Enemy");

    // Check automatic resize after exceeding initial capacity
    bag.push({32, 32, "Ring"});
    assert(bag.size() == 3);
    assert(bag.capacity() >= 3);

    cout << "testDynamicBag passed\n";
}

void testPackedStorage() {
    struct Position {
        int x;
        int y;
    };

    ent_type e = World::createEntity();

    // Check adding a Position component
    PackedStorage<Position>::add(e, {100, 200});
    assert(PackedStorage<Position>::size() == 1);

    // Check retrieving the Position component
    Position& pos = PackedStorage<Position>::get(e);
    assert(pos.x == 100 && pos.y == 200);

    // Check deleting the component updates size
    PackedStorage<Position>::del(e);
    assert(PackedStorage<Position>::size() == 0);

    cout << "testPackedStorage passed\n";
}

void run_tests()
{
    testDynamicBag();
    testPackedStorage();
}
