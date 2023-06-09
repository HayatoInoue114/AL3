#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include "MT.h"
#include <assert.h>
#include "EnemyBullet.h"

class Enemy;

class BaseEnemyState {
public:
	virtual void Update(Enemy* pEnemy) = 0;
};

// 近づく
class EnemyStateApproach : public BaseEnemyState {
	void Update(Enemy* pEnemy) override;
};

// 逃げてく
class EnemyStateLeave : public BaseEnemyState {
	void Update(Enemy* pEnemy) override;
};



/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	Enemy();
	~Enemy();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();


	enum class Phase {
		Approach,	//接近する
		Leave,		//離脱する
	};

	void Approach();
	void Leave();
	void ChangeState(BaseEnemyState* newState);

	void ChangePosition(Vector3 vector);
	Vector3 GetTranslation() { return worldTransform_.translation_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//フェーズ
	Phase phase_ = Phase::Approach;

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	//メンバ関数ポインタ
	static void (Enemy::*situation[])();
	
	BaseEnemyState* state_;

	//弾を発射する間隔
	int bulletFireCount;

	// 弾
	std::list<EnemyBullet*> bullets_;

	/*EnemyStateApproach* approach_;
	EnemyStateLeave* leave_;*/
};
