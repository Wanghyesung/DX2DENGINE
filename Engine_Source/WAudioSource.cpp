#include "WAudioSource.h"
#include "WAudioClip.h"
#include "WTransform.h"
#include "WGameObject.h"

namespace W
{
	AudioSource::AudioSource()
		: Component(eComponentType::AudioSource)
		, mAudioClip(nullptr)
	{

	}

	AudioSource::~AudioSource()
	{

	}

	void AudioSource::Initialize()
	{
	}

	void AudioSource::Update()
	{
	}

	void AudioSource::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 foward = tr->Foward();

		mAudioClip->Set3DAttributes(pos, foward);
	}

	void AudioSource::Render()
	{
	}

	void AudioSource::Play()
	{
		mAudioClip->Play();
	}
	void AudioSource::Stop()
	{
		mAudioClip->Stop();
	}
	void AudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}
}