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

	//�J�����I�u�W�F�N�g�̃��[���h�s�񂩂�r���[�s����v�Z����
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);


	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();

	float translation[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	float rotation[3] = {
	    worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z};
	//�J�����̍��W����ʕ\�����鏈��
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", translation, -30.0f, 100.0f);
	ImGui::SliderFloat3("rotation", rotation, -30, 120);
	ImGui::End();
}
