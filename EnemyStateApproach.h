#pragma once
#include "IEnemyState.h"

// �߂Â�
class EnemyStateApproach : public IEnemyState {
public:
	void Update(Enemy* pEnemy) override;
};