#include "action.h"
#include "GameObject.h"
#include "GameTimer.h"
#include"ObjectGenerator.h"


void Attack1_Update(Action* pThis);
void Attack2_Update(Action* pThis);
void Heel_UPdate(Action* pThis);
void Magic_Update(Action* pThis);
void FxSword_Update(Action* pThis);
void FxWindshot_Update(Action* pThis);
void FxWindshot_Update2left(Action* pThis);
void Flee_Update(Action* pThis);


//�e�A�j���[�V�����������p
//extern GameObject* gpPlayer;
//extern GameObject* gpEnemy;
extern GameObject* gpMagic;
extern GameObject* gpSword;

//�e�A�j���[�V�����I�����t���O�ύX�p
extern Battle* Bflg;



void Action_Initialize(Action* pThis, GameObject* pObj)
{
	pThis->pOwner = pObj;
	Action_Set(pThis, ACTION_NONE);
}

void Action_Set(Action* pThis, int actionId)
{
	pThis->id = actionId;
	pThis->isActive = true;
	pThis->time = 0.0f;
}

void Action_SetNONE(Action* pThis)
{
	pThis->isActive = true;
	pThis->time = 0.0f;
}

void Action_Update(Action* pThis)
{
	if (pThis->isActive) {
		switch (pThis->id) {
		case ACTION_NONE:
			pThis->isActive = false;
			break;

		case ACTION_ATTACK1:
			Attack1_Update(pThis);
			break;

		case ACTION_ATTACK2:
			Attack2_Update(pThis);
			break;

		case HEEL:
			Heel_UPdate(pThis);
			break;

		case ACTION_MAGIC:
			Magic_Update(pThis);
			break;

		case ACTION_FX_SWORD:
			FxSword_Update(pThis);
			break;

		case ACTION_FX_WINDSHOT:
			FxWindshot_Update(pThis);
			break;

		case ACTION_FX_WINDSHOT2left:
			FxWindshot_Update2left(pThis);
			break;

		case ACTION_FLEE:
			Flee_Update(pThis);
			/*
		case ACTION_SHOP1:
			SHOP1(pThis);*/

		}


		//���Ԃ����Z
		pThis->time += GameTimer_GetDeltaTime();
	}
}

void Attack1_Update(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // ������ۑ�

	if (time >= 0.0f && time < 0.5f) {
		pThis->pOwner->posX += 0.005f * direction; // �O�i
		//pThis->pOwner->animator.frame = 0; // �A�j���[�V�������O�R�}�ڂŌŒ�
	}
	if (time >= 0.5f) {
		pThis->isActive = false;
		//�^�[����i�s������
		Bflg->bstruct.battle_turn = Bname::Bplattakend;
	}


}

void Attack2_Update(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // ������ۑ�

	if (time >= 0.0f && time < 1.0f) {
		pThis->pOwner->posX += 0.011f * direction; // �O�i
		//pThis->pOwner->animator.frame = 0; // �A�j���[�V�������O�R�}�ڂŌŒ�
	}
	float direction1 = pThis->pOwner->charController.direction == DIR_LEFT ? -1.0f : 1.0f; // ������ۑ�
	if (time >= 1.4f && time < 2.5f) {
		pThis->pOwner->posX -= 0.011f * direction1; // ��i
		//pThis->pOwner->animator.frame = 0; // �A�j���[�V�������O�R�}�ڂŌŒ�
	}
	if (time >= 2.5f) {
		pThis->isActive = false;
		//�^�[����i�s������
		Bflg->bstruct.battle_turn = Bname::Bplattakend;
	}


}

void Heel_UPdate(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // ������ۑ�

	if (time >= 0.0f && time < 0.2f) {

		pThis->pOwner->posX += 0.005f * direction; // �O�i

	}
	else if (time >= 0.2f && time < 0.4f) {

		pThis->pOwner->posX -= 0.005f * direction; // �O�i
	}
	else if (time >= 0.4f && time < 0.6f) {

		pThis->pOwner->posX += 0.005f * direction; // �O�i

	}
	else if (time >= 0.6f && time < 0.8f) {

		pThis->pOwner->posX -= 0.005f * direction; // �O�i

	}
	if (time >= 1.5f) {
		pThis->isActive = false;
		//�^�[����i�s������
		Bflg->bstruct.battle_turn = Bname::Bplattakend;
	}
}

void Magic_Update(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // ������ۑ�

	if (time >= 0.0f && time < 0.25f) {
		pThis->pOwner->posX -= 0.005f * direction; // ��i
		//pThis->pOwner->animator.frame = 0; // �A�j���[�V�������O�R�}�ڂŌŒ�
	}
	//float direction1 = pThis->pOwner->charController.direction == DIR_LEFT ? -1.0f : 1.0f; // ������ۑ�
	if (time >= 0.5f && time < 0.75f) {
		pThis->pOwner->posX += 0.005f * direction; // �O�i
		//pThis->pOwner->animator.frame = 0; // �A�j���[�V�������O�R�}�ڂŌŒ�
	}
	if (time >= 2.0f) {
		pThis->isActive = false;
		//�^�[����i�s������
		Bflg->bstruct.battle_turn = Bname::Bplattakend;
	}


}

void FxSword_Update(Action* pThis)
{
	float time = pThis->time;

	if (time <= 1.0f) {
		pThis->isActive = true;//����������ōs�����ƂŃA�j���[�V�������ĊJ
		pThis->pOwner->animator.time = 0;
		pThis->pOwner->animator.isActive = true;
	}
	if (time >= 1.2f) {
		pThis->pOwner->collider.isActive = true;
	}
	if (time >= 1.5f) {
		// �A�N�V�����I��
		pThis->isActive = false;
		pThis->pOwner->collider.isActive = false;

	}
}

void FxWindshot_Update(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // ������ۑ�


	if (time == 0.0f) {
		pThis->isActive = true;//����������ōs�����ƂŃA�j���[�V�������ĊJ
		pThis->pOwner->animator.time = 0;
		pThis->pOwner->animator.isActive = true;
		pThis->pOwner->collider.isActive = true;

		pThis->pOwner->posX = 0.5f;//�����������I�Ɉړ�
		pThis->pOwner->posY = -0.35f;

		pThis->pOwner->sizeX = 0.01f; // �������T�C�Y����J�n
		pThis->pOwner->sizeY = 0.01f;
	}
	if (time <= 0.5f) {

		pThis->pOwner->sizeX *= 1.15f; // �傫��
		pThis->pOwner->sizeY *= 1.15f;
	}
	if (time >= 0.5f) {
		pThis->pOwner->posX -= 0.025f;
	}
	if (time >= 3.0f) {
		// �A�N�V�����I��
		pThis->isActive = false;
		pThis->pOwner->collider.isActive = false;
		pThis->pOwner->posX = 3.0f;
	}


}

void FxWindshot_Update2left(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // ������ۑ�


	if (time == 0.0f) {
		pThis->isActive = true;//����������ōs�����ƂŃA�j���[�V�������ĊJ
		pThis->pOwner->animator.time = 0;
		pThis->pOwner->animator.isActive = true;
		pThis->pOwner->collider.isActive = true;

		pThis->pOwner->posX = -0.5f;//�����������I�Ɉړ�
		pThis->pOwner->posY = -0.35f;

		pThis->pOwner->sizeX = 0.01f; // �������T�C�Y����J�n
		pThis->pOwner->sizeY = 0.01f;
	}
	if (time <= 0.5f) {

		pThis->pOwner->sizeX *= 1.15f; // �傫��
		pThis->pOwner->sizeY *= 1.15f;
	}
	if (time >= 0.5f) {
		pThis->pOwner->posX += 0.025f;
	}
	if (time >= 3.0f) {
		// �A�N�V�����I��
		pThis->isActive = false;
		pThis->pOwner->collider.isActive = false;
		pThis->pOwner->posX = 3.0f;
	}


}

void Flee_Update(Action* pThis)//������Ƃ�
{
	//���Ԃ����Z���Ė�����w��A�A�N�V�������C���N���[�h����Ȃ�
	float time = pThis->time;
	//���Ԃ����Z
	//time += GameTimer_GetDeltaTime();

	if (time >= 2.0f)
	{
		// �A�N�V�����I��
		pThis->isActive = false;
		//�^�[����i�s������
		Bflg->bstruct.battle_turn = Bname::Bplattakend;
	}

}

//*****************************
//�퓬���̍s������֐�

void attac_magic(GameObject* gp, int num)//��΂����@�g�p
{
	// ���@�G�t�F�N�g�������A1�ڂ�X�A2�ڂ�Y
	//gpMagic->pOwner = gp;

	Action_Set(&gp->action, ACTION_MAGIC);

	if (num == Bname::BPlayer)
	{
		/*gpMagic->localPosX = 0.5f;
		gpMagic->localPosY = -0.35f;*/

		Action_Set(&gpMagic->action, ACTION_FX_WINDSHOT);
		//gpMagic->animator.flip = FLIP_NONE;



	}
	if (num == Bname::BEnemy)
	{

		Action_Set(&gpMagic->action, ACTION_FX_WINDSHOT2left);
		//gpMagic->animator.flip = FLIP_HIRIZONTAL;
		/*gpMagic->localPosX = -0.5f;
		gpMagic->localPosY = -0.5f;*/


	}

}


void attac_sword(GameObject* gp, int num)//�ʏ�U�����[�V����
{
	// ���G�t�F�N�g�������A1�ڂ�X�A2�ڂ�Y
	gpSword->pOwner = gp;

	Action_Set(&gp->action, ACTION_ATTACK2);
	Action_Set(&gpSword->action, ACTION_FX_SWORD);
	if (num == Bname::BPlayer)
	{
		gpSword->animator.flip = FLIP_NONE;
		gpSword->localPosX = -0.4f;
		gpSword->localPosY = 0.1f;
	}
	if (num == Bname::BEnemy)
	{
		gpSword->animator.flip = FLIP_HIRIZONTAL;
		gpSword->localPosX = 0.3f;
		gpSword->localPosY = 0.0f;
	}

}

void heel_command(GameObject* gp, int num)//�񕜃��[�V����
{
	// �q�[���p���@�w�ɕύX
	// ���G�t�F�N�g�������A1�ڂ�X�A2�ڂ�Y

	gpSword->pOwner = gp;

	Action_Set(&gp->action, HEEL);
	Action_Set(&gpSword->action, ACTION_FX_SWORD);
	if (num == Bname::BPlayer)
	{
		gpSword->animator.flip = FLIP_NONE;
		gpSword->localPosX = -0.3f;
		gpSword->localPosY = 0.1f;
	}
	if (num == Bname::BEnemy)
	{
		gpSword->animator.flip = FLIP_HIRIZONTAL;
		gpSword->localPosX = 0.3f;
		gpSword->localPosY = 0.0f;
	}

}

void flee_command(GameObject* gp)//�����̋�
{

	Action_Set(&gp->action, ACTION_FLEE);

}