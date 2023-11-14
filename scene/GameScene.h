#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include <memory>
#include <wrl.h>
#include "Ground.h"
#include "FollowCamera.h"
#include "Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	/// //テクスチャハンドル
	uint32_t textureHandle = 0;

	// 3Dモデルデータ
	std::unique_ptr<Model> model_;

	// ビュープロジェクション
	ViewProjection viewProjection;

	// 自キャラ
	std::unique_ptr<Player> player_{};

	//デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	//デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_{};

	//地面
	std::unique_ptr<Ground> ground_{};
	std::unique_ptr<Model> modelGround_{};
	uint32_t groundTexture_{};

	//追従カメラ
	std::unique_ptr<FollowCamera> followCamera_{};
	
	std::unique_ptr<Enemy> enemy_{};
	uint32_t enemyTexture_{};
	std::unique_ptr<Model> modelEnemy_{};
};
