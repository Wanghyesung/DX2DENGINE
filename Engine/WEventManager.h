#pragma once
#include "Engine.h"
#include "WPlayerFSM.h"
#include "WMonsterFSM.h"
#include "WBattleManager.h"
namespace W
{
	enum class EVENT_TYPE
	{
		CREATE_OBJECT,
		DELET_OBJECT,
		SCENE_CHANGE,
		CHANGE_PLAYER_STATE,
		CHANGE_PLAYER_SKILL,
		CHANGE_MONSTER_STATE,
		ADD_OBJECTPOLL,
		HITCH_ABNORMAL,
		UP_STAT,
		END,
	};

	struct tEvent
	{
		DWORD_PTR wParm;
		DWORD_PTR lParm;
		LONG_PTR accParm;//�߰� ����
		EVENT_TYPE eEventType;
	};
	class EventManager
	{
	public:
		static void Update();
		static void AddEvent(const tEvent& _tEve) { m_vecEvent.push_back(_tEve); }
		
		static void AddObjectPoll(GameObject* pObj);
		static void ChangeScene(const std::wstring& _strNextScene);
		static void ChangePlayerFSMState(PlayerFSM* _pFSM, Player::ePlayerState _ePlayerState);
		static void ChangePlayerSkillState(Player::ePlayerSkill _ePlayerSkill);
		static void ChangeMonsterFSMState(MonsterFSM* _pFSM, Monster::eMonsterState _eMonsterState);
		static void CreateObject(GameObject* _pObj, eLayerType _eLayer);
		static void HitchAbnormal(GameObject* _pObj, BattleManager::eAbnormalType _eType, float _fAccStat = 0.f);
		static void UpStat(GameObject* _pObj, BattleManager::eUpStatType _eType, float _fAccStat);
	private:
		static void excute(const tEvent& _tEve);

	private:
		static std::vector<tEvent> m_vecEvent;
		static std::vector<GameObject*> m_vecObjectPool;
		static std::wstring m_strNextScene;
	};
}

