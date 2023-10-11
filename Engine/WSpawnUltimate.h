#pragma once
#include "WPlayerAttackObject.h"

namespace W
{
	class SpawnUltimate : public PlayerAttackObject
	{
	public:
		SpawnUltimate();
		virtual ~SpawnUltimate();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		//��
		float m_fCurActiveTime;
		float m_fActiveTime;

		//ǥâ
		std::vector<UINT> m_vecCreateCount;

		float m_fCurCreateTime;
		float m_fCreateTime;
	};
}


