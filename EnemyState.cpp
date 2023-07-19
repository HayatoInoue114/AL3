#include "EnemyState.h"

void EnemyStateApproach::FireAndResetCallback() {
	enemy_->Fire();

	timedCalls_.push_back(
	    new TimedCall(std::bind(&EnemyStateApproach::FireAndResetCallback, this), kFireInterval));

	////発射タイマーをセットする
	// std::function<void(void)> callback = std::bind(&Enemy::FireAndResetCallback, this);

	// TimedCall* timedCall = new TimedCall(callback, kFireInterval);

	// timedCalls_.push_back(timedCall);
}


EnemyStateApproach::~EnemyStateApproach() {
	for (TimedCall* timedCall : timedCalls_) {
		delete timedCall;
	}
}

void EnemyStateApproach::Initialize(Enemy* enemy) {
	enemy_ = enemy;
	FireAndResetCallback();
}

void EnemyStateApproach::Update(Enemy* pEnemy) {
	enemy_ = pEnemy;
	Vector3 position = enemy_->GetWorldPosition();

	Vector3 move = {0.01f, 0, -0.015f};

	// 終了したタイマーを削除
	timedCalls_.remove_if([](TimedCall* timedCall) {
		if (timedCall->IsFinished()) {
			delete timedCall;
			return true;
		}
		return false;
	});

	// 範囲for文でリストの全要素について回す
	for (TimedCall* timedCall : timedCalls_) {
		timedCall->Update();
	}

	enemy_->ChangePosition(move);
	// 既定の位置に到達したら離脱
	if (position.z < -20.0f) {
		enemy_->ChangeState(new EnemyStateLeave());
	}
}

void EnemyStateLeave::Initialize(Enemy* enemy) { enemy_ = enemy; }

void EnemyStateLeave::Update(Enemy* pEnemy) {
	enemy_ = pEnemy;
	Vector3 position = enemy_->GetWorldPosition();

	Vector3 move = {0.1f, 0.1f, 0};
	// 移動

	enemy_->ChangePosition(move);
}
