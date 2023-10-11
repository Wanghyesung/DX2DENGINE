#pragma once
#include "WSkillState.h"
namespace W
{
	class UltimateSkill : public SkillState
	{
	public:
		UltimateSkill();
		virtual ~UltimateSkill();

		virtual void Update()override;
		virtual void Initialize()override;

		virtual void Enter()override;
		virtual void Exit()override;

	private:
		void activeskill_ultimate();
		void create_shuriken();

	private:
		bool m_bCreate;

		class UltimateFog* m_pFog;
		class UltimateBackground* m_pBackGround;
	};

}

