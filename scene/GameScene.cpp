#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle = TextureManager::Load("godest.png");
	// 3Dモデルの生成
	model_.reset(Model::Create());
	modelGround_.reset(Model::CreateFromOBJ("ground", 1));
	groundTexture_ = TextureManager::Load("ground.png");

	modelEnemy_.reset(Model::CreateFromOBJ("enemy", 1));
	enemyTexture_ = TextureManager::Load("enemy.png");

	//ビュープロジェクションの初期化
	viewProjection.Initialize();

	//自キャラの生成
	player_ = std::make_unique<Player>();
	//自キャラの初期化
	player_->Initialize(model_.get(),textureHandle);

	enemy_ = std::make_unique<Enemy>();
	enemy_->SetPlayer(player_.get());
	enemy_->Initialize(model_.get(), enemyTexture_);

	//地面
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGround_.get());
	
	//追従カメラ
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->SetTarget(&player_->GetWorldTransform());
	followCamera_->Initialize();

	//デバッグカメラの生成
	//debugCamera_ = std::make_unique<DebugCamera>(1280, 720);

	//軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection);
}

void GameScene::Update() {
	//自キャラの更新
	player_->Update();

	enemy_->Update();

	followCamera_->Update();
	viewProjection.matView = followCamera_->GetViewProjection().matView;
	viewProjection.matProjection = followCamera_->GetViewProjection().matProjection;
	// ビュープロジェクション行列の転送
	viewProjection.TransferMatrix();
	//デバッグカメラの更新
	//debugCamera_->Update();
#ifdef _DEBUG
	//if (input_->TriggerKey(DIK_SPACE)) {
	//	if (isDebugCameraActive_ == false) {
	//		isDebugCameraActive_ = true;
	//	} else {
	//		isDebugCameraActive_ = false;
	//	}
	//	
	//}
#endif // DEBUG

	//カメラの処理
	//if (isDebugCameraActive_) {
	//	debugCamera_->Update();
	//	viewProjection.matView = debugCamera_->GetViewProjection().matView;
	//	viewProjection.matProjection = debugCamera_->GetViewProjection().matProjection;
	//	//ビュープロジェクション行列の転送
	//	viewProjection.TransferMatrix();
	//} else {
	//	//ビュープロジェクション行列の更新と転送
	//	viewProjection.UpdateMatrix();
	//}
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
	player_->Draw(viewProjection);

	enemy_->Draw(viewProjection);

	ground_->Draw(viewProjection, groundTexture_);
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
