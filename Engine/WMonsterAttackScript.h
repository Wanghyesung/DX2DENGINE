#pragma once

#include "WScript.h"
#include "WBattleManager.h"

namespace W
{
	class MonsterAttackScript : public Script
	{
	public:
		MonsterAttackScript();
		virtual ~MonsterAttackScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other) ;
		virtual void OnCollisionExit(Collider2D* other) ;

		const tAttackInfo& GetAttackInfo() { return m_tAttackInfo; }
		void SetAttackInfo(const tAttackInfo& _tAttackInfo) { m_tAttackInfo = _tAttackInfo; }
		
		void SeteAbnormalType(BattleManager::eAbnormalType _eType) { m_eAbnorType = _eType; }
	private:
		tAttackInfo m_tAttackInfo;

		BattleManager::eAbnormalType m_eAbnorType;
	};

}

