#include "WMonsterUI.h"
#include "WResources.h"

namespace W
{
	UINT MonsterUI::COUNT = 0;

	MonsterUI::MonsterUI():
		m_iCount(COUNT),
		m_eBossNumber(BossUI::eBossUnber::None),
		m_bSelete(false)
	{
		++COUNT;
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		//pMater->SetTexture(pTex);
		std::wstring strNum = std::to_wstring(m_iCount);
		Resources::Insert(L"MonsterUIMater" + strNum, pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);

		//off
		Resources::Load<Texture>(L"BossUI00", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete0_0.png");
		Resources::Load<Texture>(L"BossUI10", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete1_0.png");
		Resources::Load<Texture>(L"BossUI20", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete2_0.png");
		Resources::Load<Texture>(L"BossUI30", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete3_0.png");

		//on
		Resources::Load<Texture>(L"BossUI01", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete0_1.png");
		Resources::Load<Texture>(L"BossUI11", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete1_1.png");
		Resources::Load<Texture>(L"BossUI21", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete2_1.png");
		Resources::Load<Texture>(L"BossUI31", L"..\\Resources\\Texture\\UI\\MonsterUI\\selete3_1.png");

		GetComponent<Transform>()->SetPosition(-2.4f, 1.82f, 0.f);
		GetComponent<Transform>()->SetScale(2.f * 0.9f, 2.f * 0.2f, 0.f);
	}
	MonsterUI::~MonsterUI()
	{

	}
	void MonsterUI::Initialize()
	{

	}
	void MonsterUI::Update()
	{
		UI::Update();
	}
	void MonsterUI::LateUpdate()
	{
		UI::LateUpdate();

	}
	void MonsterUI::Render()
	{
		UI::Render();

	}
	void MonsterUI::MouseOn()
	{
		std::wstring strSelete;
		if (m_bSelete)
			strSelete = L"1";
		else
			strSelete = L"0";

		std::wstring strBossNum = std::to_wstring((UINT)m_eBossNumber);
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"BossUI" + strBossNum + strSelete);

		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(pTex);
	}
	void MonsterUI::MouseLbtnDown()
	{
		m_bSelete = true;
	}
	void MonsterUI::MouseLbtnUp()
	{
	}
	void MonsterUI::MouseLbtnClicked()
	{
		m_bSelete = false;
	}

	void MonsterUI::set_bossnumber(BossUI::eBossUnber _eNumber)
	{
		m_eBossNumber = _eNumber;
		clear();
	}

	void MonsterUI::clear()
	{
		std::wstring strBossNum = std::to_wstring((UINT)m_eBossNumber);
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"BossUI" + strBossNum + L"0");

		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(pTex);
	}
	
}