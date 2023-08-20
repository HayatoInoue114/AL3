#pragma once
#include "IEnemyState.h"

// 近づく
class EnemyStateApproach : public IEnemyState {
public:
	void Update(Enemy* pEnemy) override;
};