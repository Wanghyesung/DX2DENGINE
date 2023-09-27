#pragma once
#include "WComponent.h"


namespace W 
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetMass(float _fMass) { m_fMass = _fMass; }
		void AddForce(Vector2 _vForce);
		void SetGround(bool _bGround) { m_bGround = _bGround; }
		void SetPhysics(bool _bPhysics) { m_bPhysics = _bPhysics; }
		bool IsGround() { return m_bGround; }
		void SetVelocity(Vector2 _vVelocity) { m_vVelocity = _vVelocity; }
		void AddVelocity(Vector2 _vVelocity) { m_vVelocity += _vVelocity; }
		Vector2 GetVelocity() { return m_vVelocity; }

	private:
		void check_map();

	private:
		float   m_fMass;
		Vector2 m_vForce;
		Vector2 m_vAccelation;
		Vector2 m_vVelocity;
		Vector2 m_vLimitedVelocity;

		Vector2 m_vGravity;
		float m_fFriction;
		bool m_bGround;
		bool m_bPhysics;

		float m_fGravityAccel;



	};
}


