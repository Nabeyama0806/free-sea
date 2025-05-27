#pragma once

struct SpriteAnimation
{
public:
	const char* textureName; //�摜�p�X
	int textureId;			 //�`�悷��摜
	int gridAmount;			 //�A�j���[�V�����̃R�}��
	int sampleRate;			 //1�b���ɃA�j���[�V�����̃R�}��؂�ւ����
	bool loopFlag;			 //�A�j���[�V�����̂����[�v���邩�ǂ���

	//�R���X�g���N�^
	SpriteAnimation(
		const char* textureName,
		int gridAmount = 1,
		int sampleRate = 10,
		bool loopFlag = true
	) :
		textureName(textureName),
		textureId(0),
		gridAmount(gridAmount),
		sampleRate(sampleRate),
		loopFlag(loopFlag) {
	}
};
