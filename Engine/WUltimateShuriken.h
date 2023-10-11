#pragma once
#include "WPlayerAttackObject.h"
namespace W
{
	class UltimateShuriken : public PlayerAttackObject
	{
	public:
		//가져올 수리검 이미지 넘버
		UltimateShuriken(UINT _iSurikenNum);
		virtual ~UltimateShuriken();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetDir(Vector2 _vVel) { m_vDir = _vVel; }
		void SetStartPos(Vector3 _vPos);
	private:
		Vector2 m_vDir;


	};
}


