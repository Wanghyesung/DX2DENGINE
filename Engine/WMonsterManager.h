#pragma once
#include "Engine.h"

namespace W
{
	class Monster;
	class MonsterManager
	{
	public:
		static void Update();
		static void AddDeadObject(Monster* _pGameObj);

	private:
		static void respawn(Monster* _pGameObj);
		static void create_item(Monster* _pGameObj);

	private:
		static std::vector<Monster*> m_vecDeadObjs;
		static std::vector<float> m_vecReSpwanTime;
	};
}


