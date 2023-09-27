#pragma once
#include "WDamageFont.h"
#include "WAbnormal.h"
#include "WInfo.h"
#include "WEffect.h"

namespace W
{
	//SceneManager 다음 실행
	using namespace math;
	class BattleManager
	{
	public:
		enum class eAbnormalType
		{
			None,
			SealPotion,
			SealSkill,
			temptation,
			Faint,
			Dark,
			Confusion,
			Slow,
			Undead,
			Variation,
			End
		};

		enum class eUpStatType
		{
			None,
			Attack,
			Speed,
			Defense,
			Heal,
			Ignore,
			ReflexAttack,
			AccHP,
			AccMP,
			End
		};

		struct tDamageCount
		{
			tDamageCount():
				m_fResetTime(0.4f)
			{

			}
			UINT iCurCount;
			UINT iEndCount;

			float m_fCurTime;
			float m_fResetTime;
		};

		static void Initialize();
		static void Release();
		static void Update();
		static void CheckDamage(tObjectInfo& _tObjectInfo, const tAttackInfo& _tAttackInfo, const std::wstring _strName, Vector3 _vPosition);
		static void PushFont(DamageFont* _pDamageFont);
		
		static bool IsAblePotion();

		static void PushEffect(Effect* _pEffect);
		static Effect* GetEffect(std::wstring _strName);

		static void HitchAbnormal(eAbnormalType _eType, float _fAccStat = 0.f);
		static void Buff_Stat(GameObject* _pTarget, eUpStatType _eType, float _fAccStat);

	private:
		static void render_damage(std::queue<DamageFont*> _queueFonts, UINT _iDamageCount, const std::wstring& _strName);
		static void erase_damage(const std::wstring& _strName);
		static tDamageCount& add_damage(UINT _iDamageCount, const std::wstring& _strName);


		static void dark(GameObject* _pGameObject);
		static void faint(GameObject* _pGameObject);
		static void seal_potion(GameObject* _pGameObject);
		static void seal_skill(GameObject* _pGameObject);
		static void temptation(GameObject* _pGameObject);
		static void confusion(GameObject* _pGameObject);//변이
		static void undead(GameObject* _pGameObject);
		static void variation(GameObject* _pGameObject);

		static void restore_move(Player* _pTarget);

		//monster
		static void buff_attack(GameObject* _pTarget, float _fAccDamage);
		static void buff_defense(GameObject* _pTarget, float _fDefense);
		static void buff_ignore(GameObject* _pTarget, float _fsign);
		static void buff_heal(GameObject* _pTarget, float _fAccHeal);
		static void buff_reflex(GameObject* _pTarget, float _fsign);
		//player
		static void buff_speed(GameObject* _pTarget, float _fAccSpeed);
		static void slow(GameObject* _pGameObject,float _fAccSpeed);
		static void buff_HP(GameObject* _pTarget, float _fAccValue);
		static void buff_MP(GameObject* _pTarget, float _fAccValue);
	private:
		static std::queue<DamageFont*> m_queueFonts;
		static std::map<std::wstring, tDamageCount> m_mapDamage;
		static UINT m_iMaxDamage;

		static std::map<std::wstring, std::queue<Effect*>> m_mapEffects;

		//상태이상 
		static bool m_bOnAbnormal;

		//체력 회복 시간
		static float m_fPotionTime;
		static float m_fCurPotionTime;

		friend class EventManager;
		friend class Abnormal;
	};
}


