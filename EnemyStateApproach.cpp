#include "EnemyStateApproach.h"

//void EnemyStateApproach::Initialize(Enemy* enemy) {
//	enemy_ = enemy;
//}

void EnemyStateApproach::Update(Enemy* pEnemy) {
	Vector3 position = pEnemy->GetWorldPosition();

	Vector3 move = { 0.01f, 0, -0.015f };

	pEnemy->ChangePosition(move);
	// ����̈ʒu�ɓ��B�����痣�E
	/*if (position.z < -10.0f) {
		enemy_->ChangeState(new EnemyStateLeave());
	}*/
}