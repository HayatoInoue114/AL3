#include "Enemy.h"

void Enemy::Initialize(Model* model, const Vector3& position) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("title_jiki.png");

	worldTransform_.Initialize();
	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = {position};
}

void Enemy::Update() { 
	worldTransform_.UpdateMatrix(); 
}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}