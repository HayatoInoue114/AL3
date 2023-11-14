#include "Enemy.h"
#include "ImGuiManager.h"
#include "Player.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	worldTransform_.translation_ = {0, 0, 50};

	viewProjection_.Initialize();

	trackingPower_ = 0.3f;

	chaseSpeed_ = 0.1f;

	velocityXZ_ = 0.0f;

	velocity_ = {0.0f, 0.0f, -0.1f};

	isChase_ = false;

	situation_ = 0;

	fovRadius_ = 20;

	fovAngle_ = 45;
}

void Enemy::Update() {
	if (CheckCollisionWithPlayer()) {
		situation_ = CHASE;
	} else {
		situation_ = MOVE;
	}

	switch (situation_) {
	case MOVE:
		// velocity_ = {0.0f, 0.0f, -0.01f};

		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		// Y軸周り角度(0y)
		worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);

		velocityXZ_ = std::sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
		// X軸周り角度(0x)
		worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZ_);
		break;

	case STOP:

		break;

	case CHASE:
		// 座標を移動させる（1フレーム分の移動量を足しこむ)
		Vector3 toPlayer =
		    Subtract(player_->GetWorldTransform().translation_, worldTransform_.translation_);

		// ベクトルを正規化する
		if (Length(toPlayer) > 0.0001) {
			toPlayer = Normalize(toPlayer);
			velocity_ = Normalize(velocity_);
			velocity_ = Multiply(chaseSpeed_, Slerp(velocity_, toPlayer, trackingPower_));
		}

		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		// Y軸周り角度(0y)
		worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);

		velocityXZ_ = std::sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
		// X軸周り角度(0x)
		worldTransform_.rotation_.x = std::atan2(-velocity_.y, velocityXZ_);
		break;

	default:
		break;
	}

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

bool Enemy::CheckCollisionWithPlayer() {
	Vector3 toPlayer =
	    Subtract(player_->GetWorldTransform().translation_, worldTransform_.translation_);
	float distance = Length(toPlayer);

	// プレーヤーが有効範囲内にいるかつ視野角度内にいるかを判定
	if (distance <= fovRadius_ && IsPlayerInFOV(toPlayer)) {
		// 当たり判定が成立
		return true;
	}

	// 当たり判定が成立しない
	return false;
}

bool Enemy::IsPlayerInFOV(const Vector3& toPlayer) {
	// プレーヤーの方向ベクトルと敵の前方ベクトルを比較して、視野角度内にいるかを判定
	float angle = AngleBetweenVectors(ForwardVector(), Normalize(toPlayer));
	return angle <= fovAngle_ / 2.0f;
}