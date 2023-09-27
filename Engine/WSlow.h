#pragma once
#include "WUpStat.h"

namespace W
{
	class Slow : public UpStat
	{
	public:
		Slow(float _fAccStat);
		virtual ~Slow();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


	private:

	};
}

