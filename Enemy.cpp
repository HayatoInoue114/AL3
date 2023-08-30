#include "Enemy.h"
#include "Player.h"

void (Enemy::* Enemy::situation[])() = { &Enemy::Approach, &Enemy::Leave };

Enemy::Enemy() {
	state_ = new EnemyStateApproach();
	/*player_ = new Player();*/
	deltaVector_ = {};
	velocity_ = {};
	isFire_ = true;
	changeStatePositionZ_ = {};
	isAlive_ = false;
	health_ = {};
	reviveCount_ = {};
}

Enemy::~Enemy() {
	//delete state_;
	delete player_;
}

void Enemy::Initialize(Model* model, Vector3 position) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("title_jiki.png");

	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = { position };

	state_ = new EnemyStateApproach();

	isAlive_ = true;

	health_ = 15;

	reviveCount_ = 0;

	changeStatePositionZ_ = GetRandom(50.0f, 80.0f);
}

void Enemy::Approach() {}

void Enemy::Leave() {
}

void Enemy::ChangeState(IEnemyState* newState) {
	//delete state_;
	isFire_ = false;
	state_ = newState;
}

void Enemy::Update() {
	state_->Update(this);

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::ChangePosition(Vector3 vector) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, vector);
}

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos = {};
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos = {
		worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2] };

	return worldPos;
}

void Enemy::OnCollision() {
	health_--;
}

bool Enemy::IsChangeStatePosition() {
	if (worldTransform_.translation_.z < changeStatePositionZ_) {
		return true;
	}
	else {
		return false;
	}
}

bool Enemy::IsFire() {
	if (isFire_) {
		return true;
	}
	else {
		return false;
	}
}

void Enemy::OnDeath() {
	if (health_ >= 0) {
		isAlive_ = false;
	}
}

void Enemy::PostDeath() {
	if (!isAlive_) {
		reviveCount_++;
	}

	if (reviveCount_ >= 60) {
		isAlive_ = true;
		reviveCount_ = 0;
	}
}
