#pragma once
#include "WGameObject.h"

namespace W
{
	class DmianStigma : public GameObject
	{
	public:
		DmianStigma();
		virtual ~DmianStigma();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:


	};
}


