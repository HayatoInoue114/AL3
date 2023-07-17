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
	for (EnemyBullet* enemyBullet : bullets_) {
		delete enemyBullet;
	}
	
}

void Enemy::Initialize(Model* model, Vector3 position) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("title_jiki.png");
	
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = {position};

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

	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
	
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
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
	bullets_.push_back(newBullet);
}

void EnemyStateApproach::FireAndResetCallback() {
	enemy_->Fire(); 

	timedCalls_.push_back(
	    new TimedCall(std::bind(&EnemyStateApproach::FireAndResetCallback, this), kFireInterval));

	////発射タイマーをセットする
	//std::function<void(void)> callback = std::bind(&Enemy::FireAndResetCallback, this);

	//TimedCall* timedCall = new TimedCall(callback, kFireInterval);

	//timedCalls_.push_back(timedCall);
}

EnemyStateApproach::~EnemyStateApproach() {
	for (TimedCall* timedCall : timedCalls_) {
		delete timedCall;
	}
}

void EnemyStateApproach::Initialize(Enemy* enemy) { 
	enemy_ = enemy;
	FireAndResetCallback();
}

void EnemyStateApproach::Update(Enemy* pEnemy) {
	enemy_ = pEnemy;
	Vector3 position = enemy_->GetWorldPosition();

	Vector3 move = {0.01f, 0, -0.015f};
	
	// 終了したタイマーを削除
	timedCalls_.remove_if([](TimedCall* timedCall) {
		if (timedCall->IsFinished()) {
			delete timedCall;
			return true;
		}
		return false;
	});
	
	// 範囲for文でリストの全要素について回す
	for (TimedCall* timedCall : timedCalls_) {
		timedCall->Update();
	}

	enemy_->ChangePosition(move);
	// 既定の位置に到達したら離脱
	if (position.z < -20.0f) {
		enemy_->ChangeState(new EnemyStateLeave());
	}

}

void EnemyStateLeave::Initialize(Enemy* enemy) { 
	enemy_ = enemy;
}

void EnemyStateLeave::Update(Enemy* pEnemy) {
	enemy_ = pEnemy;
	Vector3 position = enemy_->GetWorldPosition();

	Vector3 move = {0.1f, 0.1f, 0};
	// 移動


	enemy_->ChangePosition(move);
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

