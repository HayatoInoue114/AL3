#pragma once
#include "EnemyBullet.h"
#include "MT.h"
#include "Model.h"
#include "TimedCall.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include <assert.h>
#include "EnemyState.h"

class Enemy;
class Player;
class BaseEnemyState;




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
	void Initialize(Model* model, Vector3 position);

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

	/*/// <summary>
	/// 接近フェーズ初期化
	/// </summary>
	void InitializeApproachPhase();*/

	/*/// <summary>
	/// 弾を発射し、タイマーをリセットするコールバック関数
	/// </summary>
	void FireAndResetCallback();*/

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	void SetPlayer(Player* player) { player_ = player; }

	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する
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

	// フェーズ
	Phase phase_ = Phase::Approach;

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	// メンバ関数ポインタ
	static void (Enemy::*situation[])();

	BaseEnemyState* state_;

	//// 弾を発射する間隔
	//static const uint32_t kFireInterval = 30;

	// 発射タイマー
	int32_t fireCount = 0;

	// 弾
	std::list<EnemyBullet*> bullets_;

	//// 次元発動のリスト
	//std::list<TimedCall*> timedCalls_;

	Player* player_ = nullptr;

	Vector3 velocity_;

	Vector3 deltaVector_;

	/*EnemyStateApproach* approach_;
	EnemyStateLeave* leave_;*/
};
