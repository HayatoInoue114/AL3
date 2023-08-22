#include "EnemyStateApproach.h"
#include "Enemy.h"
#include "EnemyStateLeave.h"
#include "ImGuiManager.h"


void EnemyStateApproach::Update(Enemy* pEnemy) {
	Vector3 move = { 0.01f, 0, -0.1f };

	pEnemy->ChangePosition(move);

	//Vector3 position = pEnemy->GetWorldPosition();
	// 既定の位置に到達したら離脱
	if (pEnemy->IsChangeStatePosition()) {
		pEnemy->ChangeState(new EnemyStateLeave());
	}
}