#pragma once
#include "Enemy.h"
#include "TimedCall.h"

class Enemy;

class BaseEnemyState {
public:
	virtual void Initialize(Enemy* enemy) = 0;
	virtual void Update(Enemy* pEnemy) = 0;
};

// 近づく
class EnemyStateApproach : public BaseEnemyState {
	~EnemyStateApproach();
	void Initialize(Enemy* enemy) override;
	void Update(Enemy* pEnemy) override;
	/// <summary>
	/// 弾を発射し、タイマーをリセットするコールバック関数
	/// </summary>
	void FireAndResetCallback();

private:
	Enemy* enemy_;
	// 弾を発射する間隔
	static const uint32_t kFireInterval = 30;
	// 次元発動のリスト
	std::list<TimedCall*> timedCalls_;
};

// 逃げてく
class EnemyStateLeave : public BaseEnemyState {
	void Initialize(Enemy* enemy) override;
	void Update(Enemy* pEnemy) override;

private:
	Enemy* enemy_;
};