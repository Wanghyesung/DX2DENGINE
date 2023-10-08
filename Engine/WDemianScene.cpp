#include "WDemianScene.h"
#include "WResources.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WGround.h"
#include "WDemian.h"
#include "WCollisionManager.h"
#include "WDemianPhase2.h"
#include "WSharHP.h"
#include "WMonsterScript.h"
#include "WWhite.h"
#include "WEventManager.h"
namespace W
{
	DemianScene::DemianScene():
		m_pWhite(nullptr),
		m_bEnd(false),
		m_iFadeCallStack(1)
	{
		SetMapSize(-1.9f, -1.f, 1.9f, -1.f);
		SetMapPossibleSize(-8.9f, 8.9f);

		std::shared_ptr<Texture> pTempleBossTex =
			Resources::Load<Texture>(L"DemianBossScene", L"..\\Resources\\Texture\\background\\demain_back.png");
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pMater->SetTexture(pTempleBossTex);
		Resources::Insert(L"DemianBackMater", pMater);

		m_pWhite = new White();
		m_pWhite->SetEndTime(2.f);
		m_pWhite->SetFunction(std::bind(&DemianScene::phase2, this));
	}
	DemianScene::~DemianScene()
	{
		if (!m_bEnd)
		{
			delete m_pWhite;
			m_pWhite = nullptr;
		}
	}
	void DemianScene::Initialize()
	{
		CreateBackground();

		create_monster();
		{
			GameObject* pCamera = new GameObject();
			pCamera->SetName(L"ObjCam");
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::UI, false);
			pCamera->AddComponent<CameraScript>();
		}

		//ui camera
		{
			GameObject* pUICamera = new GameObject();
			pUICamera->SetName(L"UICam");
			AddGameObject(eLayerType::Camera, pUICamera);
			pUICamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pUICamera->AddComponent<Camera>();
			pCameraComp->TurnUILayerMask();//UI만 그리게
			//pCamera->AddComponent<CameraScript>();
		}

		m_pSharHP = new SharHP();
		AddGameObject(eLayerType::UI, m_pSharHP);
		m_pSharHP->Initialize();
	}
	void DemianScene::Update()
	{
		float fRatio = 0.f;
		float fMaxHP = 0.f;
		float fHP = 0.f;

		const std::vector<GameObject*>& vecMonster =
			GetLayer(eLayerType::Monster).GetGameObjects();
		
		for (UINT i = 0; i < vecMonster.size(); ++i)
		{
			if (vecMonster[0]->GetState() == GameObject::eState::Paused)
			{
				if (m_iFadeCallStack == 1 &&
					dynamic_cast<Demian*>(vecMonster[0]))
				{
					fadein();
				}
			}
				
			const tObjectInfo& tInfo = vecMonster[i]->GetScript<MonsterScript>()->GetObjectInfo();

			fMaxHP += tInfo.fMaxHP;
			fHP += tInfo.fHP;
		}

		fRatio = (fHP / fMaxHP) * 100.f;
		m_pSharHP->SetHPValue(fRatio);

		Scene::Update();
	}
	void DemianScene::LateUpdate()
	{
		Scene::LateUpdate();

	}
	void DemianScene::Render()
	{
		Scene::Render();

	}
	void DemianScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::AttackObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
		CollisionManager::SetLayer(eLayerType::Ground, eLayerType::MonsterAttack, true);

		m_bEnd = false;
		m_iFadeCallStack = 1;
	}
	void DemianScene::OnExit()
	{
		CollisionManager::Clear();
	}
	void DemianScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"DemianBackMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.2372f * 8.f, 1.f * 8.f, 1.f);


		Ground* pGround = new Ground(true);
		AddGameObject(eLayerType::Ground, pGround);
		pGround->GetComponent<Transform>()->SetPosition(0.f, -2.95f, -0.1f);
		pGround->GetComponent<Transform>()->SetScale(4.3f * 7.f, 1.f * 0.3f, 0.f);
	}

	void DemianScene::fadein()
	{
		m_bEnd = true;
		m_iFadeCallStack = 0;
		m_pWhite->Initialize();
		EventManager::CreateObject(m_pWhite, eLayerType::Object);
	}
	void DemianScene::phase2()
	{
		m_bEnd = false;
		const std::vector<GameObject*>& vecGameObj =
			GetLayer(eLayerType::Monster).GetGameObjects();

		//phase2 데미안
		vecGameObj[1]->GetComponent<Collider2D>()->SetActive(true);
		vecGameObj[1]->SetState(GameObject::eState::Active);
	}

	void DemianScene::create_monster()
	{
		Demian* pDemian = new Demian();
		pDemian->Initialize();
		AddGameObject(eLayerType::Monster, pDemian);

		DemianPhase2* pDemian2 = new DemianPhase2();
		pDemian2->Initialize();
		AddGameObject(eLayerType::Monster, pDemian2);
		pDemian2->GetComponent<Collider2D>()->SetActive(false);
		pDemian2->SetState(GameObject::eState::Paused);
	}
}