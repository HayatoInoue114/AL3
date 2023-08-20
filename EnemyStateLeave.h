#pragma once
#include "IEnemyState.h"

// “¦‚°‚Ä‚­

class EnemyStateLeave : public IEnemyState {
public:
	void Update(Enemy* pEnemy) override;
};