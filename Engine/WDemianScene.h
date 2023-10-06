#pragma once
#include "..\Engine_Source\WScene.h"
namespace W
{
	class DemianScene : public Scene
	{
	public:
		DemianScene();
		virtual ~DemianScene();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void OnEnter()override;
		virtual void OnExit()override;

		virtual void CreateBackground() override;

	private:
		void fadein();
		void phase2();

	private:
		void create_monster();
		class SharHP* m_pSharHP;

		class White* m_pWhite;
		bool m_bEnd;
		UINT m_iFadeCallStack;
	};
}


