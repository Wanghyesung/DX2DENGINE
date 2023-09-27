#include "WTempleBossScene.h"
#include "WResources.h"
#include "WShader.h"
#include "WGameObject.h"
#include "WMesh.h"
#include "WMaterial.h"
#include "WMeshRenderer.h"
#include "WTransform.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WNPC.h"
#include "WGround.h"
#include "WSolomon.h"
#include "WCollisionManager.h"
#include "WRex.h"
#include "WMunin.h"
#include "WAriel.h"
#include "WPinkBean.h"
#include "WWhiggin.h"
namespace W
{
	TempleBossScene::TempleBossScene()
	{
		SetMapSize(-0.5f, 0.f, 0.5f, 0.f);
		SetMapPossibleSize(-7.5f, 7.5f);
	}
	TempleBossScene::~TempleBossScene()
	{

	}
	void TempleBossScene::Initialize()
	{
		CreateBackground();

		create_monster();

		NPC* pNPC = new NPC();
		AddGameObject(eLayerType::NPC, pNPC);
		MeshRenderer* pMeshRender = pNPC->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"NPCMater5"));
		pNPC->GetComponent<Transform>()->SetPosition(-7.f, -2.f, -1.f);
		pNPC->GetComponent<Transform>()->SetScale(0.547f * 1.2, 1.f * 1.2f, 0.f);
		pNPC->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);


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
	void TempleBossScene::Update()
	{
		Scene::Update();
	}
	void TempleBossScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TempleBossScene::Render()
	{
		Scene::Render();
	}
	void TempleBossScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ladder, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::AttackObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
	}
	void TempleBossScene::OnExit()
	{

	}
	void TempleBossScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"TempleBossMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.f * 8.f, 1.f * 8.f, 1.f);


		Ground* pGround = new Ground(true);
		AddGameObject(eLayerType::Ground, pGround);
		pGround->GetComponent<Transform>()->SetPosition(0.f, -2.75f, -0.1f);
		pGround->GetComponent<Transform>()->SetScale(2.7f * 7.f, 1.f * 0.3f, 0.f);
	}

	void TempleBossScene::create_monster()
	{
		PinkBean* pPinkBean = new PinkBean();
		pPinkBean->Initialize();
		AddGameObject(eLayerType::Monster, pPinkBean);
	}
}