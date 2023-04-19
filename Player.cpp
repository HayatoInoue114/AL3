#include "Player.h"
#include <cassert>

//NULLポインタチェック
Player::Player() {}

Player::~Player() {}

void Player::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model); 

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
}

void Player::Update() { 
	/*worldTransform_.TransferMatrix();*/
}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//void Player::SetWorldTransform_(WorldTransform worldTransform) { 
//	worldTransform_ = {worldTransform}; 
//}