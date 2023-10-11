#pragma once
#include "WPlayerAttackObject.h"

namespace W
{
	class UltimateObject : public PlayerAttackObject
	{
	public:
		UltimateObject();
		virtual ~UltimateObject();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void Off()override;

	private:
		float m_fCurResetTime;
		float m_fResetTime;
	};
}


