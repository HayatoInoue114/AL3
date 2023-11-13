#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "MT.h"
#include "ICharacter.h"


/// <summary>
/// 自キャラ
/// </summary>
class Player{
public:
	Player();
	~Player();

/// <summary>
/// 初期化
/// </summary>
/// <param name="model">モデル</param>
/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureandle);

/// <summary>
/// 更新
/// </summary>
	void Update();

/// <summary>
/// 描画
/// </summary>
	void Draw(ViewProjection viewProjection);

	WorldTransform& GetWorldTransform() { return worldTransform_; }
	void SetWorldTransform(WorldTransform& worldTransform) { worldTransform_ = worldTransform; };

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_{};
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//キーボード入力
	Input* input_ = nullptr;
	
	
};

