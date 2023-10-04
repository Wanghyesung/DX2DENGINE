#include "WDemianObject.h"
#include "WRigidbody.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WSceneManger.h"
#include "WMonster.h"
#include "WBattleManager.h"
#include "WTime.h"
namespace W
{
	DemianObject::DemianObject():
		m_bEnd(false),
		m_bMove(false),
		m_vTargetPos(Vector3::Zero),
		m_iMoveCount(5),
		m_fWaitTime(0.f)
	{
		m_vVelocity = Vector2(1.5f, 1.5f);
		AddComponent<Rigidbody>();
		AddComponent<Collider2D>()->SetActive(false);

		//기본적으로 제공하는 script를 제거하고 전용 script로

		GetComponent<Transform>()->SetScale(20.f, 20.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"MagnusStoneMater", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas
			= Resources::Find<Texture>(L"magnus_stone");
		pAnim->Create(L"stone_start", pAtlas, Vector2(0.0f, 0.0f), Vector2(350.0f, 350.0f), 7, Vector2(1100.f, 1100.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"stone_move", pAtlas, Vector2(0.0f, 350.0f), Vector2(350.0f, 350.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"stone_attack", pAtlas, Vector2(0.0f, 700.f), Vector2(350.0f, 350.0f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, 0.1f);

		pAnim->CompleteEvent(L"stone_start") = std::bind(&DemianObject::start, this);
		//pAnim->CompleteEvent(L"stone_attack") = std::bind(&DemianObject::attack, this);

		mr->SetMaterial(pMater);
	}
	DemianObject::~DemianObject()
	{
	}
	void DemianObject::Initialize()
	{
		m_tMonsterAttack.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = Vector2(0.12f, 0.12f);
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.f);
	}
	void DemianObject::Update()
	{
		if (check_position())
			set_target();
		else
			move();

		GameObject::Update();
	}
	void DemianObject::LateUpdate()
	{
		Animator* pAnimator = GetComponent<Animator>();

		std::wstring strState = L"_start";

		if (m_bEnd)
			strState = L"_attack";

		else if (m_bMove)
			strState = L"_move";


		std::wstring strAnim = L"stone" + strState;

		if (m_strCurAnim != strAnim)
		{
			m_strCurAnim = strAnim;
			pAnimator->Play(strAnim, true);
		}

		GameObject::LateUpdate();

	}
	void DemianObject::Render()
	{
		GameObject::Render();
	}
	void DemianObject::off()
	{
		SceneManger::Erase(this);
		GetOwner()->AddMonsterSkill(this);
	}
	void DemianObject::start()
	{
		m_bMove = true;
		SetMonsterAttack(m_tMonsterAttack);
	}
	
	void DemianObject::move()
	{
		if (0.f >= m_fWaitTime)
			GetComponent<Rigidbody>()->AddForce(m_vVelocity);

		m_fWaitTime -= Time::DeltaTime();
	}
	void DemianObject::set_target()
	{
		--m_iMoveCount;

		GameObject* pObj = SceneManger::FindPlayer();
		m_vTargetPos = pObj->GetComponent<Transform>()->GetPosition();
		Vector2 vTargetPos = Vector2(m_vTargetPos.x, m_vTargetPos.y);

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		Vector2 vPos = Vector2(vPosition.x, vPosition.y);

		Vector2 vDiff = m_vTargetPos - vPos;
		vDiff.Normalize();
		
		m_vVelocity *= vDiff;
	}
	bool DemianObject::check_position()
	{
		Vector3 vPos = GetComponent<Transform>()->GetPosition();
		vPos.z = 0.f;

		Vector3 vDiff = m_vTargetPos - vPos;
		if (fabs(vDiff.x) < 0.5f && fabs(vDiff.y) < 0.5f)
		{
			m_fWaitTime = 0.5f;

			return true;
		}
		return false;
	}
	void DemianObject::attack()
	{

	}
}