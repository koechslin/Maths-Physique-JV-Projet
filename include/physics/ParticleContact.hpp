#ifndef FRAYIEN_PARTICLECONTACT
#define FRAYIEN_PARTICLECONTACT

#include <array>

#include "physics/Particle.hpp"

class ParticleContact
{
private:
    std::array<Particle*, 2> m_particles;

    // value between 0 - 1
    // define the elasticness of the collision
    float m_restitution;

    // distance of penetration of the contact
    float m_penetration;

    // contact normal
    Vector3f m_normal;
    
public:
    ParticleContact(Particle* particleA, Particle* particleB);
    virtual ~ParticleContact();

    void resolve(float deltaTime);
    float calculateSeparatingVelocity();

    inline void setRestitution(float rest) { m_restitution = rest; }
    inline float getRestitution() { return m_restitution; }

    inline float getPenetration() { return m_penetration; }

    inline Vector3f getNormal() { return m_normal; }

private:
    void resolveVelocity();
    void resolveInterpenetration();
};

#endif // FRAYIEN_PARTICLECONTACT
