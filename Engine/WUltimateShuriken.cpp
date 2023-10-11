#include "WUltimateShuriken.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WCollider2D.h"
#include "WTime.h"
#include "WAttackScript.h"
#include "WRenderer.h"
namespace W
{
	UltimateShuriken::UltimateShuriken()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"UlitShurikenMater", pMater);

		//충돌체 없음
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"UltiShuriken");

		Animator* pAnim = GetComponent<Animator>();
		pAnim->Create(L"ultimate1", pTex, Vector2(0.f, 0.f), Vector2(581.f, 251.f), 6, Vector2(600.f, 600.f), Vector2(0.0f, 0.f), 0.13f);
	
		mr->SetMaterial(pMater);


	}
	UltimateShuriken::~UltimateShuriken()
	{

	}
	void UltimateShuriken::Initialize()
	{
		GetComponent<Transform>()->SetScale(5.f, 5.f, 0.f);
		Collider2D* pCOll = AddComponent<Collider2D>();
		pCOll->SetSize(Vector2(0.7f, 0.4f));

		AttackScript* pScript = AddComponent<AttackScript>();
		//pScript->SetDir(m_iDir);
		//최대 15명의 적 공격가능
		pScript->SetStayObject(3, 0.3f);
		pScript->SetDeleteTime(3.5f);
		pScript->SetAbleAttackCount(15);
	}
	void UltimateShuriken::Update()
	{
		Vector3 vPos = GetComponent<Transform>()->GetPosition();
		Vector2 vVel = m_vDir * 7.f;

		vPos.x *= (Time::DeltaTime() * vVel.x);
		vPos.y *= (Time::DeltaTime() * vVel.y);
		GetComponent<Transform>()->SetPosition(vPos);

		GameObject::Update();

	}
	void UltimateShuriken::LateUpdate()
	{
		GameObject::LateUpdate();

	}
	void UltimateShuriken::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void UltimateShuriken::SetStartPos(Vector3 _vPos)
	{
		GetComponent<Transform>()->SetPosition(_vPos);
	}
}