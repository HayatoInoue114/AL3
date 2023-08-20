#include "EnemyStateLeave.h"

//void EnemyStateLeave::Initialize(Enemy* enemy) { enemy_ = enemy; }

void EnemyStateLeave::Update(Enemy* pEnemy) {
	Vector3 position = pEnemy->GetWorldPosition();

	Vector3 move = { 0.1f, 0.1f, 0 };
	// 移動

	pEnemy->ChangePosition(move);
}