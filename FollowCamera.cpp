#include "FollowCamera.h"

void FollowCamera::Initialize() {
	viewProjection_.Initialize();
}

void FollowCamera::Update() {
	if (ktarget_) {
		Vector3 offset = {0.0f, 5.0f, -50.0f};

		viewProjection_.translation_ = Add(ktarget_->translation_, offset);
	}
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}