#include "Enemy.h"
#include "Player.h"
#include "ImGuiManager.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	worldTransform_.translation_ = {30, 0, 50};

	viewProjection_.Initialize();

	t_ = 0.2f;

	speed_ = 0.1f;

	velocityXZ_ = 0.0f;

	velocity_ = {1.0f, 1.0f, kBulletSpeed};
	
	isChase_ = false;
}

void Enemy::Update() {
	// 座標を移動させる（1フレーム分の移動量を足しこむ)
	Vector3 toPlayer = Subtract(player_->GetWorldTransform().translation_, worldTransform_.translation_);

	// ベクトルを正規化する
	if (Length(toPlayer) > 0.0001) {
		toPlayer = Normalize(toPlayer);
		velocity_ = Normalize(velocity_);
		velocity_ = Multiply(speed_, Slerp(velocity_, toPlayer, t_));
	}

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	// Y軸周り角度(0y)
	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);

	velocityXZ_ = std::sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	// X軸周り角度(0x)
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZ_);

	worldTransform_.UpdateMatrix();

	float num[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::Begin("Enemy");
	ImGui::SliderFloat3("Enemy", num, -30, 30);
	ImGui::End();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}