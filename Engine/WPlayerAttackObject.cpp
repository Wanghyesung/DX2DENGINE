#include "WPlayerAttackObject.h"
#include "WAttackScript.h"
#include "WEffect.h"
#include "WSceneManger.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WEventManager.h"
namespace W
{
	PlayerAttackObject::PlayerAttackObject():
		m_pPlayer(nullptr),
		m_pSoundClip(nullptr)
	{

	}
	PlayerAttackObject::~PlayerAttackObject()
	{
		
	}
	void PlayerAttackObject::Initialize()
	{
		AddComponent<AttackScript>()->SetDeleteTime(0.1f);

		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.4f, 0.2f));
	}
	void PlayerAttackObject::Update()
	{
		GameObject::Update();
	}
	void PlayerAttackObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void PlayerAttackObject::Render()
	{
		GameObject::Render();
	}
	void PlayerAttackObject::Off()
	{
		GetScript<AttackScript>()->off();

		SceneManger::Erase(this);
		GetComponent<Collider2D>()->SetActive(false);
		m_pPlayer->GetScript<PlayerScript>()->AddPlayerSkill(this);
	}
	void PlayerAttackObject::PushObjectPoll()
	{
		EventManager::AddObjectPoll(this);
	}
	void PlayerAttackObject::SetSound(std::shared_ptr<AudioClip> clip, bool _bLoop)
	{
		m_pSoundClip = clip;
		m_pSoundClip->SetLoop(_bLoop);
	}
	void PlayerAttackObject::StartSound()
	{

	}
	void PlayerAttackObject::EndSound()
	{

	}
	void PlayerAttackObject::SetHitSound(std::shared_ptr<AudioClip> clip, bool _bLoop)
	{
		m_pSoundClip = clip;
		m_pHitSoundClip->SetLoop(_bLoop);
	}
	void PlayerAttackObject::HitStartSound()
	{

	}
	void PlayerAttackObject::HitEndSound()
	{

	}
}