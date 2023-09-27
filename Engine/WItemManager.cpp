#include "WItemManager.h"
#include "WAlixirUI.h"
#include "WHorntailItem.h"
#include "WWeapon_10.h"
#include "WHat_10.h"
#include "WTop_10.h"
#include "WBottom_10.h"
#include "WShoes_10.h"

namespace W
{
#define HashItems std::unordered_map<std::wstring, IconUI*>

	HashItems ItemManager::m_hashItems = {};
	void ItemManager::Initialize()
	{
		//아이템 텍스쳐, 객체 이름, 보관이름 전부 동일하게
#pragma region Item
		AlixirUI* pAlixir = new AlixirUI();
		pAlixir->Initialize();
		pAlixir->SetName(L"alixir");
		AddItem(pAlixir);

		HorntailItem* pHorntailItem = new HorntailItem();
		pHorntailItem->SetName(L"horntailItem");
		AddItem(pHorntailItem);

		Weapon_10* pWeapon10 = new Weapon_10();
		pWeapon10->SetName(L"10_weapon");
		AddItem(pWeapon10);

		Hat_10* pHat10 = new Hat_10();
		pHat10->SetName(L"10_hat");
		AddItem(pHat10);

		Top_10* pTop10 = new Top_10();
		pTop10->SetName(L"10_top");
		AddItem(pTop10);

		Bottom_10* pBottom10 = new Bottom_10();
		pBottom10->SetName(L"10_bottom");
		AddItem(pBottom10);

		Shoes_10* pShoes10 = new Shoes_10();
		pShoes10->SetName(L"10_shoes");
		AddItem(pShoes10);

#pragma endregion

	}
	void ItemManager::Release()
	{
		HashItems::iterator iter = m_hashItems.begin();

		for (iter; iter != m_hashItems.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	void ItemManager::AddItem(IconUI* pItem)
	{
		const IconUI* pIcon = find_item(pItem->GetName());
		if (pIcon != nullptr)
			return;

		m_hashItems.insert(std::make_pair(pItem->GetName(), pItem));
	}
	IconUI* ItemManager::find_item(const std::wstring& _strName)
	{
		HashItems::iterator iter =
			m_hashItems.find(_strName);

		if (iter == m_hashItems.end())
			return nullptr;
		
		return iter->second;
	}
	IconUI* ItemManager::GetClone(const std::wstring& _strName)
	{
		IconUI* pIcon = find_item(_strName);

		if (pIcon == nullptr)
			return nullptr;

		return pIcon->Create_Clone();
	}
}