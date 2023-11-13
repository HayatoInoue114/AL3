#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"

/// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera {
public:
/// <summary>
/// 初期化
/// </summary>
	void Initialize();

/// <summary>
/// 更新
/// </summary>
	void Update();

	void SetTarget(const WorldTransform* target) { ktarget_ = target; }

private:
	ViewProjection viewProjection_;

	WorldTransform worldTransform_;

	const WorldTransform* ktarget_ = nullptr;
};
