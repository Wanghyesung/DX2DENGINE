#include "WUltimateSkill.h"
#include "WResources.h"
#include "WEffect.h"
#include "WAttackScript.h"
#include "WPlayerAttackObject.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WEventManager.h"
#include "WBattleManager.h"
#include "WLight.h"
#include "WUltimateFog.h"
#include "WUltimateBackground.h"
#include "WSpawnUltimate.h"
#include "WUltimateShuriken.h"
namespace W
{
	UltimateSkill::UltimateSkill()
	{
		SetSkillType(Player::ePlayerSkill::ultimate);
		SetStateName(L"_alert");

		tSkillTime tTime = {};
		tTime.fCoolTime = 50.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		m_pEffectAtlas = Resources::Load<Texture>(L"ultimate0", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate0.png");
		Effect* pEffect = CreateEffet(m_pEffectAtlas, L"ultimateEffect0", Vector2(0.f, 0.f),
			Vector2(1456.f, 860.f), 10, 5, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.13f);
		pEffect->SetFunction(std::bind(&UltimateSkill::activeskill_ultimate, this),24);
		

		
		Resources::Load<Texture>(L"UltiShuriken", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\s1.png");
	}
	UltimateSkill::~UltimateSkill()
	{

	}
	void UltimateSkill::Update()
	{
		if (m_bCreate)
			Exit();
	}
	void UltimateSkill::Initialize()
	{
		PlayerScript* pScript = GetPlayer()->GetScript<PlayerScript>();
		//처음 공격
		PlayerAttackObject* pAttackObj = new PlayerAttackObject();

		pAttackObj->SetName(L"ultimate0");
		pAttackObj->SetPlayer(GetPlayer());

		Collider2D* pCollider = pAttackObj->AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(15.f, 15.f));
		pScript->AddPlayerSkill(pAttackObj);

		//3.5초 동안 총 8번의 공격 공격당 7대
		pAttackObj->AddComponent<AttackScript>()->SetStayObject(7, 0.45f);
		pAttackObj->GetScript<AttackScript>()->SetDeleteTime(3.5f);
		pAttackObj->GetScript<AttackScript>()->SetAbleAttackCount(15);

		//이미지들
		UltimateBackground* pBackGround = new UltimateBackground();
		pBackGround->SetName(L"ultimate1");
		pBackGround->SetPlayer(GetPlayer());
		pBackGround->Initialize();
		pScript->AddPlayerSkill(pBackGround);

		UltimateFog* pFog = new UltimateFog();
		pFog->SetPlayer(GetPlayer());
		pFog->SetName(L"ultimate2");
		pFog->Initialize();
		pScript->AddPlayerSkill(pFog);

		SpawnUltimate* spawn = new SpawnUltimate();
		spawn->SetPlayer(GetPlayer());
		spawn->SetName(L"ultimate_spawn");
		spawn->Initialize();
		pScript->AddPlayerSkill(pFog);

		for (int i = 0; i < 15; ++i)
		{
			UltimateShuriken* pShuriken = new UltimateShuriken();
			pShuriken->SetPlayer(GetPlayer());
			pShuriken->SetName(L"ultimate_suriken");
			pShuriken->Initialize();
			pScript->AddPlayerSkill(pShuriken);

			const tAttackInfo& Attack = GetPlayer()->GetScript<PlayerScript>()->GetAttackInfo();

			tAttackInfo AttackInfo;
			AttackInfo.fAttackDamage = 2.f;
			AttackInfo.fAttack = Attack.fAttack;
			AttackInfo.fDex = Attack.fDex;

			AttackInfo.fAttRcnt = 0.3f;
			AttackInfo.fAttRigidityTime = 0.3f;
			AttackInfo.fAttUpperRcnt = 0.f;

			//7번 공격
			AttackInfo.iDamageCount = 15;

			pShuriken->GetScript<AttackScript>()->SetAttackInfo(AttackInfo);
		}
	}
	void UltimateSkill::Enter()
	{
		if (GetPlayer()->GetCurPlayerState() == Player::ePlayerState::ladder)
		{
			Exit();
			return;
		}
		SkillState::Enter();
	
		m_bCreate = false;

		Effect* pEffect = BattleManager::GetEffect(L"ultimateEffect0");
		StartEffect(pEffect);
	}
	void UltimateSkill::Exit()
	{
		SkillState::Exit();
	}
	void UltimateSkill::activeskill_ultimate()
	{
		PlayerAttackObject* pAttackObj = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"ultimate0");
		pAttackObj->GetScript<AttackScript>()->SetDeleteObject(false);

		Transform* pTr = pAttackObj->GetComponent<Transform>();
		pTr->SetPosition(Vector3(0.f,0.f,-4.f));

		const tAttackInfo& Attack = GetPlayer()->GetScript<PlayerScript>()->GetAttackInfo();

		tAttackInfo AttackInfo;
		AttackInfo.fAttackDamage = 2.f;
		AttackInfo.fAttack = Attack.fAttack;
		AttackInfo.fDex = Attack.fDex;

		AttackInfo.fAttRcnt = 0.3f;
		AttackInfo.fAttRigidityTime = 0.3f;
		AttackInfo.fAttUpperRcnt = 0.f;

		//7번 공격
		AttackInfo.iDamageCount = 15;

		pAttackObj->GetScript<AttackScript>()->SetAttackInfo(AttackInfo);
		EventManager::CreateObject(pAttackObj, eLayerType::AttackObject);

		m_bCreate = true;

		create_shuriken();
	}
	void UltimateSkill::create_shuriken()
	{
		
	}
}