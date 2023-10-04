#pragma once
#include "WMonsterAttackObject.h"
namespace W
{
	class DemianObject : public MonsterAttackObject
	{
	public:
		DemianObject();
		virtual ~DemianObject();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void off();
		void start();
		void move();

		void set_target();
		bool check_position();
		void attack();
	private:
		bool m_bEnd;
		bool m_bMove;

		float m_fWaitTime;
	
		UINT m_iMoveCount;

		Vector3 m_vTargetPos;
		Vector2 m_vVelocity;

		tMonsterAttack m_tMonsterAttack;
		std::wstring m_strCurAnim;

	};
}


