#ifndef MPJVP_PARTICLE
#define MPJVP_PARTICLE

#include <iostream>
#include <cmath>
#include <vector>
#include "physics/Vector3f.hpp"

class Particle
{

public:
	Particle();
	Particle(Vector3f position, float mass, float damping);
	~Particle();

	void integrate(float deltaTime);

	inline Vector3f getPosition() const { return m_position; }
	inline void setPosition(Vector3f pos) { m_position = pos; }

	inline Vector3f getVelocity() const { return m_velocity; }
	inline void setVelocity(Vector3f initialVelocity) { m_velocity = initialVelocity; }

	inline Vector3f getTotalForce() const { return m_totalForce; }
	inline void setTotalForce(Vector3f totalForce) { m_totalForce = totalForce; }
	inline void addForce(Vector3f force) { m_totalForce += force; }

	inline float getInverseMass() const { return m_inverseMass; }
	inline void setMass(float mass) { m_inverseMass = 1.0f / mass; }

	inline float getDamping() const { return m_damping; }
	inline void setDamping(float damping) { m_damping = damping; }

	friend std::ostream& operator<<(std::ostream& out, const Particle& a);

private :
	Vector3f m_position;
	Vector3f m_velocity;
	Vector3f m_totalForce;
	float m_inverseMass;
	float m_damping;
};

#endif // MPJVP_PARTICLE