#include "WDemianPhase2.h"
#include "WAnimator.h"
#include "WRigidbody.h"
#include "WResources.h"
#include "WMonsterDead.h"
#include "WMonsterFSM.h"
#include "WMonsterStand.h"
#include "WMonsterAttack.h"
#include "WMonsterMove.h"
#include "WMonsterScript.h"
#include "WSpawnMonsterAttack.h"
#include "WBattleManager.h"
#include "WDemianFire1.h"
#include "WDemianFire2.h"
#include "WEffect.h"
#include "WEventManager.h"
#include "WMonsterMoveAttack.h"
#include "WDemianSpear0.h"
#include "WDemianSpear1.h"

namespace W
{
	DemianPhase2::DemianPhase2():
		m_bGroggy(false),
		m_iSpearCount(0)
	{
		SetName(L"Demian2");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"DemianMater", pMater);

		pRenderer->SetMaterial(pMater);
		AddComponent<Rigidbody>();

		std::shared_ptr<Texture> pNormal2 =
			Resources::Load<Texture>(L"Demian2Normal", L"..\\Resources\\Texture\\Monster\\demian\\stand1.png");
		std::shared_ptr<Texture> pAttack20 =
			Resources::Load<Texture>(L"Demian2_attack0", L"..\\Resources\\Texture\\Monster\\demian\\attack10.png");
		std::shared_ptr<Texture> pAttack21 =
			Resources::Load<Texture>(L"Demian2_attack1", L"..\\Resources\\Texture\\Monster\\demian\\attack11.png");
		std::shared_ptr<Texture> pAttack22 =
			Resources::Load<Texture>(L"Demian2_attack2", L"..\\Resources\\Texture\\Monster\\demian\\attack12.png");
		std::shared_ptr<Texture> pAttack23 =
			Resources::Load<Texture>(L"Demian2_attack3", L"..\\Resources\\Texture\\Monster\\demian\\attack13.png");
		std::shared_ptr<Texture> pAttack24 =
			Resources::Load<Texture>(L"Demian2_attack4", L"..\\Resources\\Texture\\Monster\\demian\\attack14.png");
		std::shared_ptr<Texture> pAttack25 =
			Resources::Load<Texture>(L"Demian2_attack5", L"..\\Resources\\Texture\\Monster\\demian\\attack15.png");

		Animator* pAnim = AddComponent<Animator>();
		//////////////////������ 2///////////////////////
		pAnim->Create(L"Demian2_stand_left", pNormal2, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack0_left", pAttack20, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack0_left")->Create(L"Demian2_attack0_left", pAttack20, Vector2(0.f, 2000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack1_left", pAttack21, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for (int i = 0; i < 8; ++i)
			pAnim->FindAnimation(L"Demian2_attack1_left")->Create(L"Demian2_attack1_left", pAttack21, Vector2(0.f, 2000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack1_left")->Create(L"Demian2_attack1_left", pAttack21, Vector2(0.f, 4000.f), Vector2(2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 2000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 4000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 6000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 8000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 10000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 12000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);

		pAnim->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 2000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 4000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 6000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 8000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 10000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 12000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 2000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for(int i = 0; i<8; ++i)
			pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 4000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 6000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 8000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 10000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 12000.f), Vector2(2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 2000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 4000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 6000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 8000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 10000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 12000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_stand_right", pNormal2, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack0_right", pAttack20, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack0_right")->Create(L"Demian2_attack0_right", pAttack20, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack1_right", pAttack21, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for (int i = 0; i < 8; ++i)
			pAnim->FindAnimation(L"Demian2_attack1_right")->Create(L"Demian2_attack1_right", pAttack21, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack1_right")->Create(L"Demian2_attack1_right", pAttack21, Vector2(12000.f, 4000.f), Vector2(-2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 4000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 6000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 8000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 10000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 12000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);

		pAnim->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 4000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 6000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 8000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 10000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 12000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
	

		pAnim->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for(int i = 0; i<8; ++i)
			pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 4000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 6000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 8000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 10000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 12000.f), Vector2(-2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 4000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 6000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 8000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 10000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 12000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);


		Resources::Load<Texture>(L"demainfire1", L"..\\Resources\\Texture\\Monster\\demian\\demianfire1.png");
		Resources::Load<Texture>(L"demainfire2", L"..\\Resources\\Texture\\Monster\\demian\\demainfire2.png");
		Resources::Load<Texture>(L"demianClone0", L"..\\Resources\\Texture\\Monster\\demian\\demianclone0.png");
		Resources::Load<Texture>(L"demianClone1", L"..\\Resources\\Texture\\Monster\\demian\\demianclone1.png");
		Resources::Load<Texture>(L"demianspear0", L"..\\Resources\\Texture\\Monster\\demian\\demianspear0.png");
		Resources::Load<Texture>(L"demianspear1", L"..\\Resources\\Texture\\Monster\\demian\\demianspear1.png");

		Resources::Load<Texture>(L"demianfire1hit", L"..\\Resources\\Texture\\Monster\\demian\\demianfire1hit.png");
		Effect* pAttack_hit1 = new Effect();
		pAttack_hit1->SetName(L"Demian_attack1");
		pAttack_hit1->CreateAnimation(Resources::Find<Texture>(L"demianfire1hit"), Vector2(0.f, 0.f), Vector2(227.f, 228.f), 5, 1, Vector2(250.f, 250.f), Vector2(0.f, 0.f), 0.2f);


		Resources::Load<Texture>(L"DemianAttack0Effect", L"..\\Resources\\Texture\\Monster\\demian\\demianEffect.png");
		Effect* pEffect = new Effect();
		pEffect->GetComponent<Transform>()->SetScale(Vector3(18.f, 18.f, 0.f));
		pEffect->SetName(L"DemianAttack0Effect");
		pEffect->CreateAnimation(Resources::Find<Texture>(L"DemianAttack0Effect"), Vector2(0.f, 0.f), Vector2(1122.f, 382.f), 9, 1, Vector2(2000.f, 2000.f), Vector2(0.f, 0.f), 0.1f);

		//���̾� â ����
		set_effect();
	
		//���� �� �̵�
		pAnim->EndEvent(L"Demian2_attack3_right") = std::bind(&DemianPhase2::move, this);
		pAnim->EndEvent(L"Demian2_attack3_left") = std::bind(&DemianPhase2::move, this);
	}
	DemianPhase2::~DemianPhase2()
	{
	}
	void DemianPhase2::Initialize()
	{
		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);
		GetComponent<Transform>()->SetPosition(0.1f, -1.8f, -1.5f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.06f, 0.06f));
		pCollider->SetCenter(Vector2(0.f, -0.4f));

		MonsterScript* Pscript = AddComponent<MonsterScript>();
		Pscript->SetBoss();
		Pscript->Initialize();
		Pscript->CreateHP();

		setattack();
		add_skill();

		MonsterFSM* pFSM = new MonsterFSM();
		pFSM->SetMonster(this);
		Pscript->SetFSM(pFSM);

		MonsterStand* pStand = new MonsterStand();
		pStand->SetTargetDistance(15.f);
		pStand->SetMinDistance(15.f);
		pFSM->AddState(pStand);

		pFSM->AddState(new MonsterMove());
		pFSM->AddState(new MonsterAttack());
		pFSM->AddState(new MonsterDead());
		pFSM->SetActiveState(eMonsterState::stand);
	}
	void DemianPhase2::Update()
	{
		check_HP();

		Monster::Update();
	}
	void DemianPhase2::LateUpdate()
	{
		std::wstring strName = GetName();
		std::wstring strState = GetCurStateName();
		std::wstring strDir;

		if (strState == L"_attack")
		{
			UINT iNumber = GetScript<MonsterScript>()->GetAttackNumber();
			strState += std::to_wstring(iNumber);
		}
		int iDir = GetDir();


		if (iDir > 0)
			strDir = L"_right";
		else
			strDir = L"_left";

		std::wstring strCurAnim = strName + strState + strDir;
		std::wstring strAnimName = GetMonsterAnim();

		if (strAnimName != strCurAnim)
		{
			SetMonsterAnim(strCurAnim);
			GetComponent<Animator>()->Play(strCurAnim, true);
		}

		Monster::LateUpdate();
	}
	void DemianPhase2::Render()
	{
		Monster::Render();
	}
	void DemianPhase2::add_skill()
	{
		SpawnMonsterAttack* pSpawnObj = new SpawnMonsterAttack();
		pSpawnObj->SetName(L"SpawnObj");
		pSpawnObj->SetOnwer(this);
		AddMonsterSkill(pSpawnObj);

		MonsterMoveAttack* pAttack0 = new MonsterMoveAttack();
		pAttack0->SetName(L"Demian2_attack0");
		pAttack0->SetOnwer(this);
		AddMonsterSkill(pAttack0);

		for (int i = 0; i < 20; ++i)
		{
			DemianFire1* pAttack1 = new DemianFire1();
			pAttack1->SetName(L"Demian_attack1");
			pAttack1->SetOnwer(this);
			AddMonsterSkill(pAttack1);
		}
		
		DemianSpear0* pAttack2 = new DemianSpear0();
		pAttack2->SetName(L"Demian2_attack2");
		pAttack2->SetOnwer(this);
		AddMonsterSkill(pAttack2);

		DemianSpear1* pAttack2_1 = new DemianSpear1();
		pAttack2_1->SetName(L"Demian2_attack2");
		pAttack2_1->SetOnwer(this);
		AddMonsterSkill(pAttack2_1);

		pAttack2 = new DemianSpear0();
		pAttack2->SetName(L"Demian2_attack2");
		pAttack2->SetOnwer(this);
		AddMonsterSkill(pAttack2);

		MonsterAttackObject* pAttack3 = new MonsterAttackObject();
		pAttack3->SetName(L"Demian2_attack3");
		pAttack3->SetOnwer(this);
		AddMonsterSkill(pAttack3);


		for (int i = 0; i < 30; ++i)
		{
			DemianFire2* pAttack4 = new DemianFire2();
			pAttack4->SetName(L"Demian2_attack4");
			pAttack4->SetOnwer(this);
			AddMonsterSkill(pAttack4);
		}
	}
	void DemianPhase2::setattack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		tMonsterAttack attack0 = {};
		attack0.vPosition = vPosition;
		attack0.vScale = Vector2(2.f, 2.f);
		attack0.vOffset = Vector2(0.f, 0.f);
		attack0.tAttackInfo.fAttackDamage = 30.f;

		attack0.tTime.fCoolTime = 1000.f;

		attack0.pFunction = std::bind(&DemianPhase2::attack0, this);
	
		attack0.iStartFrame = 6;
		attack0.iEndFrame = 9;

		Pscript->AddAttack(attack0);

		//2
		tMonsterAttack attack1 = {};
		attack1.bSkill = true;
		
		attack1.tTime.fCoolTime = 10000.f;
		attack1.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();
		
		attack1.pFunction = std::bind(&DemianPhase2::attack1, this);
		
		attack1.iStartFrame = 7;
		attack1.iEndFrame = 64;
		
		Pscript->AddAttack(attack1);
		
		//3
		tMonsterAttack attack2 = {};
		attack2.bSkill = true;
		
		attack2.tTime.fCoolTime = 1000000.f;
		
		attack2.pFunction = std::bind(&DemianPhase2::attack2, this);
		
		attack2.iStartFrame = 11;
		attack2.iEndFrame = 12;
		Pscript->AddAttack(attack2);
		
		////
		////
		//tMonsterAttack attack3 = {};
		//attack3.vPosition = vPosition;
		//attack3.vScale = Vector2(3.f, 2.f);
		//attack3.vOffset = Vector2(4.f, 0.f);
		//attack3.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();
		//attack3.tTime.fCoolTime = 5.f;
		//
		//attack3.pFunction = std::bind(&DemianPhase2::attack3, this);
		//
		//attack3.iStartFrame = 35;
		//attack3.iEndFrame = 39;
		//Pscript->AddAttack(attack3);

		tMonsterAttack attack4 = {};
		attack4.bSkill = true;
		attack4.tTime.fCoolTime = 5.f;
		//attack4.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();
		
		attack4.pFunction = std::bind(&DemianPhase2::attack4, this);
		
		attack4.iStartFrame = 11;
		attack4.iEndFrame = 64;
		Pscript->AddAttack(attack4);
		//
		//
		tMonsterAttack attack5 = {};
		attack5.bSkill = true;
		attack5.tTime.fCoolTime = 5.f;
		
		attack5.pFunction = std::bind(&DemianPhase2::attack4, this);
		attack5.iStartFrame = 3;
		//attack5.iEndFrame = 113;
		Pscript->AddAttack(attack5);
	}
	void DemianPhase2::attack0()
	{
		Effect* pEffect =  BattleManager::GetEffect(L"DemianAttack0Effect");
		EventManager::CreateObject(pEffect, eLayerType::Effect);
		pEffect->SetActive(true);
		pEffect->StartEffect(GetDir());
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		pEffect->GetComponent<Transform>()->SetPosition(vPosition);

		MonsterAttackObject* attack0 = GetMonsterSkill(L"Demian2_attack0");
		if (attack0 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack0);
		EventManager::CreateObject(attack0, eLayerType::MonsterAttack);
	}
	void DemianPhase2::attack1()
	{
		MonsterAttackObject* attack1 = GetMonsterSkill(L"SpawnObj");
		if (attack1 == nullptr)
			return;
		SpawnMonsterAttack* pSpawn = dynamic_cast<SpawnMonsterAttack*>(attack1);
		//��ġ �ʱ�ȭ
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		pSpawn->GetComponent<Transform>()->SetPosition(vPosition);

		pSpawn->Initialize();

		//�ӵ�, ���� ��ġ ����
		Vector2 vLook[4] = { Vector2{3.f, 0.f},Vector2{3.f, 0.f},Vector2{-3.f, 0.f},
		Vector2{-3.f, 0.f} };
		Vector3 vOffset[4] = { Vector3{0.f, 0.7f,0.f},Vector3{0.f, -0.7f,0.f},Vector3{0.f, 0.7f,0.f},
		Vector3{0.f, -0.7f,0.f} };

		for (int i = 0; i < 4; ++i)
			pSpawn->SetVelocity(vLook[i], vOffset[i]);
			

		//spawn ��ü���� ���� ��� ��������
		pSpawn->SetTime(1.5f);
		pSpawn->SetAttackName(L"Demian_attack1");
		pSpawn->SetCreateCount(4);
		pSpawn->SetEndFrame(64);

		EventManager::CreateObject(pSpawn, eLayerType::MonsterAttack);
	}
	void DemianPhase2::attack2()
	{
		Effect* pEffect = BattleManager::GetEffect(L"DemianClone0");
		EventManager::CreateObject(pEffect, eLayerType::Effect);
		pEffect->SetActive(true);
		pEffect->StartEffect(GetDir());

		//���
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.x += (m_iSpearCount * GetDir());
		pEffect->GetComponent<Transform>()->SetPosition(vPosition);
	}
	void DemianPhase2::attack3()
	{
		MonsterAttackObject* attack2 = GetMonsterSkill(L"Demian2_attack3");
		if (attack2 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack2);

		EventManager::CreateObject(attack2, eLayerType::MonsterAttack);
	}
	void DemianPhase2::attack4()
	{
		MonsterAttackObject* attack2 = GetMonsterSkill(L"SpawnObj");
		if (attack2 == nullptr)
			return;
		SpawnMonsterAttack* pSpawn = dynamic_cast<SpawnMonsterAttack*>(attack2);
		//��ġ �ʱ�ȭ
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.y += 3.4;
		pSpawn->GetComponent<Transform>()->SetPosition(vPosition);

		pSpawn->Initialize();

		//�ӵ� ����
		Vector2 vLook[5] = { Vector2{0.8f,-0.8f}, Vector2{0.45f,-0.45f} , Vector2{0,-1.f},
			Vector2{-0.5f,-0.5f},Vector2{-0.8f,-0.8f} };
		for (int i = 0; i < 5; ++i)
			pSpawn->SetVelocity(vLook[i]);

		//spawn ��ü���� ���� ��� ��������
		pSpawn->SetTime(1.7f);
		pSpawn->SetAttackName(L"Demian2_attack4");
		pSpawn->SetCreateCount(5);
		pSpawn->SetEndFrame(113);
		EventManager::CreateObject(pSpawn, eLayerType::MonsterAttack);
	}

	void DemianPhase2::attack5()
	{

	}

	void DemianPhase2::check_HP()
	{
		MonsterScript* pScript = GetScript<MonsterScript>();
		const tObjectInfo& tInfo = pScript->GetObjectInfo();

		//�����
		if (tInfo.fHP / tInfo.fMaxHP <= 0.15f)
			pScript->AciveAttack(5);
	}
	void DemianPhase2::create_spear0()
	{
		//��
		++m_iSpearCount;
		MonsterAttackObject* attack2 = GetMonsterSkill(L"Demian2_attack2");
		if (attack2 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		EventManager::CreateObject(attack2, eLayerType::MonsterAttack);

		//spear
		Vector3 vSpearPosition = GetComponent<Transform>()->GetPosition();
		vSpearPosition.x += (m_iSpearCount * GetDir() / 0.5f);
		attack2->GetComponent<Transform>()->SetPosition(vSpearPosition);
		attack2->Initialize();

		//clone ����
		if (m_iSpearCount >= 3)
		{
			m_iSpearCount = 0;
			return;
		}
		Effect* pEffect = BattleManager::GetEffect(L"DemianClone1");
		EventManager::CreateObject(pEffect, eLayerType::Effect);
		pEffect->SetActive(true);
		pEffect->StartEffect(GetDir());

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.x += (m_iSpearCount * GetDir());
		pEffect->GetComponent<Transform>()->SetPosition(vPosition);
	}

	void DemianPhase2::create_spear1()
	{
		//�Ʒ�
		++m_iSpearCount;

		MonsterAttackObject* attack2 = GetMonsterSkill(L"Demian2_attack2");
		if (attack2 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		EventManager::CreateObject(attack2, eLayerType::MonsterAttack);

		Vector3 vSpearPosition = GetComponent<Transform>()->GetPosition();
		vSpearPosition.x += (m_iSpearCount * GetDir() / 0.5f);
		attack2->GetComponent<Transform>()->SetPosition(vSpearPosition);
		attack2->Initialize();

		//clone ����
		if (m_iSpearCount >= 3)
		{
			m_iSpearCount = 0;
			return;
		}

		Effect* pEffect = BattleManager::GetEffect(L"DemianClone0");
		EventManager::CreateObject(pEffect, eLayerType::Effect);
		pEffect->SetActive(true);
		pEffect->StartEffect(GetDir());

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.x += (m_iSpearCount * GetDir());
		pEffect->GetComponent<Transform>()->SetPosition(vPosition);

	}
	void DemianPhase2::set_effect()
	{
		Effect* pClone1 = new Effect();
		pClone1->GetComponent<Transform>()->SetScale(Vector3(18.f, 18.f, 0.f));
		pClone1->SetName(L"DemianClone0");
		pClone1->CreateAnimation(Resources::Find<Texture>(L"demianClone0"), Vector2(0.f, 0.f), Vector2(515.f, 318.f), 8, 1, Vector2(2000.f, 2000.f), Vector2(0.f, 0.f), 0.1f);
		pClone1->SetFunction(std::bind(&DemianPhase2::create_spear0, this), 1);

		Effect* pClone2 = new Effect();
		pClone2->GetComponent<Transform>()->SetScale(Vector3(18.f, 18.f, 0.f));
		pClone2->SetName(L"DemianClone1");
		pClone2->CreateAnimation(Resources::Find<Texture>(L"demianClone1"), Vector2(0.f, 0.f), Vector2(679.f, 542.f), 8, 1, Vector2(1800.f, 1800.f), Vector2(0.f, 0.f), 0.1f);
		pClone2->SetFunction(std::bind(&DemianPhase2::create_spear1, this), 1);

		pClone1 = new Effect();
		pClone1->GetComponent<Transform>()->SetScale(Vector3(18.f, 18.f, 0.f));
		pClone1->SetName(L"DemianClone0");
		pClone1->CreateAnimation(Resources::Find<Texture>(L"demianClone0"), Vector2(0.f, 0.f), Vector2(515.f, 318.f), 8, 1, Vector2(2000.f, 2000.f), Vector2(0.f, 0.f), 0.1f);
		pClone1->SetFunction(std::bind(&DemianPhase2::create_spear0, this), 1);
	}

	void DemianPhase2::move()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.x += (GetDir() * 4.38f);
		GetComponent<Transform>()->SetPosition(vPosition);
	}
	
}