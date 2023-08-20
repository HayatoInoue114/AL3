#pragma once
#include "IEnemyState.h"

// 逃げてく

class EnemyStateLeave : public IEnemyState {
public:
	void Update(Enemy* pEnemy) override;
};