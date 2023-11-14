#include "Enemy.h"
#include "Player.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	viewProjection_.Initialize();

	t_ = 0;

	speed_ = 0.8f;
}

void Enemy::Update() {
	// 座標を移動させる（1フレーム分の移動量を足しこむ)
	Vector3 toPlayer = Subtract(player_->GetWorldTransform().translation_, worldTransform_.translation_);

	// ベクトルを正規化する
	toPlayer = Normalize(toPlayer);
	

	velocity_ = Multiply(speed_, Slerp(velocity_, toPlayer, t_));

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	// Y軸周り角度(0y)
	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);

	velocityXZ_ = std::sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	// X軸周り角度(0x)
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZ_);

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}