#include "Ground.h"

void Ground::Initialize(Model* model) { 
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {10, 10, 1};
}

void Ground::Update() {

}

void Ground::Draw(ViewProjection& viewProjection, uint32_t textureHandle) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle);
}