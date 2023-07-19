#include "RailCamera.h"

void RailCamera::Initialize(WorldTransform& worldTransform) { 
	worldTransform_ = worldTransform;
	viewProjection_.Initialize();
}

void RailCamera::Update() { 
	Vector3 move = {0, 0, 100.0f};
	worldTransform_.translation_ = Add(worldTransform_.translation_,move);

	Vector3 rotate = {0, 0, 100.0f};
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, rotate);

	//カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);


	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();

	float translation[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	float rotation[3] = {
	    worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z};
	//カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", translation, -30.0f, 100.0f);
	ImGui::SliderFloat3("rotation", rotation, -30, 120);
	ImGui::End();
}
