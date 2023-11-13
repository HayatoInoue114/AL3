#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class ICharacter {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize(const std::vector<Model*>& models);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw(const ViewProjection& viewProjection, uint32_t textureHandle);

	/// <summary>
	/// ワールド変換データ
	/// </summary>
	/// <returns>ワールド変換データ</returns>
	const WorldTransform& GetworldTransform() { return worldTransform_; }

protected:
	std::vector<Model*> models_;

	WorldTransform worldTransform_;
};