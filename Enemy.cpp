#include "Enemy.h"

void Enemy::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("title_jiki.png");

	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = {0,5.0f,5.0f};
}

void Enemy::Approach() {
	move = {0, 0, -kCharacterSpeed};
	// 移動
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	// 既定の位置に到達したら離脱
	if (worldTransform_.translation_.z < -10.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	move = {kCharacterSpeed, kCharacterSpeed, 0};
	// 移動
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
}

void Enemy::Update() { 

	

	switch (phase_) {
	case Phase::Approach:
		Approach();
		break;

		case Phase::Leave:
		Leave();
		break;
	default:
		break;
	}



	
	

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);


	worldTransform_.UpdateMatrix(); 
}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}