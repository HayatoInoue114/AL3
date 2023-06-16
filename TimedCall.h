#pragma once
#include <iostream>
#include <functional>

/// <summary>
/// ��������
/// </summary>
class TimedCall {
public:
	TimedCall(std::function <int(int)> f, uint32_t time);
	~TimedCall();

	//�X�V
	void Update();

	//�����Ȃ�true��Ԃ�
	bool IsFinished() { return isComplete; }

private:
	//�R�[���o�b�N
	std::function<int(int)> f_;

	//�c�莞��
	uint32_t time_;

	//�����t���O
	bool isComplete;
};

