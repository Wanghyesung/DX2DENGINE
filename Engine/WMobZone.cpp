#include "WMobZone.h"
#include "WRenderer.h"
#include "WResources.h"
#include "WPlayer.h"
#include "WSceneManger.h"
#include "WMonster.h"
#include "WBattleManager.h"
#include "WPlayerScript.h"
#include "WAnimator.h"
#include "WInfo.h"
namespace W
{
	MobZone::MobZone():
		m_pTarget(nullptr),
		m_pMonster(nullptr),
		m_iCurLevel(0),
		m_tAttackInfo{}
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"MobZoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);

		Resources::Load<Texture>(L"Megnus_Zone0", L"..\\Resources\\Texture\\Monster\\megnus\\mobzon1.png");
		Resources::Load<Texture>(L"Megnus_Zone1", L"..\\Resources\\Texture\\Monster\\megnus\\mobzon2.png");
		Resources::Load<Texture>(L"Megnus_Zone2", L"..\\Resources\\Texture\\Monster\\megnus\\mobzon3.png");
		Resources::Load<Texture>(L"Megnus_Zone3", L"..\\Resources\\Texture\\Monster\\megnus\\mobzon4.png");

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Megnus_Zone0");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Megnus_Zone0", pAtlas, Vector2(0.0f, 0.0f), Vector2(796.f, 852.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		
		pAnim->Play(L"Megnus_Zone0", true);
	}
	MobZone::~MobZone()
	{

	}
	void MobZone::Initialize()
	{
		m_tAttackInfo.fAttackDamage = 10.f;
		m_tAttackInfo.fAttRcnt = 0.f;//����
		m_tAttackInfo.fAttUpperRcnt = 0.f;

		m_vecLength.push_back(3.f);
		m_vecLength.push_back(2.5f);
		m_vecLength.push_back(2.f);
		m_vecLength.push_back(1.5f);

	}
	void MobZone::Update()
	{
		Vector3 vPosition = m_pMonster->GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(vPosition);

		m_pTarget = dynamic_cast<Player*>(SceneManger::FindPlayer());
		if (m_pTarget &&
			m_pTarget->GetState() == GameObject::eState::Active)
		{
			float fPlayerX = m_pTarget->GetComponent<Transform>()->GetPosition().x;
			float fX = GetComponent<Transform>()->GetPosition().x;

			float fLen = fPlayerX - fX;
			if (fLen >= m_vecLength[m_iCurLevel])
				m_pTarget->GetScript<PlayerScript>()->Hit(m_tAttackInfo,L"MobZone");
		}
		GameObject::Update();
	}
	void MobZone::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MobZone::Render()
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
}