#ifndef MPJVP_PHYSICSENGINE
#define MPJVP_PHYSICSENGINE

#include "GameState.hpp"
#include "physics/ParticleForceRegistry.hpp"
#include "physics/ParticleContactResolver.hpp"
#include "physics/ParticleContactGenerator.hpp"

class PhysicsEngine
{

public:
	PhysicsEngine();
	~PhysicsEngine();

	void update(float deltaTime, GameState & gameState);
	void registerForce(Particle * particle, ParticleForceGenerator * particleForceGenerator, float duration);

    inline ParticleForceRegistry & getParticleForceRegistry() { return m_particleForceRegistry; }

private :
	ParticleForceRegistry m_particleForceRegistry;
	ParticleContactResolver m_particleContactResolver;
};

#endif // MPJVP_PHYSICSENGINE
