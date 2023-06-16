#include "TimedCall.h"


TimedCall::TimedCall(std::function<int(int)> f, uint32_t time) {
	f_ = f; 
	time_ = time;
}

TimedCall::~TimedCall() {}

void TimedCall::Update() { 
	if (isComplete) {
		return;
	}
	time_--;
	if (time_ <= 0) {
		isComplete = true;
		//�R�[���o�b�N�֐��Ăяo��
		std::function<int(int)> f_();
	}
}