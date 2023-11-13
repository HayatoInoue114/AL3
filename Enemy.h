#pragma once
#include "ICharacter.h"

class Enemy
{
public:
	/// <summary>
	/// 初期化
	/// <summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// <summary>
	void Update();

	/// <summary>
	/// 描画
	/// <summary>
	void Draw(const ViewProjection& viewProjection);

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Model* model_;

	ViewProjection viewProjection_;
};

