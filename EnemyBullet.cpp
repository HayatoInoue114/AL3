#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() { velocity_ = {}; }

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("ball.png");

	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = {position};

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void EnemyBullet::Update() {
	// 座標を移動させる（1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	worldTransform_.UpdateMatrix();
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}


}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}