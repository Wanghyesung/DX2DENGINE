#include "WSpawnUltimate.h"
#include "WTime.h"

namespace W
{
	SpawnUltimate::SpawnUltimate():
		m_fCreateTime(2.f)
	{
		m_vecCreateCount.push_back(3);
		m_vecCreateCount.push_back(4);
		m_vecCreateCount.push_back(5);
	}
	SpawnUltimate::~SpawnUltimate()
	{

	}
	void SpawnUltimate::Initialize()
	{

	}
	void SpawnUltimate::Update()
	{
		m_fCreateTime += Time::DeltaTime();


		GameObject::Update();
	}
	void SpawnUltimate::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void SpawnUltimate::Render()
	{
		GameObject::Render();
	}
}