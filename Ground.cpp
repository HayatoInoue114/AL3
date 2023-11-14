#include "Ground.h"

void Ground::Initialize(Model* model) { 
	model_ = model;

	worldTransform_.Initialize();
	
	worldTransform_.scale_ = {1, 1, 1};
	worldTransform_.translation_ = {0, -2.0f, 0.0f};
	worldTransform_.UpdateMatrix();
}

void Ground::Update() {
	
}

void Ground::Draw(ViewProjection& viewProjection, uint32_t textureHandle) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle);
}