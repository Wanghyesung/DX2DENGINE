#include "WSowrdExplode.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonsterAttackScript.h"
#include "WMonster.h"
namespace W
{
	SowrdExplode::SowrdExplode() :
		m_iCallCount(0),
		m_tMonsterAttack{}
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"FireMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		Collider2D* pCollider = GetComponent<Collider2D>();
		pCollider->SetActive(false);

		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"swordExplodeTex", L"..\\Resources\\Texture\\Monster\\demian\\swordexplode.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"start", pAtlas, Vector2(0.0f, 0.0f), Vector2(111.f, 110.0f), 30, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"explode", pAtlas, Vector2(0.0f, 0.0f), Vector2(111.f, 110.0f), 30, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->CompleteEvent(L"explode") = std::bind(&SowrdExplode::off, this);
		pAnim->Play(L"start", true);

	}

	SowrdExplode::~SowrdExplode()
	{

	}

	void SowrdExplode::Initialize()
	{
		m_tMonsterAttack.tAttackInfo.fAttackDamage = 10.f;

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = Vector2(0.6f, 0.6f);
		m_tMonsterAttack.vOffset = Vector2(0.f, -0.25f);

		m_tMonsterAttack.iStartFrame = 25;
		m_tMonsterAttack.iEndFrame = 27;
	}

	void SowrdExplode::Update()
	{
		GameObject::Update();
	}

	void SowrdExplode::LateUpdate()
	{
		Animation* pAnim = GetComponent<Animator>()->GetActiveAnimation();

		int iIndex = pAnim->GetCurIndex();
		if (iIndex >= m_tMonsterAttack.iStartFrame && m_iCallCount == 0)
		{
			m_iCallCount = 1;
			//���� �������� ������ ���� �ѱ��
			SetMonsterAttack(m_tMonsterAttack);
			GetComponent<Collider2D>()->SetActive(true);
		}

		if (m_iCallCount == 1 && iIndex >= m_tMonsterAttack.iEndFrame)
		{
			m_iCallCount = 2;
			GetComponent<Collider2D>()->SetActive(false);
		}

		GameObject::LateUpdate();
	}
	void SowrdExplode::Render()
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
	void SowrdExplode::off()
	{
		m_iCallCount = 0;
		SceneManger::Erase(this);
		GetOwner()->AddMonsterSkill(this);
	}
}