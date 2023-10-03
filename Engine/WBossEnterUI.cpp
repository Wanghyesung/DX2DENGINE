#include "WBossEnterUI.h"
#include "WEventManager.h"

namespace W
{
	BossEnterUI::BossEnterUI():
		m_bDown(false)
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"BossEnterUI0", L"..\\Resources\\Texture\\UI\\MonsterUI\\move0.png");
		pTex = Resources::Load<Texture>(L"BossEnterUI1", L"..\\Resources\\Texture\\UI\\MonsterUI\\move1.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"MonsterUITexMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(7.f * 0.3f, 3.f * 0.3f, -0.1f);

	}
	BossEnterUI::~BossEnterUI()
	{

	}
	void BossEnterUI::Initialize()
	{

	}
	void BossEnterUI::Update()
	{
		UI::Update();
	}
	void BossEnterUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void BossEnterUI::Render()
	{
		UI::Render();
	}
	void BossEnterUI::MouseOn()
	{
		std::shared_ptr<Texture> pTex;
		if (m_bDown)
			pTex = Resources::Find<Texture>(L"BossEnterUI0");
		else
			pTex = Resources::Find<Texture>(L"BossEnterUI1");

		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(pTex);
	}
	void BossEnterUI::MouseLbtnDown()
	{
		m_bDown = true;
	}
	void BossEnterUI::MouseLbtnUp()
	{

	}
	void BossEnterUI::MouseLbtnClicked()
	{
		m_bDown = false;
		
		EventManager::ChangeScene(m_strNextScene);
	}
	void BossEnterUI::set_nextscene(BossUI::eBossUnber _eNumber)
	{
		switch (_eNumber)
		{
		case W::BossUI::eBossUnber::Horntail:
			m_strNextScene = L"Cave";
			break;
		case W::BossUI::eBossUnber::PinkBean:
			m_strNextScene = L"TempleBoss";
			break;
		case W::BossUI::eBossUnber::Magnus:
			m_strNextScene = L"Helisium";
			break;
		case W::BossUI::eBossUnber::Demian:
			m_strNextScene = L"";
			break;
		}
	}
}