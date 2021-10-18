#ifndef MPJVP_PARTICLEANCHOREDSPRING
#define MPJVP_PARTICLEANCHOREDSPRING

#include "physics/ParticleForceGenerator.hpp"

class ParticleAnchoredSpring : public ParticleForceGenerator 
{
protected:
	Vector3f m_anchor;
    float m_k;
    float m_restLength;

public:
	ParticleAnchoredSpring();
	ParticleAnchoredSpring(Vector3f anchor, float k, float restLength);
	virtual ~ParticleAnchoredSpring();

	void setK(float k);
    void setRestLength(float restLength);
	void setAnchor(Vector3f anchor);

	virtual void updateForce(Particle* particle, float duration);
};

#endif // MPJVP_PARTICLEANCHOREDSPRING