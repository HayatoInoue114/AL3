#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <imgui.h>

class RailCamera {
public:
/// <summary>
/// 初期化
/// </summary>
	void Initialize(WorldTransform& worldTransform);

/// <summary>
/// 更新
/// </summary>
	void Update();

private:
	//ワールド変換データ
	WorldTransform worldTransform_;

	//ビュープロジェクション
	ViewProjection viewProjection_;
};

