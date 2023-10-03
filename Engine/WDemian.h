#pragma once
#include "WMonster.h"

namespace W
{
	class Demian : public Monster
	{
	public:
		Demian();
		virtual ~Demian();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void add_skill();
		void setattack();

		void chanage_level();

		void attack0();
		void attack1();
		void attack2();
		void attack3();


		std::wstring m_strLevel;
	};
}


