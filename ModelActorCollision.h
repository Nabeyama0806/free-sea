#pragma once
#include <list>

//�N���X�̑O���錾
class ModelActor;

//Actor���m�̐ڐG����N���X
class ModelActorCollision
{
private:
	std::list<ModelActor*> m_actorList;	//�Փ˔��������Actor�̃��X�g

	//�R���X�g���N�^
	ModelActorCollision() {}

public:
	//�V���O���g��
	static ModelActorCollision* GetInstance()
	{
		static ModelActorCollision instance;
		return &instance;
	}

	//�o�^
	void Register(ModelActor* actor)
	{
		m_actorList.push_back(actor);
	}

	//�폜
	void Remove(ModelActor* actor)
	{
		m_actorList.remove(actor);
	}

	//�X�V
	void Update();

#ifdef _DEBUG
	//�`��
	void Draw() const;
#endif
};