#include "WMonster.h"
#include "WRenderer.h"
#include "WSceneManger.h"
#include "WCollisionManager.h"

namespace W
{
	Monster::Monster():
		m_iDir(1),
		m_eMonsterState(eMonsterState::stand),
		m_strCurStateName(L"_stand"),
		m_vecItemNames{},
		m_iCreateCount(1),
		m_mapAttackObjs{}
	{

	}
	Monster::~Monster()
	{
		std::map < std::wstring, std::queue<MonsterAttackObject*>>::iterator iter =
			m_mapAttackObjs.begin();

		for (iter; iter != m_mapAttackObjs.end(); ++iter)
		{
			std::queue< MonsterAttackObject*> queue = iter->second;
			while (!queue.empty())
			{
				MonsterAttackObject* pObj =  queue.front();
				delete pObj;
				pObj = nullptr;
				queue.pop();
			}

		}
	}
	void Monster::Initialize()
	{
		
	}
	void Monster::Update()
	{
		if (m_bDead)
			return;

		GameObject::Update();
	}
	void Monster::LateUpdate()
	{
		if (m_bDead)
			return;
		GameObject::LateUpdate();
	}

	void Monster::Render()
	{
		if (m_bDead)
			return;

		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = m_iDir * -1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void Monster::SetItem(const std::vector<std::wstring>& _vecItemNames)
	{
		for (int i = 0; i < _vecItemNames.size(); ++i)
			m_vecItemNames.push_back(_vecItemNames[i]);
	}

	void Monster::AddMonsterSkill(MonsterAttackObject* _pObj)
	{
		std::map<std::wstring, std::queue<MonsterAttackObject*>>::iterator iter =
			m_mapAttackObjs.find(_pObj->GetName());

		if (iter == m_mapAttackObjs.end())
		{
			std::queue<MonsterAttackObject*> queue = {};
			queue.push(_pObj);
			m_mapAttackObjs.insert(std::make_pair(_pObj->GetName(), queue));
		}
		else
			iter->second.push(_pObj);

		
	}

	MonsterAttackObject* Monster::GetMonsterSkill(const std::wstring& _strName)
	{
		std::map<std::wstring, std::queue<MonsterAttackObject*>>::iterator iter =
			m_mapAttackObjs.find(_strName);

		if(iter == m_mapAttackObjs.end())
			assert(nullptr);

		MonsterAttackObject* pObj = iter->second.front();
		iter->second.pop();

		return pObj;
	}

	

}