#include "Enemy.h"
#include "Player.h"

void (Enemy::*Enemy::situation[])() = {
	&Enemy::Approach,
	&Enemy::Leave
};

Enemy::Enemy() { 
	state_ = new EnemyStateApproach();
	/*player_ = new Player();*/
	deltaVector_ = {};
	velocity_ = {};
}

Enemy::~Enemy() { 
	/*delete state_;
	delete player_;*/
	
	
}

void Enemy::Initialize(Model* model, Vector3 position,GameScene* gameScene) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("title_jiki.png");
	
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = {position};

	SetGameScene(gameScene);

	state_->Initialize(this);
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

	//worldTransform_.matWorld_ = MakeAffineMatrix(
	//    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::ChangePosition(Vector3 vector) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, vector);
}

void Enemy::Fire() {
	assert(player_);

	// 弾の速度
	const float kBulletSpeed = 1.0f;
	velocity_ = {1, 1, kBulletSpeed};

	//差分ベクトルを求める
	velocity_ = Subtract(player_->GetWorldPosition(), GetWorldPosition());

	//ベクトルの正規化
	velocity_ = Normalize(velocity_);

	//ベクトルの長さを速さに合わせる
	velocity_ = Multiply(kBulletSpeed, velocity_);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, GetWorldPosition(), velocity_);

	// 弾を登録する
	gameScene_->AddEnemyBullet(newBullet);

}



Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos = {};
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos = {
	    worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
	    worldTransform_.matWorld_.m[3][2]
	};

	return worldPos;
}

void Enemy::OnCollision() {

}

