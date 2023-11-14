#pragma once
#include "MT.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

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

	WorldTransform& GetWorldTransform() { return worldTransform_; }
	void SetPlayer(Player* player) { player_ = player; }

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Model* model_;

	ViewProjection viewProjection_;

	Player* player_;

	//Vector3 velocity_{};

	float t_;

	float speed_;

	float velocityXZ_;

	const float kBulletSpeed = 1.0f;
	Vector3 velocity_;
};

