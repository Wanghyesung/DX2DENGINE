#include "WHelisiumBoss.h"
#include "WResources.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WCollisionManager.h"
#include "WGround.h"
#include "WMegnus.h"
namespace W
{
	HelisiumBoss::HelisiumBoss()
	{
		SetMapSize(-7.5f, -1.f, 7.5f, -1.f);
		SetMapPossibleSize(-14.f, 14.f);

		std::shared_ptr<Texture> pTempleBossTex =
			Resources::Load<Texture>(L"HelisiumBoss", L"..\\Resources\\Texture\\background\\Helisium_boss.png");
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pMater->SetTexture(pTempleBossTex);
		Resources::Insert(L"HelisiumBossMater", pMater);
	}
	HelisiumBoss::~HelisiumBoss()
	{

	}
	void HelisiumBoss::Initialize()
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
	}
	void HelisiumBoss::Update()
	{
		Scene::Update();
	}
	void HelisiumBoss::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void HelisiumBoss::Render()
	{
		Scene::Render();

	}
	void HelisiumBoss::OnEnter()
	{
		StartSound();

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ladder, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::AttackObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
		CollisionManager::SetLayer(eLayerType::Ground, eLayerType::MonsterAttack, true);

	}
	void HelisiumBoss::OnExit()
	{
		EndSound();
		CollisionManager::Clear();
	}
	void HelisiumBoss::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AudioSource* pAudio = pBackGround->AddComponent<AudioSource>();
		pAudio->SetClip(Resources::Load<AudioClip>(L"Helisiumsound", L"..\\Resources\\sound\\thefinalWar.mp3"));

		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"HelisiumBossMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(3.65f * 8.f, 1.f * 8.f, 1.f);


		Ground* pGround = new Ground(true);
		AddGameObject(eLayerType::Ground, pGround);
		pGround->GetComponent<Transform>()->SetPosition(0.f, -2.95f, -0.1f);
		pGround->GetComponent<Transform>()->SetScale(4.3f * 7.f, 1.f * 0.3f, 0.f);
	}
	void HelisiumBoss::StartSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->SetLoop(true);
		pAudio->Play();
	}

	void HelisiumBoss::EndSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->Stop();
	}
	void HelisiumBoss::create_monster()
	{
		Megnus* pMegnus = new Megnus();
		pMegnus->Initialize();
		AddGameObject(eLayerType::Monster, pMegnus);
	}
}