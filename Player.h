#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "MT.h"
#include "ICharacter.h"


/// <summary>
/// 自キャラ
/// </summary>
class Player : ICharacter{
public:
	Player();
	~Player();

/// <summary>
/// 初期化
/// </summary>
/// <param name="model">モデル</param>
/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(const std::vector<Model*>& models) override;

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
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//キーボード入力
	Input* input_ = nullptr;
	
	
};

