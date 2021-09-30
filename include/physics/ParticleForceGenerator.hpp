#ifndef MPJVP_PARTICLEFORCEGENERATOR
#define MPJVP_PARTICLEFORCEGENERATOR

#include "physics/Particle.hpp"

class ParticleForceGenerator
{
public:
	virtual void updateForce(Particle* particle, float duration) = 0;
};

#endif // MPJVP_PARTICLEFORCEGENERATOR