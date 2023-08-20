#include "EnemyStateApproach.h"

void EnemyStateApproach::Update(Enemy* pEnemy) {
	Vector3 position = pEnemy->GetWorldPosition();

	Vector3 move = { 0.01f, 0, -0.015f };

	pEnemy->ChangePosition(move);
	// 既定の位置に到達したら離脱
	/*if (position.z < -10.0f) {
		enemy_->ChangeState(new EnemyStateLeave());
	}*/
}