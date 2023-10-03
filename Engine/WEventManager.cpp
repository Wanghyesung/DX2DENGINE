#include "WEventManager.h"
#include "WSceneManger.h"
#include "WSkillManager.h"
#include "..\Engine\WPlayerAttackObject.h"
namespace W
{
	std::vector<tEvent> EventManager::m_vecEvent = {};
	std::vector<GameObject*> EventManager::m_vecObjectPool = {};

	std::wstring EventManager::m_strNextScene = {};
#define ObjectPollPosition 2000.f
	void EventManager::Update()
	{
		for (int i = 0; i < m_vecObjectPool.size(); ++i)
		{
			dynamic_cast<PlayerAttackObject*>(m_vecObjectPool[i])->Off();
		}
		m_vecObjectPool.clear();

		for (int i = 0; i < m_vecEvent.size(); ++i)
		{
			excute(m_vecEvent[i]);
		}
		m_vecEvent.clear();
	}
	
	void EventManager::excute(const tEvent& _tEve)
	{
		switch (_tEve.eEventType)
		{
		case EVENT_TYPE::CREATE_OBJECT:
		{
			GameObject* pObj = (GameObject*)_tEve.lParm;
			eLayerType eLyaer = (eLayerType)_tEve.wParm;

			SceneManger::AddGameObject(eLyaer, pObj);
		}
		break;

		case EVENT_TYPE::DELET_OBJECT:
		{
			
		}
		break;

		case EVENT_TYPE::SCENE_CHANGE:
		{
			SceneManger::LoadScene(m_strNextScene);
		}
		break;

		case EVENT_TYPE::CHANGE_PLAYER_STATE:
		{
			PlayerFSM* pFSM = (PlayerFSM*)_tEve.lParm;
			Player::ePlayerState eState = (Player::ePlayerState)_tEve.wParm;
			pFSM->ChangeState(eState);
		}
		break;
		case EVENT_TYPE::CHANGE_PLAYER_SKILL:
		{
			Player::ePlayerSkill _ePlayerSkill = (Player::ePlayerSkill)_tEve.lParm;
			SkillManager::SetActiveSkill(_ePlayerSkill);
		}
		break;

		case EVENT_TYPE::CHANGE_MONSTER_STATE:
		{
			MonsterFSM* pFSM = (MonsterFSM*)_tEve.lParm;
			Monster::eMonsterState eState = (Monster::eMonsterState)_tEve.wParm;
			pFSM->ChangeState(eState);
		}
		break;
		case EVENT_TYPE::ADD_OBJECTPOLL:
		{
			GameObject* pObj = (GameObject*)_tEve.lParm;
			m_vecObjectPool.push_back(pObj);
		}
		break;
		case EVENT_TYPE::HITCH_ABNORMAL:
		{
			GameObject* pObj = (GameObject*)_tEve.lParm;
			BattleManager::eAbnormalType eType = (BattleManager::eAbnormalType)_tEve.wParm;
			switch (eType)
			{
			case W::BattleManager::eAbnormalType::SealPotion:
				BattleManager::seal_potion(pObj);
				break;
			case W::BattleManager::eAbnormalType::SealSkill:
				BattleManager::seal_skill(pObj);
				break;
			case W::BattleManager::eAbnormalType::temptation:
				BattleManager::temptation(pObj);
				break;
			case W::BattleManager::eAbnormalType::Undead:
				BattleManager::undead(pObj);
				break;
			case W::BattleManager::eAbnormalType::Faint:
				BattleManager::faint(pObj);
				break;
			case W::BattleManager::eAbnormalType::Stop:
				BattleManager::stop(pObj);
				break;
			case W::BattleManager::eAbnormalType::Dark:
				BattleManager::dark(pObj);
				break;
			case W::BattleManager::eAbnormalType::Confusion:
				BattleManager::confusion(pObj);
				break;
			case W::BattleManager::eAbnormalType::Slow:
				BattleManager::debuff_slow(pObj, _tEve.accParm);//능력치 깍는 효과는 accparm추가
				break;
			case W::BattleManager::eAbnormalType::Variation:
				BattleManager::variation(pObj);
				break;
			}
		}
		break;

		case EVENT_TYPE::UP_STAT:
		{
			GameObject* pObj = (GameObject*)_tEve.lParm;
			BattleManager::eUpStatType eType = (BattleManager::eUpStatType)_tEve.wParm;
			float fAccStat = (float)_tEve.accParm;
			switch (eType)
			{
			case W::BattleManager::eUpStatType::Attack:
				BattleManager::buff_attack(pObj, fAccStat);
				break;
			case W::BattleManager::eUpStatType::Speed:
				BattleManager::buff_speed(pObj, fAccStat);
				break;
			case W::BattleManager::eUpStatType::Defense:
				BattleManager::buff_defense(pObj, fAccStat);
				break;
			case W::BattleManager::eUpStatType::Heal:
				BattleManager::buff_heal(pObj, fAccStat);
				break;
			case W::BattleManager::eUpStatType::Ignore:
				BattleManager::buff_ignore(pObj, fAccStat);
				break;
			case W::BattleManager::eUpStatType::ReflexAttack:
				BattleManager::buff_reflex(pObj, fAccStat);
				break;
			//player
			case W::BattleManager::eUpStatType::AccHP:
				BattleManager::buff_HP(pObj,fAccStat);
				break;
			case W::BattleManager::eUpStatType::AccMP:
				BattleManager::buff_MP(pObj,fAccStat);
				break;
			}
		}
		break;
		case EVENT_TYPE::RESTORE:
		{
			GameObject* pObj = (GameObject*)_tEve.lParm;
			BattleManager::eAbnormalType eType = (BattleManager::eAbnormalType)_tEve.wParm;
			float fAccStat = (float)_tEve.accParm;
			BattleManager::restore(pObj,eType,fAccStat);
		}
		break;
		}
	}

	void EventManager::AddObjectPoll(GameObject* pObj)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::ADD_OBJECTPOLL;
		eve.lParm = (DWORD_PTR)pObj;

		//오브젝트 풀에 넘기기
		Vector3 vPosition = pObj->GetComponent<Transform>()->GetPosition();
		vPosition.x += ObjectPollPosition;
		vPosition.y += ObjectPollPosition;
		pObj->GetComponent<Transform>()->SetPosition(vPosition);

		AddEvent(eve);
	}

	void EventManager::ChangeScene(const std::wstring& _strNextScene)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::SCENE_CHANGE;
		m_strNextScene = _strNextScene;

		AddEvent(eve);
	}
	void EventManager::ChangePlayerFSMState(PlayerFSM* _pFSM, Player::ePlayerState _ePlayerState)
	{
		tEvent eve = {};
		eve.lParm = (DWORD_PTR)_pFSM;//보낼 주소
		eve.wParm = (DWORD_PTR)_ePlayerState;//다음 상태값
		eve.eEventType = EVENT_TYPE::CHANGE_PLAYER_STATE;

		AddEvent(eve);
	}
	void EventManager::ChangePlayerSkillState(Player::ePlayerSkill _ePlayerSkill)
	{
		tEvent eve = {};
		eve.lParm = (DWORD_PTR)_ePlayerSkill;
		eve.eEventType = EVENT_TYPE::CHANGE_PLAYER_SKILL;
		AddEvent(eve);
	}
	void EventManager::ChangeMonsterFSMState(MonsterFSM* _pFSM, Monster::eMonsterState _eMonsterState)
	{
		tEvent eve = {};
		eve.lParm = (DWORD_PTR)_pFSM;//보낼 주소
		eve.wParm = (DWORD_PTR)_eMonsterState;//다음 상태값
		eve.eEventType = EVENT_TYPE::CHANGE_MONSTER_STATE;

		AddEvent(eve);
	}

	void EventManager::CreateObject(GameObject* _pObj, eLayerType _eLayer)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_OBJECT;
		eve.lParm = (DWORD_PTR)_pObj;
		eve.wParm = (DWORD_PTR)_eLayer;

		AddEvent(eve);
	}

	void EventManager::HitchAbnormal(GameObject* _pObj, BattleManager::eAbnormalType _eType, float _fAccStat)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::HITCH_ABNORMAL;
		eve.lParm = (DWORD_PTR)_pObj;
		eve.wParm = (DWORD_PTR)_eType;
		eve.accParm = _fAccStat;

		AddEvent(eve);
	}

	void EventManager::Restore(GameObject* _pObj, BattleManager::eAbnormalType _eType, float _fAccStat)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::RESTORE;
		eve.lParm = (DWORD_PTR)_pObj;
		eve.wParm = (DWORD_PTR)_eType;
		eve.accParm = (LONG_PTR)_fAccStat;

		AddEvent(eve);
	}

	void EventManager::UpStat(GameObject* _pObj, BattleManager::eUpStatType _eType, float _fAccStat)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::UP_STAT;
		eve.lParm = (DWORD_PTR)_pObj;
		eve.wParm = (DWORD_PTR)_eType;
		eve.accParm = (LONG_PTR)_fAccStat;

		AddEvent(eve);
	}

}