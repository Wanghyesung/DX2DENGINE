#include "WDemianCircle.h"
#include "WRenderer.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WRigidbody.h"
#include "WPlayerScript.h"
#include "WMonsterAttackScript.h"
namespace W
{
	DemianCircle::DemianCircle():
		m_bEnter(false),
		m_bActive(false),
		m_pTarget(nullptr),
		m_iCurIndex(0)
	{
		AddComponent<Rigidbody>();

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"DemianCircleMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		Collider2D* pCollider = GetComponent<Collider2D>();
		pCollider->SetActive(false);

		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"DemianCircle");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"level0", pAtlas, Vector2(0.0f, 0.0f), Vector2(260.f, 272.0f), 12, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"level1", pAtlas, Vector2(0.0f, 272.0f), Vector2(361.f, 374.0f), 12, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"level2", pAtlas, Vector2(0.0f, 666.f), Vector2(431.f, 449.0f), 12, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"level0", true);
	}

	DemianCircle::~DemianCircle()
	{

	}
	void DemianCircle::Initialize()
	{
		m_vecColliderSize.push_back(Vector2(0.06f, 0.06f));
		m_vecColliderSize.push_back(Vector2(0.08f, 0.08f));
		m_vecColliderSize.push_back(Vector2(0.1f, 0.1f));

		m_bActive = true;

		Vector3 vPosition = Vector3(0.1f, -1.85f, -1.5f);
		GetComponent<Transform>()->SetPosition(vPosition);

		m_tMonsterAttack.vPosition = vPosition;
		m_tMonsterAttack.vScale = m_vecColliderSize[0];

		m_tMonsterAttack.tAttackInfo.fAttackDamage = 3;
		m_tMonsterAttack.tAttackInfo.fAttRcnt = 0.f;//¸ÂÀ¸
		m_tMonsterAttack.tAttackInfo.fAttUpperRcnt = 0.f;

		
		SetMonsterAttack(m_tMonsterAttack);
	}
	void DemianCircle::Update()
	{
		check_enter();

		move();

		GameObject::Update();
	}
	void DemianCircle::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianCircle::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void DemianCircle::LevelUp(UINT _iLevel)
	{
		GetComponent<Collider2D>()->SetSize(m_vecColliderSize[_iLevel]);

		m_iCurIndex = _iLevel;
		std::wstring strNum = std::to_wstring(m_iCurIndex);
		GetComponent<Animator>()->Play(L"level"+ strNum, true);
	}
	
	void DemianCircle::check_enter()
	{
		m_pTarget = SceneManger::FindPlayer();
		bool bEnter = GetScript< MonsterAttackScript>()->IsPlayerEnter();
		
		if (m_bEnter == bEnter)
			return;

		m_bEnter = bEnter;

		if (m_bEnter)
			BattleManager::Player_DeBuff_Attack(m_pTarget, BattleManager::eUpStatType::Defense, 9);

		else
			BattleManager::Player_DeBuff_Attack(m_pTarget, BattleManager::eUpStatType::Defense, -9);
	}
	void DemianCircle::move()
	{

	 	Vector3 vTargetPos = m_pTarget->GetComponent<Transform>()->GetPosition();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		float fLen = vTargetPos.x - vPosition.x;
		int iDir = fLen > 0.f ? 1 : -1;

		GetComponent<Rigidbody>()->AddForce(Vector2(iDir * 1.f, 0.f));
	}
}