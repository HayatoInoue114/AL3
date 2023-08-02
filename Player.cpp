﻿#include "Player.h"
#include "ImGuiManager.h"
#include "MT.h"
#include <cassert>

// NULLポインタチェック
Player::Player() {}

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
	delete sprite2DReticle_;
}

void Player::Initialize(Model* model, uint32_t textureHandle, Vector3 playerPosition) {
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	reticleTextureHandle_ = TextureManager::Load("reticle.png");

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	// 3Dレティクルのワールドトランスフォーム初期化
	worldTransform3DReticle_.Initialize();

	// スプライト生成
	sprite2DReticle_ = Sprite::Create(
	    reticleTextureHandle_,
	    {640,360},
	    {0, 0, 0, 1}, {0.5f, 0.5f});

	worldTransform_.Initialize();
	worldTransform_.translation_ = {playerPosition};
}

void Player::Update(ViewProjection viewProjection) {
	/*worldTransform_.TransferMatrix();*/



	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	// 座標移動（ベクトルの加算）
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

	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();

	// キャラクターの座標を画面表示する処理
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


		// 自機から3Dレティクルへの距離
	const float kDistanceplayerTo3DReticle = 50.0f;

	// 自機のワールド行列の回転を反映
	offset = Multyply(offset, worldTransform_.matWorld_);
	// ベクトルの長さを整える
	offset = Multiply(kDistanceplayerTo3DReticle, Normalize(offset));
	// 3Dレティクルの座標を設定
	worldTransform3DReticle_.translation_ = Add(offset, worldTransform_.translation_);
	worldTransform3DReticle_.UpdateMatrix();
	worldTransform3DReticle_.TransferMatrix();

	Vector3 positionReticle = worldTransform3DReticle_.translation_;
	Matrix4x4 matViewport =
	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	Matrix4x4 matViewProjectionViewport =
	    Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport));
	positionReticle = Transform(positionReticle, matViewProjectionViewport);
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));

	// キャラクター攻撃処理
	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Player::Draw(ViewProjection viewProjection) {
	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

// void Player::SetWorldTransform_(WorldTransform worldTransform) {
//	worldTransform_ = {worldTransform};
// }

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {
		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 自機から照準オブジェクトへのベクトル
		velocity = Subtract(worldTransform3DReticle_.translation_, GetWorldPosition());
		velocity = Multiply(kBulletSpeed, Normalize(velocity));

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		// 弾を登録する
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

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos = {};
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos = {
	    worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1],
	    worldTransform_.matWorld_.m[3][2]};
	return worldPos;
}

Vector3 Player::GetReticleWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos = {};
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos = {
	    worldTransform3DReticle_.matWorld_.m[3][0], worldTransform3DReticle_.matWorld_.m[3][1],
	    worldTransform3DReticle_.matWorld_.m[3][2]};
	return worldPos;
}

void Player::OnCollision() {}

void Player::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}

void Player::DrawUI() { sprite2DReticle_->Draw(); }