#include "WUltimateObject.h"
#include "WAttackScript.h"
#include "WSceneManger.h"
#include "WTime.h"
namespace W
{
	UltimateObject::UltimateObject():
		m_fCurResetTime(0.f),
		m_fResetTime(0.32f)
	{
		AddComponent<AttackScript>();
	}
	UltimateObject::~UltimateObject()
	{

	}
	void UltimateObject::Initialize()
	{
		//3.5�� ���� �� 8���� ���� ���ݴ� 7��
		GetComponent<AttackScript>()->SetStayObject(7, m_fResetTime);
		GetScript<AttackScript>()->SetDeleteTime(m_fResetTime * 8.f);
		//�ִ� 15�� ���� ����
		GetScript<AttackScript>()->SetAbleAttackCount(12);
	}
	void UltimateObject::Update()
	{
		m_fCurResetTime += Time::DeltaTime();

		if (m_fCurResetTime >= m_fResetTime)
		{
			m_fCurResetTime = 0.f;
			GetScript< AttackScript>()->ResetAttackCount();
		}

		GameObject::Update();
	}
	void UltimateObject::LateUpdate()
	{
		GameObject::LateUpdate();

	}
	void UltimateObject::Render()
	{
		GameObject::Render();

	}
	void UltimateObject::Off()
	{
		m_fCurResetTime = 0.f;
		PlayerAttackObject::Off();
	}
}