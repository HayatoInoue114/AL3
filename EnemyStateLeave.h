#pragma once
#include "IEnemyState.h"

// �����Ă�

class EnemyStateLeave : public IEnemyState {
public:
	void Update(Enemy* pEnemy) override;
};