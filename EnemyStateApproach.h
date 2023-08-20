#pragma once
#include "IEnemyState.h"

// ‹ß‚Ã‚­
class EnemyStateApproach : public IEnemyState {
public:
	void Update(Enemy* pEnemy) override;
};