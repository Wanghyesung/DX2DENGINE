#include "WSlow.h"
#include "WAnimator.h"
#include "WResources.h"
namespace W
{
	Slow::Slow(float _fAccStat):
		UpStat(_fAccStat)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"slow2Mater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"slow2Tex", L"..\\Resources\\Texture\\Abnormal\\slow2.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"slow", pAtlas, Vector2(0.0f, 0.0f), Vector2(112.0f, 91.0f), 6, Vector2(110.f, 110.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"slow", true);
	}
	Slow::~Slow()
	{

	}
	void Slow::Initialize()
	{

	}
	void Slow::Update()
	{
		UpStat::Update();
	}
	void Slow::LateUpdate()
	{
		UpStat::LateUpdate();
	}
	void Slow::Render()
	{
		UpStat::Render();
	}
}