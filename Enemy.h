#pragma once
#include "ICharacter.h"
#include "MT.h"

class Player;

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

	Player* player_{};

	Vector3 velocity_{};

	float speed_{};

	float velocityXZ_{};

	float t_{};
};

