#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	viewProjection_.Initialize();
}

void Enemy::Update() {
	worldTransform_.translation_.z += 0.01f;

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}