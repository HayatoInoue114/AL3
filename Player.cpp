﻿#include "Player.h"
#include <cassert>
#include "MT.h"
#include "ImGuiManager.h"

//NULLポインタチェック
Player::Player() {}

Player::~Player() { 
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

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
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	

	//座標移動（ベクトルの加算）
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 移動限界座標
	const float kMoveLimitX = 17;
	const float kMoveLimitY = 17;

	// 範囲を超えない処理
	worldTransform_.translation_.x =
	    std::clamp(worldTransform_.translation_.x, -kMoveLimitX, kMoveLimitX);

	worldTransform_.translation_.y =
	    std::clamp(worldTransform_.translation_.y, -kMoveLimitY, kMoveLimitY);

	//行列を定数バッファに転送
	worldTransform_.UpdateMatrix();

	//キャラクターの座標を画面表示する処理
	float num[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::Begin("Player    DebugCamera : LALT");
	ImGui::SliderFloat3("Player", num, -30, 30);
	ImGui::Text("Rotate : A or D");
	ImGui::Text("Bullet : SPACE");
	ImGui::End();

	worldTransform_.translation_.x = num[0];
	worldTransform_.translation_.y = num[1];
	worldTransform_.translation_.z = num[2];

	Rotate();

	//キャラクター攻撃処理
	Attack();

	//弾更新
	for (PlayerBullet* bullet : bullets_) {
	bullet->Update();
	}
}

void Player::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//弾描画
	for (PlayerBullet* bullet : bullets_) {
	bullet->Draw(viewProjection);
	}
	
}

//void Player::SetWorldTransform_(WorldTransform worldTransform) { 
//	worldTransform_ = {worldTransform}; 
//}

void Player::Attack() { 
	if (input_->PushKey(DIK_SPACE)) {
		// 弾があれば開放する
	

		//弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		//弾を登録する
		bullets_.push_back(newBullet);
	}
}



void Player::Rotate() {
	// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y += kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
}
