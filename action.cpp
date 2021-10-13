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


//各アニメーション発生時用
//extern GameObject* gpPlayer;
//extern GameObject* gpEnemy;
extern GameObject* gpMagic;
extern GameObject* gpSword;

//各アニメーション終了時フラグ変更用
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


		//時間を加算
		pThis->time += GameTimer_GetDeltaTime();
	}
}

void Attack1_Update(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // 向きを保存

	if (time >= 0.0f && time < 0.5f) {
		pThis->pOwner->posX += 0.005f * direction; // 前進
		//pThis->pOwner->animator.frame = 0; // アニメーションを０コマ目で固定
	}
	if (time >= 0.5f) {
		pThis->isActive = false;
		//ターンを進行させる
		Bflg->bstruct.battle_turn = Bname::Bplattakend;
	}


}

void Attack2_Update(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // 向きを保存

	if (time >= 0.0f && time < 1.0f) {
		pThis->pOwner->posX += 0.011f * direction; // 前進
		//pThis->pOwner->animator.frame = 0; // アニメーションを０コマ目で固定
	}
	float direction1 = pThis->pOwner->charController.direction == DIR_LEFT ? -1.0f : 1.0f; // 向きを保存
	if (time >= 1.4f && time < 2.5f) {
		pThis->pOwner->posX -= 0.011f * direction1; // 後進
		//pThis->pOwner->animator.frame = 0; // アニメーションを０コマ目で固定
	}
	if (time >= 2.5f) {
		pThis->isActive = false;
		//ターンを進行させる
		Bflg->bstruct.battle_turn = Bname::Bplattakend;
	}


}

void Heel_UPdate(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // 向きを保存

	if (time >= 0.0f && time < 0.2f) {

		pThis->pOwner->posX += 0.005f * direction; // 前進

	}
	else if (time >= 0.2f && time < 0.4f) {

		pThis->pOwner->posX -= 0.005f * direction; // 前進
	}
	else if (time >= 0.4f && time < 0.6f) {

		pThis->pOwner->posX += 0.005f * direction; // 前進

	}
	else if (time >= 0.6f && time < 0.8f) {

		pThis->pOwner->posX -= 0.005f * direction; // 前進

	}
	if (time >= 1.5f) {
		pThis->isActive = false;
		//ターンを進行させる
		Bflg->bstruct.battle_turn = Bname::Bplattakend;
	}
}

void Magic_Update(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // 向きを保存

	if (time >= 0.0f && time < 0.25f) {
		pThis->pOwner->posX -= 0.005f * direction; // 後進
		//pThis->pOwner->animator.frame = 0; // アニメーションを０コマ目で固定
	}
	//float direction1 = pThis->pOwner->charController.direction == DIR_LEFT ? -1.0f : 1.0f; // 向きを保存
	if (time >= 0.5f && time < 0.75f) {
		pThis->pOwner->posX += 0.005f * direction; // 前進
		//pThis->pOwner->animator.frame = 0; // アニメーションを０コマ目で固定
	}
	if (time >= 2.0f) {
		pThis->isActive = false;
		//ターンを進行させる
		Bflg->bstruct.battle_turn = Bname::Bplattakend;
	}


}

void FxSword_Update(Action* pThis)
{
	float time = pThis->time;

	if (time <= 1.0f) {
		pThis->isActive = true;//これをここで行うことでアニメーションを再開
		pThis->pOwner->animator.time = 0;
		pThis->pOwner->animator.isActive = true;
	}
	if (time >= 1.2f) {
		pThis->pOwner->collider.isActive = true;
	}
	if (time >= 1.5f) {
		// アクション終了
		pThis->isActive = false;
		pThis->pOwner->collider.isActive = false;

	}
}

void FxWindshot_Update(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // 向きを保存


	if (time == 0.0f) {
		pThis->isActive = true;//これをここで行うことでアニメーションを再開
		pThis->pOwner->animator.time = 0;
		pThis->pOwner->animator.isActive = true;
		pThis->pOwner->collider.isActive = true;

		pThis->pOwner->posX = 0.5f;//向きを強制的に移動
		pThis->pOwner->posY = -0.35f;

		pThis->pOwner->sizeX = 0.01f; // 小さいサイズから開始
		pThis->pOwner->sizeY = 0.01f;
	}
	if (time <= 0.5f) {

		pThis->pOwner->sizeX *= 1.15f; // 大きく
		pThis->pOwner->sizeY *= 1.15f;
	}
	if (time >= 0.5f) {
		pThis->pOwner->posX -= 0.025f;
	}
	if (time >= 3.0f) {
		// アクション終了
		pThis->isActive = false;
		pThis->pOwner->collider.isActive = false;
		pThis->pOwner->posX = 3.0f;
	}


}

void FxWindshot_Update2left(Action* pThis)
{
	float time = pThis->time;
	float direction = pThis->pOwner->charController.direction == DIR_RIGHT ? 1.0f : -1.0f; // 向きを保存


	if (time == 0.0f) {
		pThis->isActive = true;//これをここで行うことでアニメーションを再開
		pThis->pOwner->animator.time = 0;
		pThis->pOwner->animator.isActive = true;
		pThis->pOwner->collider.isActive = true;

		pThis->pOwner->posX = -0.5f;//向きを強制的に移動
		pThis->pOwner->posY = -0.35f;

		pThis->pOwner->sizeX = 0.01f; // 小さいサイズから開始
		pThis->pOwner->sizeY = 0.01f;
	}
	if (time <= 0.5f) {

		pThis->pOwner->sizeX *= 1.15f; // 大きく
		pThis->pOwner->sizeY *= 1.15f;
	}
	if (time >= 0.5f) {
		pThis->pOwner->posX += 0.025f;
	}
	if (time >= 3.0f) {
		// アクション終了
		pThis->isActive = false;
		pThis->pOwner->collider.isActive = false;
		pThis->pOwner->posX = 3.0f;
	}


}

void Flee_Update(Action* pThis)//逃げるとき
{
	//時間を加算して眠りを指定、アクションをインクルードするなら
	float time = pThis->time;
	//時間を加算
	//time += GameTimer_GetDeltaTime();

	if (time >= 2.0f)
	{
		// アクション終了
		pThis->isActive = false;
		//ターンを進行させる
		Bflg->bstruct.battle_turn = Bname::Bplattakend;
	}

}

//*****************************
//戦闘時の行動制御関数

void attac_magic(GameObject* gp, int num)//飛ばす魔法使用
{
	// 魔法エフェクト初期化、1つ目がX、2つ目がY
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


void attac_sword(GameObject* gp, int num)//通常攻撃モーション
{
	// 剣エフェクト初期化、1つ目がX、2つ目がY
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

void heel_command(GameObject* gp, int num)//回復モーション
{
	// ヒール用魔法陣に変更
	// 剣エフェクト初期化、1つ目がX、2つ目がY

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

void flee_command(GameObject* gp)//逃げの空白
{

	Action_Set(&gp->action, ACTION_FLEE);

}