#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include "MT.h"
#include <assert.h>

/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);


	enum class Phase {
		Approach,	//接近する
		Leave,		//離脱する
	};

	void Approach();
	void Leave();
	void Situation();

	

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//フェーズ
	Phase phase_ = Phase::Approach;

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	//メンバ関数ポインタ
	static void (Enemy::*situation[])();
	
	
};
