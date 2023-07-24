#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model;
	delete player_;
	delete debugCamera_;
	delete enemy_;
	delete skydome_;
	delete modelSkydome_;
	delete railCamera_;
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		delete enemyBullet;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle = TextureManager::Load("godest.png");
	// 3Dモデルの生成
	model = Model::Create();

	worldTransform_.Initialize();

	// 3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	//ビュープロジェクションの初期化
	viewProjection.farZ = 500;
	viewProjection.Initialize();

	// レールカメラの生成
	railCamera_ = new RailCamera();
	// レールカメラの初期化
	railCamera_->Initialize({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});

	//自キャラの生成
	player_ = new Player();
	Vector3 playerPosition(0, 0, 50.0f);
	//自キャラの初期化
	player_->Initialize(model,textureHandle,playerPosition);
	

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection);

	//敵の生成
	enemy_ = new Enemy();
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	//敵の初期化
	enemy_->Initialize(model, {0.5f,0.0f,80.0f});
	enemy_->SetGameScene(this);
	
	//天球の生成
	skydome_ = new Skydome();
	//天球の初期化
	skydome_->Initialize(modelSkydome_);

	// 自キャラとレールカメラの親子関係を結ぶ
	player_->SetParent(&railCamera_->GetWorldTransform());
}

void GameScene::Update() {
	// レールカメラの更新
	railCamera_->Update();
	viewProjection.matView = railCamera_->GetViewProjection().matView;
	viewProjection.matProjection = railCamera_->GetViewProjection().matProjection;
	viewProjection.TransferMatrix();

	//自キャラの更新
	player_->Update();

	//敵の更新
	enemy_->Update();

	// デスフラグの立った弾を削除
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}

	//当たり判定
	CheckAllCollisions();

	//天球の更新
	skydome_->Update();

	

	//デバッグカメラの更新
//	debugCamera_->Update();
//#ifdef _DEBUG
//	if (input_->TriggerKey(DIK_LALT)) {
//		if (isDebugCameraActive_ == false) {
//			isDebugCameraActive_ = true;
//		} else {
//			isDebugCameraActive_ = false;
//		}
//		
//	}
//#endif // DEBUG
//
//	//カメラの処理
//	if (isDebugCameraActive_) {
//		debugCamera_->Update();
//		viewProjection.matView = debugCamera_->GetViewProjection().matView;
//		viewProjection.matProjection = debugCamera_->GetViewProjection().matProjection;
//		//ビュープロジェクション行列の転送
//		viewProjection.TransferMatrix();
//	} else {
//		//ビュープロジェクション行列の更新と転送
//		viewProjection.UpdateMatrix();
//	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	skydome_->Draw(viewProjection);

	player_->Draw(viewProjection);

	// 弾描画
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection);
	}

	enemy_->Draw(viewProjection);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() { 

	//自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemyBullets_;

	#pragma region 
	Vector3 playerPosition = player_->GetWorldPosition();

	Vector3 enemyPosition = enemy_->GetWorldPosition();

	for (EnemyBullet* enemyBullet : enemyBullets) {
		for (PlayerBullet* playerBullet : playerBullets) {
			//敵弾と自機
			Vector3 enemyBulletPosition = enemyBullet->GetWorldPosition();

			Vector3 distanceToEnemyBullet = Subtract(playerPosition, enemyBulletPosition);
			float dotEnemyBullet = (distanceToEnemyBullet.x * distanceToEnemyBullet.x) +
			                       (distanceToEnemyBullet.y * distanceToEnemyBullet.y) +
			                       (distanceToEnemyBullet.z * distanceToEnemyBullet.z);

			if (dotEnemyBullet <= 5) {
				player_->OnCollision();
				enemyBullet->OnCollision();
			}

			//自弾と敵
			Vector3 playerBulletPosition = playerBullet->GetWorldPosition();

			Vector3 distanceToPlayerBullet = Subtract(enemyPosition, playerBulletPosition);
			float dotPlayerBullet = (distanceToPlayerBullet.x * distanceToPlayerBullet.x) +
			                        (distanceToPlayerBullet.y * distanceToPlayerBullet.y) +
			                        (distanceToPlayerBullet.z * distanceToPlayerBullet.z);

			if (dotPlayerBullet <= 5) {
				player_->OnCollision();
				playerBullet->OnCollision();
			}
		}
	}

	#pragma endregion

	#pragma region
	#pragma endregion

	#pragma region
	#pragma endregion
}

void GameScene::AddEnemyBullet(EnemyBullet* enemhyBullet) {
	//リストに登録する
	enemyBullets_.push_back(enemhyBullet);
}