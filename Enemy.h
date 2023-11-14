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

	bool CheckCollisionWithPlayer();

	bool IsPlayerInFOV(const Vector3& toPlayer);

	Vector3 ForwardVector() { return {velocity_}; }

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Model* model_;

	ViewProjection viewProjection_;

	Player* player_;

	//Vector3 velocity_{};

	//追いかける強度(1が最大)
	float trackingPower_;

	//追いかけるスピード
	float chaseSpeed_;

	float velocityXZ_;

	Vector3 velocity_;

	bool isChase_;

	enum Situation {
		MOVE,
		STOP,
		CHASE
	};

	int situation_;

	float fovRadius_;

	float fovAngle_;
};

