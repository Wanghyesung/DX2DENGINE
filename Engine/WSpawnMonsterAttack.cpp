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
		m_iEndFrame(0),
		m_vecOffset{}
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
		m_vecOffset.clear();
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

				//��ġ �ӵ��� ���ϱ�
				pObj->GetComponent<Rigidbody>()->SetVelocity(m_vecVelocity[m_iCurIndex]);

				if (++m_iCurIndex >= m_vecVelocity.size())
					m_iCurIndex = 0;

				Vector3 vCreatePos = vPosition;
				vCreatePos.x += m_vecOffset[i].x;
				vCreatePos.y += m_vecOffset[i].y;

				pObj->GetComponent<Transform>()->SetPosition(vCreatePos);
				//�ӵ� ����
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
	void SpawnMonsterAttack::SetVelocity(const Vector2& _vVelocity, const Vector3& _vOffset)
	{
		m_vecVelocity.push_back(_vVelocity);
		m_vecOffset.push_back(_vOffset);
	}
	void SpawnMonsterAttack::off()
	{
		SceneManger::Erase(this);
		GetOwner()->AddMonsterSkill(this);
	}
}
