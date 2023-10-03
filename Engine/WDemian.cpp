#include "WDemian.h"
#include "WResources.h"
#include "WRigidbody.h"
#include "WMonsterScript.h"
#include "WMonsterMove.h"
#include "WMonsterStand.h"
#include "WMonsterAttack.h"
#include "WMonsterFSM.h"
#include "WMonsterDead.h"
#include "WRigidbody.h"
#include "WAnimator.h"
#include "WEventManager.h"
namespace W
{
	Demian::Demian():
		m_strLevel(L"0")
	{
		SetName(L"Demian");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"DemianMater", pMater);

		pRenderer->SetMaterial(pMater);
		AddComponent<Rigidbody>();

		std::shared_ptr<Texture> pNormal =
			Resources::Load<Texture>(L"DemianNormal", L"..\\Resources\\Texture\\Monster\\demian\\stand.png");
		std::shared_ptr<Texture> pAttack0 =
			Resources::Load<Texture>(L"Demian_attack0", L"..\\Resources\\Texture\\Monster\\demian\\attack0.png");
		std::shared_ptr<Texture> pAttack1 =
			Resources::Load<Texture>(L"Demian_attack1", L"..\\Resources\\Texture\\Monster\\demian\\attack1.png");
		std::shared_ptr<Texture> pAttack2 =
			Resources::Load<Texture>(L"Demian_attack2", L"..\\Resources\\Texture\\Monster\\demian\\attack2.png");
		std::shared_ptr<Texture> pAttack3 =
			Resources::Load<Texture>(L"Demian_attack3", L"..\\Resources\\Texture\\Monster\\demian\\attack3.png");

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"stand_left", pNormal, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"attack0_left", pAttack0, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack0_left")->Create(L"attack0_left",pAttack0, Vector2(0.f, 2000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack0_left")->Create(L"attack0_left", pAttack0, Vector2(0.f, 4000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack0_left")->Create(L"attack0_left", pAttack0, Vector2(0.f, 6000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack0_left")->Create(L"attack0_left", pAttack0, Vector2(0.f, 8000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"attack1_left", pAttack1, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_left")->Create(L"attack1_left", pAttack1, Vector2(0.f, 2000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_left")->Create(L"attack1_left", pAttack1, Vector2(0.f, 4000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_left")->Create(L"attack1_left", pAttack1, Vector2(0.f, 6000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_left")->Create(L"attack1_left", pAttack1, Vector2(0.f, 8000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_left")->Create(L"attack1_left", pAttack1, Vector2(0.f, 10000.f), Vector2(2000.f, 2000.f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"attack2_left", pAttack2, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_left")->Create(L"attack2_left", pAttack2, Vector2(0.f, 2000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_left")->Create(L"attack2_left", pAttack2, Vector2(0.f, 4000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_left")->Create(L"attack2_left", pAttack2, Vector2(0.f, 6000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_left")->Create(L"attack2_left", pAttack2, Vector2(0.f, 8000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_left")->Create(L"attack2_left", pAttack2, Vector2(0.f, 10000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_left")->Create(L"attack2_left", pAttack2, Vector2(0.f, 12000.f), Vector2(2000.f, 2000.f), 2, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"attack3_left", pAttack3, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack3_left")->Create(L"attack3_left", pAttack3, Vector2(0.f, 2000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack3_left")->Create(L"attack3_left", pAttack3, Vector2(0.f, 4000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack3_left")->Create(L"attack3_left", pAttack3, Vector2(0.f, 6000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack3_left")->Create(L"attack3_left", pAttack3, Vector2(0.f, 8000.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"stand_right", pNormal, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		
		pAnim->Create(L"attack0_right", pAttack0, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack0_right")->Create(L"attack0_right", pAttack0, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack0_right")->Create(L"attack0_right", pAttack0, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack0_right")->Create(L"attack0_right", pAttack0, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack0_right")->Create(L"attack0_right", pAttack0, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"attack1_right", pAttack1, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_right")->Create(L"attack1_right", pAttack1, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_right")->Create(L"attack1_right", pAttack1, Vector2(12000.f, 4000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_right")->Create(L"attack1_right", pAttack1, Vector2(12000.f, 6000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_right")->Create(L"attack1_right", pAttack1, Vector2(12000.f, 8000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_right")->Create(L"attack1_right", pAttack1, Vector2(12000.f, 10000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack1_right")->Create(L"attack1_right", pAttack1, Vector2(12000.f, 12000.f), Vector2(-2000.f, 2000.f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"attack2_right", pAttack2, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_right")->Create(L"attack2_right", pAttack2, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_right")->Create(L"attack2_right", pAttack2, Vector2(12000.f, 4000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_right")->Create(L"attack2_right", pAttack2, Vector2(12000.f, 6000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_right")->Create(L"attack2_right", pAttack2, Vector2(12000.f, 8000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_right")->Create(L"attack2_right", pAttack2, Vector2(12000.f, 10000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack2_right")->Create(L"attack2_right", pAttack2, Vector2(12000.f, 12000.f), Vector2(-2000.f, 2000.f), 2, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"attack3_right", pAttack3, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack3_right")->Create(L"attack3_right", pAttack3, Vector2(12000.f, 2000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack3_right")->Create(L"attack3_right", pAttack3, Vector2(12000.f, 4000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack3_right")->Create(L"attack3_right", pAttack3, Vector2(12000.f, 6000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"attack3_right")->Create(L"attack3_right", pAttack3, Vector2(12000.f, 8000.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"stand_left", true);
		
	}
	Demian::~Demian()
	{

	}
	void Demian::Initialize()
	{
		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		GetComponent<Transform>()->SetPosition(0.1f, -1.f, -1.5f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.16f, 0.16f));
		pCollider->SetCenter(Vector2(0.f, -0.7f));

		MonsterScript* Pscript = AddComponent<MonsterScript>();
		Pscript->SetBoss();
		Pscript->Initialize();
		Pscript->CreateHP();

		//setattack();
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
	void Demian::Update()
	{
		Monster::Update();
	}
	void Demian::LateUpdate()
	{
		Monster::LateUpdate();
	}
	void Demian::Render()
	{
		Monster::Render();
	}
	void Demian::add_skill()
	{
		for (int i = 0; i < 4; ++i)
		{

		}
	}
	void Demian::setattack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		tMonsterAttack attack0 = {};
		attack0.tTime.fCoolTime = 15.f;

		attack0.vScale = Vector2(2.5f, 1.f);
		attack0.vOffset = Vector2(0.f, -1.5f);
		attack0.vPosition = vPosition;
		attack0.tAttackInfo.fAttackDamage = 10.f;
		attack0.pFunction = std::bind(&Demian::attack0, this);

		attack0.iStartFrame = 18;
		attack0.iEndFrame = 23;

		Pscript->AddAttack(attack0);

		//2
		tMonsterAttack attack1 = {};
		attack1.bSkill = true;

		attack1.tTime.fCoolTime = 20.f;
		attack1.vScale = Vector2(3.f, 3.f);

		attack1.pFunction = std::bind(&Demian::attack1, this);

		attack1.iStartFrame = 12;
		attack1.iEndFrame = 13;

		Pscript->AddAttack(attack1);

		////3
		tMonsterAttack attack2 = {};
		attack2.vPosition = vPosition;
		attack2.vScale = Vector2(3.f, 2.f);
		attack2.vOffset = Vector2(0.f, -1.f);
		attack2.tTime.fCoolTime = 10.f;

		attack2.pFunction = std::bind(&Demian::attack2, this);

		attack2.iStartFrame = 15;
		attack2.iEndFrame = 18;
		Pscript->AddAttack(attack2);

		//
		//
		tMonsterAttack attack3 = {};
		attack3.bSkill = true;
		attack3.tTime.fCoolTime = 15.f;
		//attack4.tTime.fCurTime = 5.f;

		attack3.vScale = Vector2(0.f, 0.f);
		attack3.pFunction = std::bind(&Demian::attack3, this);

		attack3.iStartFrame = 27;
		attack3.iEndFrame = 37;
		Pscript->AddAttack(attack3);
		
	}
	void Demian::chanage_level()
	{
		m_strLevel = L"1";
	}
	void Demian::attack0()
	{
		for (int i = 0; i < 4; ++i)
		{
			MonsterAttackObject* attack0 = GetMonsterSkill(L"Demian_attack0");
			if (attack0 == nullptr)
				return;
			MonsterScript* pMonsterScript = GetScript<MonsterScript>();
			pMonsterScript->SetMonsterAttack(attack0);
			attack0->SetOnwer(this);

			EventManager::CreateObject(attack0, eLayerType::MonsterAttack);
		}
	}
	void Demian::attack1()
	{
	}
	void Demian::attack2()
	{
	}
	void Demian::attack3()
	{
	}
}