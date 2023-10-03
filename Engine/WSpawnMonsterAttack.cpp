#include "WSpawnMonsterAttack.h"
#include "WMonster.h"
#include "WTime.h"
#include "WSceneManger.h"
#include "WEventManager.h"
#include "WRigidbody.h"
#include "WAnimator.h"
namespace W
{
	SpawnMonsterAttack::SpawnMonsterAttack():
		m_fCreateTime(0.f),
		m_fCurCreateTime(0.f),
		m_iCurIndex(0),
		m_iEndFrame(0)
	{

	}
	SpawnMonsterAttack::~SpawnMonsterAttack()
	{

	}
	void SpawnMonsterAttack::Initialize()
	{
		m_iCurIndex = 0;
		m_iEndFrame = 0;
		m_fCurCreateTime = 0.f;
		m_fCreateTime = 0.f;
		m_vecVelocity.clear();
	}
	void SpawnMonsterAttack::Update()
	{
		int iFrame = GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->GetCurIndex();

		if (m_iEndFrame <= iFrame)
			off();

		GameObject::Update();
	}
	void SpawnMonsterAttack::LateUpdate()
	{
		m_fCurCreateTime += Time::DeltaTime();

		if (m_fCurCreateTime >= m_fCreateTime)
		{
			m_fCurCreateTime = 0.f;
			Vector3 vPosition = GetComponent<Transform>()->GetPosition();

			for (int i = 0; i < m_iCreateCount; ++i)
			{
				MonsterAttackObject* pObj = GetOwner()->GetMonsterSkill(m_strAttackName);
				if (pObj == nullptr)
					return;

				//위치 속도값 정하기
				pObj->GetComponent<Rigidbody>()->SetVelocity(m_vecVelocity[m_iCurIndex]);

				if (++m_iCurIndex >= m_vecVelocity.size())
					m_iCurIndex = 0;

				pObj->GetComponent<Transform>()->SetPosition(vPosition);
				//속도 전달
				pObj->Initialize();

				EventManager::CreateObject(pObj, eLayerType::MonsterAttack);
			}
		}

		GameObject::LateUpdate();
	}
	void SpawnMonsterAttack::Render()
	{
		GameObject::Render();
	}
	void SpawnMonsterAttack::SetVelocity(const Vector2& _vVelocity)
	{
		/*std::random_device rDiv;
		std::mt19937 en(rDiv());
		std::uniform_int_distribution<int> time(_vVelocity.y - 0.2f, _vVelocity.y);
		float m_fCreateTime = (float)time(en);*/

		m_vecVelocity.push_back(_vVelocity);
	}
	void SpawnMonsterAttack::off()
	{
		SceneManger::Erase(this);
		GetOwner()->AddMonsterSkill(this);
	}
}
