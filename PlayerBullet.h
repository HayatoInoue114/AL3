#pragma once
#include"Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include <assert.h>

class PlayerBullet {
public:
	PlayerBullet();
	~PlayerBullet();

/// <summary>
/// 初期化
/// </summary>
/// <param name="model">モデル</param>
/// <param name="position">初期座標</param>
	void Initialize(Model* model, const Vector3& position);

/// <summary>
/// 更新
/// </summary>
	void Update();

/// <summary>
/// 描画
/// </summary>
/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);



private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};


