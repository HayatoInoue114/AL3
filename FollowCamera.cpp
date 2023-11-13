#include "FollowCamera.h"

void FollowCamera::Initialize() { 
	worldTransform_.Initialize();
}

void FollowCamera::Update() {
	if (ktarget_) {
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		viewProjection_.translation_ = Add(ktarget_->translation_, offset);
	}
}