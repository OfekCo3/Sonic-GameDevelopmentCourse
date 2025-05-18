#pragma once
#include "Game.h"

constexpr Bagel Params{
	.DynamicResize = true
};


    BAGEL_STORAGE(SonicGame::Position, PackedStorage)
    BAGEL_STORAGE(SonicGame::Velocity, PackedStorage)
    BAGEL_STORAGE(SonicGame::MovementAbility, TaggedStorage)
    BAGEL_STORAGE(SonicGame::Animation, SparseStorage)
    BAGEL_STORAGE(SonicGame::Health, SparseStorage)
    BAGEL_STORAGE(SonicGame::PlayerTag, TaggedStorage)
    BAGEL_STORAGE(SonicGame::EnemyTag, TaggedStorage)
    BAGEL_STORAGE(SonicGame::CollectorTag, TaggedStorage)
    BAGEL_STORAGE(SonicGame::RingCount, SparseStorage)
    BAGEL_STORAGE(SonicGame::CollectableTag, TaggedStorage)
    BAGEL_STORAGE(SonicGame::CollisionInfo, PackedStorage)
    BAGEL_STORAGE(SonicGame::ObstacleTag, TaggedStorage)
    BAGEL_STORAGE(SonicGame::DamageTag, SparseStorage)
    BAGEL_STORAGE(SonicGame::TemporaryPowerup, SparseStorage)
    BAGEL_STORAGE(SonicGame::GravityTag, TaggedStorage)
    BAGEL_STORAGE(SonicGame::Intent, SparseStorage)
    BAGEL_STORAGE(SonicGame::JumpingTag, TaggedStorage)
    BAGEL_STORAGE(SonicGame::RollingTag, TaggedStorage)
    BAGEL_STORAGE(SonicGame::PowerupTypeComponent, SparseStorage)
    BAGEL_STORAGE(SonicGame::Input, SparseStorage)
