#pragma once
#include "WGameObject.h"

namespace W
{
	class Player;
	class Effect;
	class PlayerAttackObject : public GameObject
	{
	public:
		PlayerAttackObject();
		virtual ~PlayerAttackObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		Player* GetPlayer() { return m_pPlayer; }
		void SetPlayer(Player* _pPlayer){ m_pPlayer = _pPlayer;}

		virtual void Off();
		void PushObjectPoll();

		void SetSound(std::shared_ptr<AudioClip> clip, bool _bLoop);
		void StartSound();
		void EndSound();

		void SetHitSound(std::shared_ptr<AudioClip> clip, bool _bLoop);
		void HitStartSound();
		void HitEndSound();

	private:
		Player* m_pPlayer;

		std::shared_ptr<AudioClip> m_pSoundClip;
		std::shared_ptr<AudioClip> m_pHitSoundClip;
	};
}


