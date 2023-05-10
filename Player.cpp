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

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	worldTransform_.Initialize();
}

void Player::Update() { 
	/*worldTransform_.TransferMatrix();*/
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	//キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_UP)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.x += kCharacterSpeed;
	}

	//座標移動（ベクトルの加算）
	Add(worldTransform_.translation_, move);
}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//void Player::SetWorldTransform_(WorldTransform worldTransform) { 
//	worldTransform_ = {worldTransform}; 
//}