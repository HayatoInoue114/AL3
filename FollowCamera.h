#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "MT.h"

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

	/// <summary>
	/// ビュープロジェクションを取得
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	const ViewProjection& GetViewProjection() { return viewProjection_; }

private:
	ViewProjection viewProjection_;

	const WorldTransform* ktarget_ = nullptr;
};
