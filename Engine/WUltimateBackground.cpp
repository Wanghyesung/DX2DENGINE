#include "WUltimateBackground.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WAnimator.h"
namespace W
{
	UltimateBackground::UltimateBackground()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"UltiBackMater", pMater);

		//충돌체 없음
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"ultimate1", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate1.png");

		Animator* pAnim = GetComponent<Animator>();
		pAnim->Create(L"ultimate1", pTex, Vector2(0.f, 0.f), Vector2(1412.f, 812.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.13f);
		pAnim->FindAnimation(L"ultimate1")->Create(L"ultimate1", pTex, Vector2(0.f, 0.f), Vector2(1412.f, 812.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.13f);

		mr->SetMaterial(pMater);
	}
	UltimateBackground::~UltimateBackground()
	{
	}
	void UltimateBackground::Initialize()
	{
		GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -3.9f));
		GetComponent<Transform>()->SetScale(Vector3(15.f, 15.f, 0.f));
	}
	void UltimateBackground::Update()
	{
		GameObject::Update();
	}
	void UltimateBackground::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UltimateBackground::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}