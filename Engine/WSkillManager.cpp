#include "WSkillManager.h"
#include "WTime.h"
#include "WPlayerScript.h"
namespace W
{
	std::map<Player::ePlayerSkill, tSkillTime> SkillManager::m_mapSkillTime = {};
	PlayerSkill* SkillManager::m_pPlayerSkill = nullptr;

	//플레이어꺼 쓰기
	void SkillManager::Update()
	{
		update_skill();
	}
	void SkillManager::Initialize()
	{
	}

	void SkillManager::AddSkill(SkillState* _pSkill)
	{
		Player::ePlayerSkill eSkill = _pSkill->GetPlayerSkill();
		m_mapSkillTime.insert(std::make_pair(eSkill, _pSkill->GetCoolTime()));
	}

	void SkillManager::SetActiveSkill(Player::ePlayerSkill _eSkill)
	{
		PlayerScript* pScript = m_pPlayerSkill->m_pPlayer->GetScript<PlayerScript>();
	
		if (_eSkill == Player::ePlayerSkill::end)
		{
			m_pPlayerSkill->m_pActiveSkill = nullptr;
			m_pPlayerSkill->m_bSkillOn = false;
			return;
		}

		if (m_pPlayerSkill->m_pActiveSkill != nullptr)
			return;

		if (!check_cooltime(_eSkill))
			return;

		if (pScript->IsAbnormal() || pScript->IsAttack() || pScript->IsSealSkill())
			return;

		m_pPlayerSkill->m_pActiveSkill = m_pPlayerSkill->FindSkillState(_eSkill);

		m_pPlayerSkill->m_bSkillOn = true;
		m_pPlayerSkill->m_pActiveSkill->Enter();
		set_max(_eSkill);
	}

	void SkillManager::AccAttack(const Vector3& _vPosition)
	{
		m_pPlayerSkill->AccAttack(_vPosition);	
	}


	void SkillManager::update_skill()
	{
		std::map<Player::ePlayerSkill, tSkillTime>::iterator iter =
			m_mapSkillTime.begin();

		for (iter; iter != m_mapSkillTime.end(); ++iter)
		{
			tSkillTime& tTime = iter->second;
			if (tTime.fCurTime > 0.f)
			{
				tTime.fCurTime -= Time::DeltaTime();
			}
		}
	}
	void SkillManager::set_max(Player::ePlayerSkill _eTarget)
	{
		std::map<Player::ePlayerSkill, tSkillTime>::iterator iter =
			m_mapSkillTime.find(_eTarget);

		tSkillTime& tTime = iter->second;
		tTime.fCurTime = tTime.fCoolTime;
	}

	bool SkillManager::check_cooltime(Player::ePlayerSkill _eTarget)
	{
		std::map<Player::ePlayerSkill, tSkillTime>::iterator iter =
			m_mapSkillTime.find(_eTarget);

		tSkillTime tTime = iter->second;
		if (tTime.fCurTime <= 0.f)
			return true;

		return false;
	}
}