#include "Enemy.h"

void (Enemy::*Enemy::situation[])() = {
	&Enemy::Approach,
	&Enemy::Leave
};

Enemy::Enemy() { 
	state_ = new EnemyStateApproach();
}

Enemy::~Enemy() { 
}

void Enemy::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("title_jiki.png");

	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = {0,5.0f,5.0f};
}

void Enemy::Approach() {
	
	
}

void Enemy::Leave() {
	//move = {kCharacterSpeed, kCharacterSpeed, 0};
	////// 移動
	//worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	
}

void Enemy::ChangeState(BaseEnemyState* newState) {
	delete state_;
	state_ = newState;
}

void Enemy::Update() { 
	state_->Update(this);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);


	worldTransform_.UpdateMatrix(); 
}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	// 弾描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::ChangePosition(Vector3 vector) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, vector);
}

void Enemy::Fire() {
	bulletFireCount++;
	if (bulletFireCount % 30 == 0) {
		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾を生成し、初期化
		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}
}



void EnemyStateApproach::Update(Enemy* pEnemy) {
	Vector3 position = pEnemy->GetTranslation();

	Vector3 move = {0, 0, -0.25f};
	// 移動
	

	pEnemy->ChangePosition(move);
	// 既定の位置に到達したら離脱
	if (position.z < -10.0f) {
		pEnemy->ChangeState(new EnemyStateLeave());
	}

}

void EnemyStateLeave::Update(Enemy* pEnemy) {
	Vector3 position = pEnemy->GetTranslation();

	Vector3 move = {0.25f, 0.25f, 0};
	// 移動


	pEnemy->ChangePosition(move);
}
