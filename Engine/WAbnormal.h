#pragma once
#include "WGameObject.h"

namespace W
{
	class Player;
	class Abnormal : public GameObject
	{
	public:
		Abnormal();
		virtual ~Abnormal();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void Restore();

		void SetTime(float _fTime) { m_fDeleteTime = _fTime; }
		void SetTarget(Player* _pTarget) { m_pTarget = _pTarget; }

	protected:
		Player* m_pTarget;
		
	private:
		float m_fDeleteTime;
		float m_fCurTime;
		bool m_bRender;

		friend class BattleManager;
	};
}


