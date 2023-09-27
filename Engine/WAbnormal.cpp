#include "WAbnormal.h"
#include "WTime.h"
#include "WBattleManager.h"
#include "WPlayer.h"
#include "WObject.h"

namespace W
{
	Abnormal::Abnormal() :
		m_pTarget(nullptr),
		m_bRender(false),
		m_fDeleteTime(0.f),
		m_fCurTime(0.f)
	{

	}
	Abnormal::~Abnormal()
	{

	}
	void Abnormal::Initialize()
	{
	}
	void Abnormal::Update()
	{	

		GameObject::Update();
	}
	void Abnormal::LateUpdate()
	{	
		m_fCurTime += Time::DeltaTime();

		if (m_fCurTime >= m_fDeleteTime ||
			m_pTarget->GetState() == GameObject::Dead)
		{
			object::Destroy(this);
			BattleManager::restore_move(m_pTarget);
			return;
		}

		Vector3 vTargetPos = m_pTarget->GetComponent<Transform>()->GetPosition();
		vTargetPos.y += 0.5f;
		vTargetPos.z -= 0.5f;

		GetComponent<Transform>()->SetPosition(vTargetPos);

		GameObject::LateUpdate();
	}
	void Abnormal::Render()
	{	
		GameObject::Render();
	}

}