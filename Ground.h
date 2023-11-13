#pragma once
#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// 地面
/// </summary>
class Ground {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection, uint32_t textureHandle);

private:
	Model* model_;

	WorldTransform worldTransform_;
};
