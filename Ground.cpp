#include "Ground.h"

void Ground::Initialize(Model* model) { 
	model_ = model;

	worldTransform_.Initialize();
	
}

void Ground::Update() {
	worldTransform_.scale_ = {100, 100, 1};
	worldTransform_.translation_ = {0, 0, -10.0f};
}

void Ground::Draw(ViewProjection& viewProjection, uint32_t textureHandle) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle);
}